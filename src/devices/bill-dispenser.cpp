#include <iostream>
#include <string>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "bill-dispenser.hpp"

void CDUErrorHandler(int iRet, unsigned char *errmsg) {
    printf("\n DEBUG: CDU FAIL: %d\n", iRet);
    printf(" DEBUG: DEVICE ERROR CODE: %s\n", errmsg);
    CDU_Close();
}

std::string CDU_Status(char* serialPortName) {
    unsigned char errmsg[6] = {0};
    int iRet, resetMode = 0;
    unsigned char szVerInfo[15]={0};

    DISPENSED_RESULT result[6];
	CDU_STATUS CduDisplayStatus;

    std::string result = "";
}

std::string CDU_Init(char* serialPortName, char* licenseKey, char, int cassetteNumber) {
    unsigned char errmsg[6] = {0};
    int iRet = 0;  // Reset mode(0: Normal, 1: Forced)
    unsigned char szVerInfo[15]={0};

    if(strlen(licenseKey) != 15) {
		CDU_GetLastError(errmsg);
        CDUErrorHandler(iRet, errmsg);
        return std::to_string(HM_DEV_NOT_AUTHORIZED);
    }
    iRet = CDU_Verify_LicenseKey(licenseKey);
    if (iRet != HM_DEV_OK) {
        CDU_GetLastError(errmsg);
        CDUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }
    iRet = CDU_Open(serialPortName, OUT szVerInfo);
    if(iRet != HM_DEV_OK ){
		CDU_GetLastError(errmsg);
        CDUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
	}
    // Reject the notes to Reject Bin if the notes are on the feeding path
    // Not checking whether Cassette loaded or not
    // "... CDU_Reset(Forced) => ...retract notes(Forced reset command)."
    iRet = CDU_Reset(resetMode);
    if (iRet != HM_DEV_OK) {
        CDU_GetLastError(errmsg);
        CDUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }
    iRet = CDU_SetCassetteNum(cassetteNumber);
	if (iRet == HM_DEV_OK ) {
        return std::to_string(iRet);
    }
    CDU_GetLastError(errmsg);
    CDUErrorHandler(iRet, errmsg);
    return std::to_string(iRet);
}