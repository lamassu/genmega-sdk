#include <iostream>
#include <string>
#include <time.h>

#include "genmegadevice/HmDeviceIF.h"
#include "barcode-scanner.hpp"

struct {
    bool valid = false;
    bool canceled = false;
    BCSScanData *scannedData;
} scannedDataResult;


void ScannedBarcodeData(int iId, int iKind, BCSScanData *BcsScanData) {
    printf("\n DEBUG: BCS BarCode Data: ID-%d, KIND-%d Data:%s\n", iId, iKind, BcsScanData->szCode);
    scannedDataResult.scannedData = BcsScanData;
    scannedDataResult.valid = true;
}

void ErrorHandler(int iRet, unsigned char *errmsg) {
    printf("\n DEBUG: BCS FAIL: %d\n", iRet);
    printf(" DEBUG: DEVICE ERROR CODE: %s\n", errmsg);
    BCS_Close();
}

std::string BCS_Scan(char* serialPortName, int mobilePhoneMode, int presentationMode) {
    // reset scanning variables
    scannedDataResult.valid = false;
    scannedDataResult.canceled = false;

    unsigned char errmsg[6] = {0};
    int iRet = 0;
    time_t StartTime, CurTime;

    BCS_CallBackRegister(ScannedBarcodeData);

    // open device serial port
    iRet = BCS_Open(serialPortName, mobilePhoneMode);

    // initialize device
    iRet = BCS_Reset();

    if (iRet == HM_DEV_OK) {
        printf("\n DEBUG: BCS READY TO SCAN \n");
    } else {
        BCS_GetLastError(errmsg);
        ErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }

    iRet = BCS_AcceptScanCode(presentationMode);

    if (iRet == HM_DEV_OK) {
        time(&StartTime);
        while (1) {
            std::this_thread::yield(); // give priority to other process/threads
            if (scannedDataResult.canceled) {
                iRet = BCS_CancelScanCode();
                BCS_Close();
                // should this return a custom error code informing that the scan was canceled intensionally?
                return std::to_string(iRet);
            }
            time(&CurTime);
            if((StartTime+30) < CurTime){
                printf("30sec Timeout and Cancel\n");
                iRet = BCS_CancelScanCode();
                BCS_Close();
                return std::to_string(iRet);
            }
            if (scannedDataResult.valid && scannedDataResult.scannedData->wSize > 0) {
                iRet = BCS_CancelScanCode();
                break;
            }
        }
    } else {
        BCS_GetLastError(errmsg);
        ErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }

    BCS_Close();

    std::string result(reinterpret_cast<char const *>(scannedDataResult.scannedData->szCode));

    return result;
}

std::string BCS_CancelScan() { 
    int iRet = 0;
    unsigned char errmsg[6] = {0};

    scannedDataResult.canceled = true;
    scannedDataResult.valid = false;

    iRet = BCS_CancelScanCode();
    BCS_Close();

    if (iRet == HM_DEV_OK) {
        printf("\n DEBUG: BCS SCAN CANCELED \n");
    } else {
        BCS_GetLastError(errmsg);
        ErrorHandler(iRet, errmsg);
    }

    return std::to_string(iRet);
}
