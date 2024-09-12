#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

static std::atomic<bool> _bcs_stop;
static std::mutex _bcs_m;
static std::condition_variable _bcs_scan_con;
static std::string _bcs_data;
static int _bcs_iRet = 0;


static bool _bcs_stop_pred ()
{
	return _bcs_stop;
}

void ScannedBarcodeDataCallBack (int iId, int iKind, BCSScanData * BcsScanData)
{
	std::unique_lock<std::mutex> lock(_bcs_m);

	char * data = new char [BcsScanData->wSize + 1];
	std::memcpy(data, BcsScanData->szCode, BcsScanData->wSize);
	data[BcsScanData->wSize] = '\0';
	fprintf(stderr, "\n DEBUG: BCS BarCode Data: ID-%d, KIND-%d Data:%s\n", iId, iKind, data);
	_bcs_data = std::string(reinterpret_cast<char const *>(data));
	delete[] data;

	_bcs_stop = true;
	_bcs_scan_con.notify_all();
}

void StartScan (std::string serialPortName, int mobilePhoneMode, char presentationMode)
{
	_bcs_data = std::string("");
	_bcs_iRet = 0;
	const char * where = "";

	BCS_CallBackRegister(ScannedBarcodeDataCallBack);

	_bcs_iRet = BCS_Open(serialPortName.c_str(), mobilePhoneMode);
	if (_bcs_iRet != HM_DEV_OK) {
		where = "BCS_Open";
		goto error;
	}

	_bcs_iRet = BCS_Reset();
	if (_bcs_iRet != HM_DEV_OK) {
		where = "BCS_Reset";
		goto error;
	}

	_bcs_iRet = BCS_AcceptScanCode(presentationMode);
	if (_bcs_iRet != HM_DEV_OK) {
		where = "BCS_AcceptScanCode";
		goto error;
	}

	fprintf(stderr, "\n DEBUG: BCS READY TO SCAN \n");
	return;

error:
	unsigned char errmsg[6] = {0};
	BCS_GetLastError(errmsg);
	fprintf(stderr, "GM DEBUG: BCS FAIL (%d) at %s: %s\n", _bcs_iRet, where, errmsg);
	BCS_Close();
}

struct _BCS_ScanWorker : public Napi::AsyncWorker
{
public:
	_BCS_ScanWorker(Napi::Function& callback, std::string serialPortName, int mobilePhoneMode, char presentationMode)
		: Napi::AsyncWorker(callback), serialPortName(serialPortName), mobilePhoneMode(mobilePhoneMode), presentationMode(presentationMode) {}
	~_BCS_ScanWorker() {}

	void Execute() override
	{
		std::unique_lock<std::mutex> lock(_bcs_m);
		StartScan(serialPortName, mobilePhoneMode, presentationMode);

		/*
		 * "pred can be optionally provided to detect spurious wakeup."
		 * https://en.cppreference.com/w/cpp/thread/condition_variable/wait
		 */
		_bcs_scan_con.wait(lock, _bcs_stop_pred);
		BCS_Close();
	}

	void OnOK()
	{
		Callback().Call({Napi::Number::New(Env(), _bcs_iRet), Napi::String::New(Env(), _bcs_data)});
	}

private:
	std::string serialPortName;
	int mobilePhoneMode;
	int presentationMode;
};

void BCSCancelScan ()
{
	BCS_CancelScanCode();
	BCS_Close();
	_bcs_stop = true;
	_bcs_iRet = HM_DEV_CANCEL;
	_bcs_data = std::string("");
	_bcs_scan_con.notify_all();
}

void BCSScan (std::string serialPortName, int mobilePhoneMode, char presentationMode, Napi::Function callback)
{
	_bcs_stop = false;
	_BCS_ScanWorker * _bcs_scanWorker = new _BCS_ScanWorker(callback, serialPortName, mobilePhoneMode, presentationMode);
	_bcs_scanWorker->Queue();
}
