#include <iostream>
#include <string>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "printer.hpp"

using namespace std;

operationResult RPUGetLastError() {
    char errmsg[6] = {0};
    operationResult result;

    RPU_GetLastError(errmsg);
    result.data = string (reinterpret_cast<char const *>(errmsg));
    return result;
}

operationResult RPUOpen(char* serialPortName) {
    char szVerInfo[10] = {0};
    int iRet = 0;
    operationResult result;

    iRet = RPU_Open(serialPortName, OUT szVerInfo);

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
        char lineStatus = RpuStatus.LineStatus ? '1' : '0';
        result.data.push_back(lineStatus);
        char paperLoad = RpuStatus.PaperLoad ? '1' : '0';
        result.data.push_back(paperLoad);
        char paperTphLoad = RpuStatus.PaperTphLoad ? '1' : '0';
        result.data.push_back(paperTphLoad);
        char paperNearEnd = RpuStatus.PaperNearEnd ? '1' : '0';
        result.data.push_back(paperNearEnd);
        char tphLever = RpuStatus.TphLever ? '1' : '0';
        result.data.push_back(tphLever);
        char paperJam = RpuStatus.PaperJam ? '1' : '0';
        result.data.push_back(paperJam);
        char cutterHome = RpuStatus.CutterHome ? '1' : '0';
        result.data.push_back(cutterHome);
        char paperNormal = RpuStatus.PaperNormal ? '1' : '0';
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