#include <iostream>
#include <string>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "bill-validator.hpp"

void BAUErrorHandler(int iRet, unsigned char *errmsg) {
    printf("\n DEBUG: BAU FAIL: %d\n", iRet);
    printf(" DEBUG: DEVICE ERROR CODE: %s\n", errmsg);
    BAU_Close();
}

std::string BAU_Status(char* serialPortName) {
    unsigned char errmsg[6] = {0};
    int iRet = 0;
    unsigned char szVerInfo[10];

    BAU_STATUS BauStatus;
    std::string result = "";

    // open device serial port
    iRet = BAU_Open(serialPortName, OUT szVerInfo);
    if (iRet != HM_DEV_OK || iRet != HM_DEV_ALREADY_OPEN) {
        BAU_GetLastError(errmsg);
        BAUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }
    iRet = BAU_Status(&BauStatus);
    if(iRet == HM_DEV_OK) {
        // TODO: push back all the information or simply try to return the struct and convert it into an object?
        result.push_back(BauStatus.bLineStatus);
        return result;
    } else {
        BAU_GetLastError(errmsg);
        BAUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }
}

std::string BAU_Init(char* serialPortName, char* denominationData) {
    unsigned char errmsg[6] = {0};
    int iRet = 0;
    unsigned char szVerInfo[10];

    // open device serial port
    iRet = BAU_Open(serialPortName, OUT szVerInfo);
    if (iRet != HM_DEV_OK || iRet != HM_DEV_ALREADY_OPEN) {
        BAU_GetLastError(errmsg);
        BAUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }

    // Initialize BAU
    iRet = BAU_Reset();
    if(iRet != HM_DEV_OK) {
        BAU_GetLastError(errmsg);
        BAUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }

    // set new denomination config
    iRet = BAU_SetEnableDenom(denominationData);
    if(iRet == HM_DEV_OK) {
        return std::to_string(iRet);
    } else {
        BAU_GetLastError(errmsg);
        BAUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }
}

std::string BAU_Enable() {
    unsigned char errmsg[6] = {0};
    int iRet = 0;
    int iBillResult = 0;

    iRet = BAU_AcceptBill(SENDONLY, &iBillResult);
    while (1) {
        iRet = BAU_AcceptBill(RECVONLY, &iBillResult);
        if(iRet != HM_DEV_DOING) break;
        usleep(300*1000);  // 300ms
    }
    if ((iBillResult != 0) && (iRet == HM_DEV_OK)) {
        return std::to_string(iBillResult); // needs mapping to the current denom string
    }
    BAU_GetLastError(errmsg);
    BAUErrorHandler(iRet, errmsg);
    BAU_Cancel(&iBillResult);
    return "ERROR: " + std::to_string(iRet);  
}


std::string BAU_Disable() {
    unsigned char errmsg[6] = {0};
    int iRet = 0;
    int iBillResult = 0;

    iRet = BAU_Cancel(&iBillResult);
    if (iRet == HM_DEV_OK) {
        printf("\n DEBUG: BAU BILL ACCEPTANCE DISABLED \n");
        return std::to_string(iRet);
    }
    BAU_GetLastError(errmsg);
    BAUErrorHandler(iRet, errmsg);
    return "ERROR: " + std::to_string(iRet);
    
}

std::string BAU_Reject() {
    unsigned char errmsg[6] = {0};
    int iRet = 0;

    BAU_STATUS BauStatus;
    iRet = BAU_Status(&BauStatus);
    if (iRet == HM_DEV_OK) {
        if (BauStatus.bEscrow) {
            iRet = BAU_ReturnBill();
            if (iRet == HM_DEV_OK) {
                printf("BAU RETURN SUCCESS\n");
                return std::to_string(iRet);
            }
        }
    }
    BAU_GetLastError(errmsg);			
    BAUErrorHandler(iRet, errmsg);
    return "ERROR: " + std::to_string(iRet);

}

std::string BAU_Stack() {
    unsigned char errmsg[6] = {0};
    int iRet = 0;

    BAU_STATUS BauStatus;
    iRet = BAU_Status(&BauStatus);
    if (iRet == HM_DEV_OK) {
        if (BauStatus.bEscrow) {
            iRet = BAU_StackBill();
            if (iRet == HM_DEV_OK) {
                printf("BAU STACK SUCCESS\n");
                return std::to_string(iRet);
            }
        }
    }
    BAU_GetLastError(errmsg);			
    BAUErrorHandler(iRet, errmsg);
    return "ERROR: " + std::to_string(iRet);
}

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
        result.data.push_back(BauStatus.bLineStatus);
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






