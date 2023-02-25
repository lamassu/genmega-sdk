#include <iostream>
#include <string>
#include <thread>
#include <time.h>

#include "genmegadevice/HmDeviceIF.h"
#include "barcode-scanner.hpp"

struct {
    bool valid = false;
    bool canceled = false;
    BCSScanData scannedData;
} scannedDataResult;


void ScannedBarcodeData(int iId, int iKind, BCSScanData *BcsScanData) {
    printf("\n DEBUG: BCS BarCode Data: ID-%d, KIND-%d Data:%s\n", iId, iKind, BcsScanData->szCode);
    scannedDataResult.scannedData = *BcsScanData;
    scannedDataResult.valid = true;
}

void ErrorHandler(int iRet, unsigned char *errmsg) {
    printf("\n DEBUG: BCS FAIL: %d\n", iRet);
    printf(" DEBUG: DEVICE ERROR CODE: %s\n", errmsg);
    BCS_Close();
}

operationResult BCS_Scan(char* serialPortName, int mobilePhoneMode, int presentationMode) {
    // reset scanning variables
    scannedDataResult.valid = false;
    scannedDataResult.canceled = false;

    unsigned char errmsg[6] = {0};
    int iRet = 0;
    time_t StartTime, CurTime;

    operationResult result;

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
        result.iRet = iRet;
        result.data = "";
        return result;
    }

    iRet = BCS_AcceptScanCode(presentationMode);

    if (iRet == HM_DEV_OK) {
        time(&StartTime);
        while (1) {
            std::this_thread::yield(); // give priority to other process/threads
            if (scannedDataResult.canceled) {
                iRet = BCS_CancelScanCode();
                BCS_Close();
                result.iRet = iRet;
                result.data = "";
                return result;
            }
            time(&CurTime);
            if((StartTime+30) < CurTime){
                printf("30sec Timeout and Cancel\n");
                iRet = BCS_CancelScanCode();
                BCS_Close();
                result.iRet = iRet;
                result.data = "";
                return result;
            }
            if (scannedDataResult.valid && scannedDataResult.scannedData.wSize > 0) {
                iRet = BCS_CancelScanCode();
                break;
            }
        }
    } else {
        BCS_GetLastError(errmsg);
        ErrorHandler(iRet, errmsg);
        result.iRet = iRet;
        result.data = "";
        return result;
    }

    BCS_Close();

    std::string scanResult(reinterpret_cast<char const *>(scannedDataResult.scannedData.szCode));
    result.data = scanResult;
    result.iRet = iRet;

    return result;
}

operationResult BCS_CancelScan() { 
    int iRet = 0;
    unsigned char errmsg[6] = {0};

    operationResult result;

    scannedDataResult.canceled = true;
    scannedDataResult.valid = false;

    iRet = BCS_CancelScanCode();
    BCS_Close();

    result.iRet = iRet;
    result.data = "";

    if (iRet == HM_DEV_OK) {
        printf("\n DEBUG: BCS SCAN CANCELED \n");
    } else {
        BCS_GetLastError(errmsg);
        ErrorHandler(iRet, errmsg);
    }

    return result;
}