#include <iostream>
#include <string>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "printer.hpp"

using namespace std;

operationResult RPUGetLastError() {
    unsigned char errmsg[6] = {0};
    operationResult result;

    RPU_GetLastError(errmsg);
    result.data = string (reinterpret_cast<char const *>(errmsg));
    return result;
}

operationResult RPUOpen(char* serialPortName) {
    unsigned char szVerInfo[10];
    int iRet = 0;
    operationResult result;

    iRet = RPU_Open(serialPortName, OUR szVerInfo);

    result.data = string (reinterpret_cast<char const *>(szVerInfo));
    result.iRet = iRet;
    return result; 
}

operationResult RPUClose() {
    operationResult result;
    RPU_Close();
    return result;
}

operationResult RPUStatus () {
    int iRet = 0;
    RPU_STATUS RpuStatus;
    operationResult result;

    iRet = RPU_Status(&RpuStatus);
    result.iRet = iRet;
    if(iRet == HM_DEV_OK) {
        const lineStatus = RpuStatus.LineStatus ? '1' : '0';
        result.data.push_back(lineStatus);
        const paperLoad = RpuStatus.PaperLoad ? '1' : '0';
        result.data.push_back(paperLoad);
        const paperTphLoad = RpuStatus.PaperTphLoad ? '1' : '0';
        result.data.push_back(paperTphLoad);
        const paperNearEnd = RpuStatus.PaperNearEnd ? '1' : '0';
        result.data.push_back(paperNearEnd);
        const tphLever = RpuStatus.TphLever ? '1' : '0';
        result.data.push_back(tphLever);
        const paperJam = RpuStatus.PaperJam ? '1' : '0';
        result.data.push_back(paperJam);
        const cutterHome = RpuStatus.CutterHome ? '1' : '0';
        result.data.push_back(cutterHome);
        const paperNormal = RpuStatus.PaperNormal ? '1' : '0';
        result.data.push_back(paperNormal);
    } else {
        result.data = "";
    }
    return result;
}

operationResult RPUCutPaper () {
    int iRet = 0;
    operationResult result;

    iRet = RPU_CutPaper();
    result.iRet = iRet;
    return result;
}

operationResult RPUPrintText (char* text) {
    int iRet = 0;
    operationResult result;

    iRet = RPU_PrintText(text);
    result.iRet = iRet;
    return result;
}