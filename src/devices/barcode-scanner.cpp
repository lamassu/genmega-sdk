#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

std::atomic<bool> sigg;
std::mutex m;
std::condition_variable v;
std::string scannedData;
int iRetScan = 0;

bool pred ()
{
	return sigg;
}

void ScannedBarcodeDataCallBack (int iId, int iKind, BCSScanData * BcsScanData)
{
	printf("\n DEBUG: BCS BarCode Data: ID-%d, KIND-%d Data:%s\n", iId, iKind, BcsScanData->szCode);
	scannedData = std::string(reinterpret_cast<char const *>(BcsScanData->szCode));
	sigg = true;
	v.notify_one();
	BCS_Close();
}

void ErrorHandler (int iRet, unsigned char * errmsg)
{
	printf("\n DEBUG: BCS FAIL: %d\n", iRet);
	printf(" DEBUG: DEVICE ERROR CODE: %s\n", errmsg);
	BCS_Close();
}

void StartScan (std::string serialPortName, int mobilePhoneMode, int presentationMode)
{
	unsigned char errmsg[6] = {0};

	scannedData = "";
	iRetScan = 0;

	std::unique_lock<std::mutex> lock(m);

	BCS_CallBackRegister(ScannedBarcodeDataCallBack);

	// open device serial port
	iRetScan = BCS_Open(serialPortName.c_str(), mobilePhoneMode);

	// initialize device
	iRetScan = BCS_Reset();

	// start scan
	iRetScan = BCS_AcceptScanCode(presentationMode);

	if (iRetScan == HM_DEV_OK) {
		printf("\n DEBUG: BCS READY TO SCAN \n");
	} else {
		BCS_GetLastError(errmsg);
		ErrorHandler(iRetScan, errmsg);
	}
}

class ScanWorker : public Napi::AsyncWorker
{
public:
	ScanWorker(Napi::Function& callback, std::string serialPortName, int mobilePhoneMode, int presentationMode)
		: Napi::AsyncWorker(callback), serialPortName_(serialPortName), mobilePhoneMode_(mobilePhoneMode), presentationMode_(presentationMode) {}
	~ScanWorker() {}

	// Executed inside the worker-thread.
	// It is not safe to access JS engine data structure
	// here, so everything we need for input and output
	// should go on `this`.
	void Execute() override
	{
		std::thread t1(std::bind(StartScan, serialPortName_, mobilePhoneMode_, presentationMode_));
		std::unique_lock<std::mutex> lock(m);
		v.wait(lock, pred);
		t1.join();
	}

	// Executed when the async work is complete
	// this function will be run inside the main event loop
	// so it is safe to use JS engine data again
	void OnOK()
	{
		Callback().Call({Napi::Number::New(Env(), iRetScan), Napi::String::New(Env(), scannedData)});
	}

private:
	std::string serialPortName_;
	int mobilePhoneMode_;
	int presentationMode_;
};


void BCSScan (std::string serialPortName, int mobilePhoneMode, int presentationMode, Napi::Function callback)
{
	sigg = false;
	ScanWorker * scanWorker = new ScanWorker(callback, serialPortName, mobilePhoneMode, presentationMode);
	scanWorker->Queue();
}

void BCSCancelScan ()
{
	unsigned char errmsg[6] = {0};
	
	int iRet = BCS_CancelScanCode();
	BCS_Close();
	
	if (iRet == HM_DEV_OK) {
		printf("\n DEBUG: BCS SCAN CANCELED \n");
	} else {
		BCS_GetLastError(errmsg);
		ErrorHandler(iRet, errmsg);
	}
	
	scannedData = "";
	
	sigg = true;
	v.notify_one();
}
