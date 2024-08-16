#include <string>

#include <genmegadevice/HmDeviceIF.h>
#include "bill-dispenser.hpp"

std::string mapDispensedResultToString (DISPENSED_RESULT dispensed)
{
    std::string result = "";
    result = std::to_string(dispensed.iDispensedCount)
        + std::to_string(dispensed.iRejectedCount)
        + std::to_string(dispensed.iPassedCount)
        + std::to_string(dispensed.iSkewCount)
        + std::to_string(dispensed.iAbnormalSpaceCount)
        + std::to_string(dispensed.iLongCount)
        + std::to_string(dispensed.iShortCount)
        + std::to_string(dispensed.iDoubleNoteCount)
        + std::to_string(dispensed.iHalfSizeCount);
    return result;
}


operationResult CDUOpen (char* serialPortName)
{
    unsigned char szVerInfo[15] = {0};
    int iRet = 0;
    operationResult result;

    iRet = CDU_Open(serialPortName, OUT szVerInfo);

    result.data = std::string (reinterpret_cast<char const *>(szVerInfo));
    result.iRet = iRet;
    return result;
}

operationResult CDUClose ()
{
    operationResult result;
    CDU_Close();
    return result;
}

operationResult CDUReset (int resetMode)
{
    int iRet = 0;
    operationResult result;

    iRet = CDU_Reset(resetMode);
    result.iRet = iRet;

    return result;
}

operationResult CDUStatus ()
{
    int iRet = 0;
    CDU_STATUS CduStatus;
    operationResult result;

    iRet = CDU_Status(&CduStatus);
    result.iRet = iRet;
    if (iRet == HM_DEV_OK) {
        result.data = std::to_string(CduStatus.iLineStatus)
            + std::to_string(CduStatus.iCstNum)
            + std::to_string(CduStatus.iDispenseType)
            + std::to_string(CduStatus.iJamStatus)
            + std::to_string(CduStatus.iCst1Status)
            + std::to_string(CduStatus.iCst2Status)
            + std::to_string(CduStatus.iCst3Status)
            + std::to_string(CduStatus.iCst4Status)
            + std::to_string(CduStatus.iCst5Status)
            + std::to_string(CduStatus.iCst6Status)
            + std::to_string(CduStatus.iShutterStatus)
            + std::to_string(CduStatus.iShutterRemain)
            + std::to_string(CduStatus.iStackerRemain)
            + std::to_string(CduStatus.iTransporterRemain);
    } else {
        result.data = "";
    }
    return result;
}

operationResult CDUSetCassetteNumber (int cassetteNumber)
{
    int iRet = 0;
    operationResult result;

    iRet = CDU_SetCassetteNum(cassetteNumber);
    result.iRet = iRet;

    return result;
}

operationResult CDUDispense (int* dispenseData, int numberOfCassettesEnabled)
{
    int iRet = 0;
	DISPENSED_RESULT dispensedResult[6];
    operationResult result;

    iRet = CDU_Dispense(dispenseData, dispensedResult);
    result.iRet = iRet;

    for (int i = 0; i < numberOfCassettesEnabled; i++) {
        result.data += mapDispensedResultToString(dispensedResult[i]);
        if ((i+1) < numberOfCassettesEnabled) {
            result.data += ";";
        }
    }
    
    return result;
}

operationResult CDUPresent ()
{
    int iRet = 0;
    operationResult result;

    iRet = CDU_Present();
    result.iRet = iRet;

    return result;
}

operationResult CDUShutterAction (int action)
{
    int iRet = 0;
    operationResult result;

    iRet = CDU_ShutterAction(action);
    result.iRet = iRet;

    return result;
}

operationResult CDUForceEject ()
{
    int iRet = 0;
    operationResult result;

    iRet = CDU_ForceEject();
    result.iRet = iRet;

    return result;
}

operationResult CDUGetLastError ()
{
    unsigned char errmsg[6] = {0};
    operationResult result;

    CDU_GetLastError(errmsg);
    result.data = std::string (reinterpret_cast<char const *>(errmsg));
    return result;
}

operationResult CDUVerifyLicenseKey (char* licenseKey)
{
    int iRet = 0;
    operationResult result;

    iRet = CDU_Verify_LicenseKey(licenseKey);
    result.iRet = iRet;

    return result;
}
