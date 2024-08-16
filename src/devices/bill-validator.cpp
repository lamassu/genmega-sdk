#include "bill-validator.hpp"

#include <genmegadevice/HmDeviceIF.h>

operationResult BAUOpen (const char * serialPortName)
{
	unsigned char szVerInfo[11] = {0};
	operationResult result;
	result.iRet = BAU_Open(serialPortName, szVerInfo);
	result.data = std::string(reinterpret_cast<char const *>(szVerInfo));
	return result;
}

operationResult BAUClose ()
{
	operationResult result;
	BAU_Close();
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

operationResult BAUStatus() {
    int iRet = 0;
    BAU_STATUS BauStatus;
    operationResult result;

    iRet = BAU_Status(&BauStatus);
    result.iRet = iRet;
    if(iRet == HM_DEV_OK) {
#define getpropinto(propname)  result.data.push_back(BauStatus.propname ? '1' : '0')
        /* NOTE: order matters; see ../../bau.js:BAUStatus() */
        getpropinto(bLineStatus);
        getpropinto(bIdling);
        getpropinto(bAccepting);
        getpropinto(bEscrow);
        getpropinto(bStacking);
        getpropinto(bReturning);
        getpropinto(bJammed);
        getpropinto(bStackerFull);
        getpropinto(bCassetteAttached);
        getpropinto(bPaused);
        getpropinto(bCalibration);
        getpropinto(bFailure);
        getpropinto(bPushNoPush);
        getpropinto(bFlashDownload);
#undef getpropinto
    } else {
        result.data = "";
    }
    return result;
}

operationResult BAUSetCapabilities(unsigned char escrow_enabled) {
    operationResult result;
    // TODO: get denominations and directions as arguments?
    unsigned char denominations = BAU_NOTE1|BAU_NOTE2|BAU_NOTE3|BAU_NOTE4|BAU_NOTE5|BAU_NOTE6|BAU_NOTE7;
    int directions = BAU_ONEWAY;
    result.iRet = BAU_SetCapabilities(denominations, directions, escrow_enabled);
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

operationResult BAUStackBill() {
    int iRet = 0;
    operationResult result;

    iRet = BAU_StackBill();
    result.iRet = iRet;
    result.data = "";
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

operationResult BAUSetEnableDenom(char* denominationData) {
    int iRet = 0;
    operationResult result;

    iRet = BAU_SetEnableDenom(denominationData);
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

operationResult BAUGetLastError() {
    unsigned char errmsg[6] = {0};
    operationResult result;

    BAU_GetLastError(errmsg);
    result.data = std::string (reinterpret_cast<char const *>(errmsg));
    return result;
}
