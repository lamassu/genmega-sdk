#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

static std::atomic<bool> _bcs_stop;
static std::mutex _bcs_m;
static std::condition_variable _bcs_scan_con;
static std::string _bcs_data;
static int _bcs_return_int = 0;


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

#define literal_array_length(arr) (sizeof(arr)/sizeof((arr)[0]))

struct operationResult BCSGetInfo (std::string serialPortName)
{
	struct operationResult ret;
	const char * where = "";

	// TODO remove this magic number (contacted GenMega, waiting)
	unsigned char deviceInfor[1025] = {0};

	ret.return_int = BCS_Open(serialPortName.c_str(), 0);
	if (ret.return_int != HM_DEV_OK) {
		where = "BCS_Open";
		goto error;
	}

	ret.return_int = BCS_GetInfor(deviceInfor);
	if (ret.return_int != HM_DEV_OK) {
		where = "BCS_GetInfor";
		goto error;
	}
	deviceInfor[literal_array_length(deviceInfor)-1] = '\0';
	ret.data = std::string(reinterpret_cast<const char*>(deviceInfor), literal_array_length(deviceInfor));

	BCS_Close();

	return ret;

error:
	unsigned char errmsg[7] = {0};
	BCS_GetLastError(errmsg);
	errmsg[literal_array_length(errmsg)-1] = '\0';
	fprintf(stderr, "GM DEBUG: BCS FAIL (%d) at %s: %s\n", ret.return_int, where, errmsg);
	BCS_Close();
	return ret;
}

bool StartScan (std::string serialPortName, int mobilePhoneMode, char presentationMode, std::vector<std::string> extensions)
{
	_bcs_data = std::string("");
	_bcs_return_int = 0;
	const char * where = "";

	const uint32_t nextensions = extensions.size();
	unsigned char * extension = nullptr;

	BCS_CallBackRegister(ScannedBarcodeDataCallBack);

	_bcs_return_int = BCS_Open(serialPortName.c_str(), mobilePhoneMode);
	if (_bcs_return_int != HM_DEV_OK) {
		where = "BCS_Open";
		goto error;
	}

	_bcs_return_int = BCS_Reset();
	if (_bcs_return_int != HM_DEV_OK) {
		where = "BCS_Reset";
		goto error;
	}

	for (uint32_t i = 0; i < nextensions; i++) {
		extension = reinterpret_cast<unsigned char *>(const_cast<char *>(extensions[i].c_str()));
		_bcs_return_int = BCS_SetCommand(extension);
		if (_bcs_return_int != HM_DEV_OK) {
			where = "BCS_SetCommand";
			goto error;
		}
	}
	extension = nullptr;

	_bcs_return_int = BCS_AcceptScanCode(presentationMode);
	if (_bcs_return_int != HM_DEV_OK) {
		where = "BCS_AcceptScanCode";
		goto error;
	}

	fprintf(stderr, "\n DEBUG: BCS READY TO SCAN \n");
	return true;

error:
	unsigned char errmsg[7] = {0};
	BCS_GetLastError(errmsg);
	errmsg[literal_array_length(errmsg)-1] = '\0';
	fprintf(stderr, "GM DEBUG: BCS FAIL (%d) at %s: %s\n", _bcs_return_int, where, errmsg);
	BCS_Close();
	return false;
}

struct _BCS_ScanWorker : public Napi::AsyncWorker
{
public:
	_BCS_ScanWorker(Napi::Function& callback, std::string serialPortName, int mobilePhoneMode, char presentationMode, std::vector<std::string> extensions) :
		Napi::AsyncWorker(callback),
		serialPortName(serialPortName),
		mobilePhoneMode(mobilePhoneMode),
		presentationMode(presentationMode),
		extensions(extensions)
	{}

	~_BCS_ScanWorker() {}

	void Execute() override
	{
		std::unique_lock<std::mutex> lock(_bcs_m);
		if (!StartScan(serialPortName, mobilePhoneMode, presentationMode, extensions))
			return;

		/*
		 * "pred can be optionally provided to detect spurious wakeup."
		 * https://en.cppreference.com/w/cpp/thread/condition_variable/wait
		 */
		_bcs_scan_con.wait(lock, _bcs_stop_pred);
		BCS_Close();
	}

	void OnOK()
	{
		Callback().Call({Napi::Number::New(Env(), _bcs_return_int), Napi::String::New(Env(), _bcs_data)});
	}

private:
	std::string serialPortName;
	int mobilePhoneMode;
	int presentationMode;
	std::vector<std::string> extensions;
};

void BCSCancelScan ()
{
	BCS_CancelScanCode();
	_bcs_stop = true;
	_bcs_return_int = HM_DEV_CANCEL;
	_bcs_data = std::string("");
	_bcs_scan_con.notify_all();
}

void BCSScan (std::string serialPortName, int mobilePhoneMode, char presentationMode, std::vector<std::string> extensions, Napi::Function callback)
{
	_bcs_stop = false;
	_BCS_ScanWorker * _bcs_scanWorker = new _BCS_ScanWorker(callback, serialPortName, mobilePhoneMode, presentationMode, extensions);
	_bcs_scanWorker->Queue();
}
