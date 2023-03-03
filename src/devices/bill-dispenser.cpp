#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "bill-dispenser.hpp"

using namespace std;

operationResult CDUGetLastError() {
    unsigned char errmsg[6] = {0};
    operationResult result;

    CDU_GetLastError(errmsg);
    result.data = string (reinterpret_cast<char const *>(errmsg));
    return result;
}

operationResult CDUOpen(char* serialPortName) {
    unsigned char szVerInfo[10];
    int iRet = 0;
    operationResult result;

    iRet = CDU_Open(serialPortName, OUT szVerInfo);

    result.data = string (reinterpret_cast<char const *>(szVerInfo));
    result.iRet = iRet;
    return result;
}

operationResult CDUClose() {
    operationResult result;
    CDU_Close();
    return result;
}

operationResult CDUStatus() {
    int iRet = 0;
    CDU_STATUS CduStatus;
    operationResult result;

    iRet = CDU_Status(&CduStatus);
    result.iRet = iRet;
    if(iRet == HM_DEV_OK) {
        result.data + to_string(CduStatus.iLineStatus);
        result.data + to_string(CduStatus.iCstNum);
        result.data + to_string(CduStatus.iDispenseType);
        result.data + to_string(CduStatus.iJamStatus);
        result.data + to_string(CduStatus.iCst1Status);
        result.data + to_string(CduStatus.iCst2Status);
        result.data + to_string(CduStatus.iCst3Status);
        result.data + to_string(CduStatus.iCst4Status);
        result.data + to_string(CduStatus.iCst5Status);
        result.data + to_string(CduStatus.iCst6Status);
        result.data + to_string(CduStatus.iShutterStatus);
        result.data + to_string(CduStatus.iShutterRemain);
        result.data + to_string(CduStatus.iStackerRemain);
        result.data + to_string(CduStatus.iTransporterRemain);
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

    return result;
}

operationResult CDUReset(int resetMode) {
    int iRet = 0;
    operationResult result;

    iRet = CDU_Reset(resetMode);
    result.iRet = iRet;

    return result;
}

operationResult CDUSetCassetteNumber(int cassetteNumber) {
    int iRet = 0;
    operationResult result;

    iRet = CDU_SetCassetteNum(cassetteNumber);
    result.iRet = iRet;

    return result;
}

string mapDispensedResultToString(DISPENSED_RESULT dispensed) {
    string result = "";
    result + to_string(dispensed.iDispensedCount);
    result + to_string(dispensed.iRejectedCount);
    result + to_string(dispensed.iPassedCount);
    result + to_string(dispensed.iSkewCount);
    result + to_string(dispensed.iAbnormalSpaceCount);
    result + to_string(dispensed.iLongCount);
    result + to_string(dispensed.iShortCount);
    result + to_string(dispensed.iDoubleNoteCount);
    result + to_string(dispensed.iHalfSizeCount);
    return result;
}

operationResult CDUDispense(int* dispenseData, int numberOfCassettesEnabled) {
    int iRet = 0;
	DISPENSED_RESULT dispensedResult[6];
    operationResult result;

    iRet = CDU_Dispense(dispenseData, dispensedResult);
    result.iRet = iRet;

    for(int i = 0; i < numberOfCassettesEnabled; i++) {
        result.data + mapDispensedResultToString(dispensedResult[i]);
        if ((i+1) < numberOfCassettesEnabled) {
            result.data + ";";
        }
    }
    
    return result;
}

operationResult CDUPresent() {
    int iRet = 0;
    operationResult result;

    iRet = CDU_Present();
    result.iRet = iRet;

    return result;
}

operationResult CDUForceEject() {
    int iRet = 0;
    operationResult result;

    iRet = CDU_ForceEject();
    result.iRet = iRet;

    return result;
}

operationResult CDUShutterAction(int action) {
    int iRet = 0;
    operationResult result;

    iRet = CDU_ShutterAction(action);
    result.iRet = iRet;

    return result;
}