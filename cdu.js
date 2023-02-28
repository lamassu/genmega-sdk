//TODO: rewrite in js

const _ = require('lodash/fp')
const genmega = require('./build/Release/genmega.node')

void CDUErrorHandler(int iRet, unsigned char *errmsg) {
    CDU_GetLastError(errmsg);
    printf("\n DEBUG: CDU FAIL: %d\n", iRet);
    printf(" DEBUG: DEVICE ERROR CODE: %s\n", errmsg);
    CDU_Close();
}

std::string CDU_Status(char* serialPortName) {
    unsigned char errmsg[6] = {0};
    int iRet = 0;
    unsigned char szVerInfo[15]={0};

	CDU_STATUS CduDisplayStatus;

    std::string result = "";

    // open device serial port
    iRet = CDU_Open(serialPortName, szVerInfo);
    if (iRet != HM_DEV_OK || HM_DEV_ALREADY_OPEN) {
        CDUErrorHandler(iRet, errmsg);
        return std::to_string(iRet);
    }
    iRet = CDU_Status(&CduDisplayStatus);
    if(iRet == HM_DEV_OK) {
        // TODO: push back all the information or simply try to return the struct and convert it into an object?
        result.push_back(CduDisplayStatus.iLineStatus);
        return result;
    } else {
        CDUErrorHandler(iRet, errmsg);
        return "ERROR: " + std::to_string(iRet);
    }
}


std::string CDU_Dispense(int numberNotesCassetteOne, int numberNotesCassetteTwo) {
    unsigned char errmsg[6] = {0};
    int iRet = 0;
    int dispenseData[6] = {0};
	DISPENSED_RESULT result[6];
	CDU_STATUS CduDisplayStatus;

    dispenseData[0] = numberNotesCassetteOne;
    dispenseData[1] = numberNotesCassetteTwo;

    iRet = CDU_Dispense(dispenseData, result);
    if (iRet != HM_DEV_OK ) {
        printf("CDU DISPENSE FAIL\n");
        CDUErrorHandler(iRet, errmsg);
        return "ERROR: " + std::to_string(iRet);
    }
    iRet = CDU_Status(&CduDisplayStatus);
    if (iRet == HM_DEV_OK && CduDisplayStatus.iDispenseType == PRESENT_TYPE) {
        iRet = CDU_Present();
        if (iRet == HM_DEV_OK) {
            CDU_Close();
            return std::to_string(iRet);
        }
    }
    CDUErrorHandler(iRet, errmsg);
    return "ERROR: " + std::to_string(iRet);
}

std::string CDU_Init(char* serialPortName, char* licenseKey, int cassetteNumber) {
    unsigned char errmsg[6] = {0};
    int iRet = 0, resetMode = 0;  // Reset mode(0: Normal, 1: Forced)
    unsigned char szVerInfo[15]={0};

    if(strlen(licenseKey) != 15) {
        CDUErrorHandler(iRet, errmsg);
        return "ERROR: " + std::to_string(HM_DEV_NOT_AUTHORIZED);
    }
    iRet = CDU_Verify_LicenseKey(licenseKey);
    if (iRet != HM_DEV_OK) {
        CDUErrorHandler(iRet, errmsg);
        return "ERROR: " + std::to_string(iRet);
    }
    iRet = CDU_Open(serialPortName, OUT szVerInfo);
    if(iRet != HM_DEV_OK ){
        CDUErrorHandler(iRet, errmsg);
        return "ERROR: " + std::to_string(iRet);
	}
    // Reject the notes to Reject Bin if the notes are on the feeding path
    // Not checking whether Cassette loaded or not
    // "... CDU_Reset(Forced) => ...retract notes(Forced reset command)."
    iRet = CDU_Reset(resetMode);
    if (iRet != HM_DEV_OK) {
        CDUErrorHandler(iRet, errmsg);
        return "ERROR: " + std::to_string(iRet);
    }
    iRet = CDU_SetCassetteNum(cassetteNumber);
	if (iRet == HM_DEV_OK ) {
        return std::to_string(iRet);
    }
    CDUErrorHandler(iRet, errmsg);
    return "ERROR: " + std::to_string(iRet);
}