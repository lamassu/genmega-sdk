#include <iostream>
#include <string>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "bill-validator.hpp"

operationResult BAUGetLastError() {
    unsigned char errmsg[6] = {0};
    operationResult result;

    BAU_GetLastError(errmsg);
    result.data = std::string (reinterpret_cast<char const *>(errmsg));
    return result;
}

operationResult BAUOpen(char* serialPortName) {
    unsigned char szVerInfo[10];
    int iRet = 0;
    operationResult result;

    iRet = BAU_Open(serialPortName, OUT szVerInfo);
   
    result.data = std::string (reinterpret_cast<char const *>(szVerInfo));
    result.iRet = iRet;
    return result;
}

operationResult BAUReset() {
    int iRet = 0;
    operationResult result;

    iRet = BAU_Reset();
    result.iRet = iRet;
    result.data = "";
    return result;
}

operationResult BAUClose() {
    operationResult result;

    BAU_Close();
    result.data = "";
    return result;
}

operationResult BAUStatus() {
    int iRet = 0;
    BAU_STATUS BauStatus;
    operationResult result;

    iRet = BAU_Status(&BauStatus);
    result.iRet = iRet;
    if(iRet == HM_DEV_OK) {
        char bLineStatus = BauStatus.bLineStatus ? '1' : '0';
        result.data.push_back(bLineStatus);
        char bIdling = BauStatus.bIdling ? '1' : '0';
        result.data.push_back(bIdling);
        char bAccepting = BauStatus.bAccepting ? '1' : '0';
        result.data.push_back(bAccepting);
        char bEscrow = BauStatus.bEscrow ? '1' : '0';
        result.data.push_back(bEscrow);
        char bStacking = BauStatus.bStacking ? '1' : '0';
        result.data.push_back(bStacking);
        char bReturning = BauStatus.bReturning ? '1' : '0';
        result.data.push_back(bReturning);
        char bJammed = BauStatus.bJammed ? '1' : '0';
        result.data.push_back(bJammed);
        char bStackerFull = BauStatus.bStackerFull ? '1' : '0';
        result.data.push_back(bStackerFull);
        char bCassetteAttached = BauStatus.bCassetteAttached ? '1' : '0';
        result.data.push_back(bCassetteAttached);
        char bPaused = BauStatus.bPaused ? '1' : '0';
        result.data.push_back(bPaused);
        char bCalibration = BauStatus.bCalibration ? '1' : '0';
        result.data.push_back(bCalibration);
        char bFailure = BauStatus.bFailure ? '1' : '0';
        result.data.push_back(bFailure);
        char bPushNoPush = BauStatus.bPushNoPush ? '1' : '0';
        result.data.push_back(bPushNoPush);
        char bFlashDownload = BauStatus.bFlashDownload ? '1' : '0';
        result.data.push_back(bFlashDownload);
    } else {
        result.data = "";
    }
    return result;
}

operationResult BAUSetEnableDenom(char* denominationData) {
    int iRet = 0;
    operationResult result;

    iRet = BAU_SetEnableDenom(denominationData);
    result.iRet = iRet;
    result.data = "";
    return result;
}

operationResult BAUAcceptBill(int mode) {
    int iRet = 0;
    int iBillResult;
    operationResult result;

    iRet = BAU_AcceptBill(mode, &iBillResult);
    result.iRet = iRet;
    result.data = std::to_string(iBillResult);
    return result;
}


operationResult BAUCancel() {
    int iRet = 0;
    int iBillResult;
    operationResult result;

    iRet = BAU_Cancel(&iBillResult);
    result.iRet = iRet;
    result.data = std::to_string(iBillResult);
    return result;
}


operationResult BAUReturnBill() {
    int iRet = 0;
    operationResult result;

    iRet = BAU_ReturnBill();
    result.iRet = iRet;
    result.data = "";
    return result;
}

operationResult BAUStackBill() {
    int iRet = 0;
    operationResult result;

    iRet = BAU_StackBill();
    result.iRet = iRet;
    result.data = "";
    return result;
}

operationResult BAUGetSupportCurrency() {
    int iRet = 0;
    char szDenomData[512];
    operationResult result;

    iRet = BAU_GetSupportCurrency(szDenomData);
    result.iRet = iRet;
    result.data = szDenomData;
    return result;
}






