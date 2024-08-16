
#include <string>

#include <genmegadevice/HmDeviceIF.h>
#include "leds.hpp"

using namespace std;

operationResult SIUOpen(char* serialPortName) {
    unsigned char szVerInfo[10] = {0};
    int iRet = 0;
    operationResult result;

    iRet = SIU_Open(serialPortName, OUT szVerInfo);

    result.data = string (reinterpret_cast<char const *>(szVerInfo));
    result.iRet = iRet;
    return result;
}

operationResult SIUFlicker(int device, int type) {
    int iRet = 0;
    operationResult result;

    iRet = SIU_Flicker(device, type);
    result.iRet = iRet;
    return result;
}

operationResult SIUClose() {
    operationResult result;
    SIU_Close();
    return result;
}

operationResult SIUReset() {
    int iRet = 0;
    operationResult result;

    iRet = SIU_Reset();
    result.iRet = iRet;

    return result;
}
