#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "bill-dispenser.hpp"

operationResult CDUGetLastError() {
    unsigned char errmsg[6] = {0};
    operationResult result;

    CDU_GetLastError(errmsg);
    result.data = std::string (reinterpret_cast<char const *>(errmsg));
    return result;
}

operationResult CDUOpen(char* serialPortName) {
    unsigned char szVerInfo[10];
    int iRet = 0;
    operationResult result;

    iRet = CDU_Open(serialPortName, OUT szVerInfo);

    result.data = std::string (reinterpret_cast<char const *>(szVerInfo));
    result.iRet = iRet;
    return result;
}

operationResult CDUClose() {
    operationResult result;

    CDU_Close();
    result.data = "";
    return result;
}

operationResult CDUStatus() {
    int iRet = 0;
    CDU_STATUS CduStatus;
    operationResult result;

    iRet = CDU_Status(&CduStatus);
    result.iRet = iRet;
    if(iRet == HM_DEV_OK) {
        char iLineStatus = to_string(CduStatus.iLineStatus);
        result.data.push_back(iLineStatus);
        char iCstNum = to_string(CduStatus.iCstNum);
        result.data.push_back(iCstNum);
        char iDispenseType = to_string(CduStatus.iDispenseType);
        result.data.push_back(iDispenseType);
        char iJamStatus = to_string(CduStatus.iJamStatus);
        result.data.push_back(iJamStatus);
        char iCst1Status = to_string(CduStatus.iCst1Status);
        result.data.push_back(iCst1Status);
        char iCst2Status = to_string(CduStatus.iCst2Status);
        result.data.push_back(iCst2Status);
        char iCst3Status = to_string(CduStatus.iCst3Status);
        result.data.push_back(iCst3Status);
        char iCst4Status = to_string(CduStatus.iCst4Status);
        result.data.push_back(iCst4Status);
        char iCst5Status = to_string(CduStatus.iCst5Status);
        result.data.push_back(iCst5Status);
        char iCst6Status = to_string(CduStatus.iCst6Status);
        result.data.push_back(iCst6Status);
        char iShutterStatus = to_string(CduStatus.iShutterStatus);
        result.data.push_back(iShutterStatus);
        char iShutterRemain = to_string(CduStatus.iShutterRemain);
        result.data.push_back(iShutterRemain);
        char iStackerRemain = to_string(CduStatus.iStackerRemain);
        result.data.push_back(iStackerRemain);
        char iTransporterRemain = to_string(CduStatus.iTransporterRemain);
        result.data.push_back(iTransporterRemain);
    } else {
        result.data = "";
    }
    return result;
}

operationResult CDUVerifyLicenseKey(char* licenseKey) {
    int iRet = 0;
    operationResult result;

    iRet = CDU_Verify_LicenseKey(licenseKey);
    result.iRet = iRet;
    result.data = "";

    return result;
}

operationResult CDUReset(int resetMode) {
    int iRet = 0;
    operationResult result;

    iRet = CDU_Reset(resetMode);
    result.iRet = iRet;
    result.data = "";

    return result;
}

operationResult CDUSetCassetteNumber(int cassetteNumber) {
    int iRet = 0;
    operationResult result;

    iRet = CDU_SetCassetteNum(cassetteNumber);
    result.iRet = iRet;
    result.data = "";

    return result;
}

operationResult CDUDispense(int numberNotesCassetteOne, int numberNotesCassetteTwo) {
    int iRet = 0;
    int dispenseData[6] = {0};
	DISPENSED_RESULT dispensedResult[6];
    operationResult result;

    dispenseData[0] = numberNotesCassetteOne;
    dispenseData[1] = numberNotesCassetteTwo;

    iRet = CDU_Dispense(dispenseData, dispensedResult);
    result.iRet = iRet;
    //TODO: map dispensed result to data
    result.data = "";

    return result;
}

operationResult CDUPresent() {
    int iRet = 0;
    operationResult result;

    iRet = CDU_Present();
    result.iRet = iRet;
    result.data = "";

    return result;
}