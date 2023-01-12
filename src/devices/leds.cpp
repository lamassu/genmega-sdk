#include <iostream>
#include <string>
#include <unistd.h>

#include "genmegadevice/HmDeviceIF.h"
#include "leds.hpp"

void SIUErrorHandler(int iRet) {
    printf("\n DEBUG: SIU FAIL: %d\n", iRet);
    SIU_Close();
}

std::string SIU_LightUp(char* serialPortName, int type, int device) {
    int iRet = 0;
    unsigned char szVerInfo[10];

    // open device serial port
    iRet = SIU_Open(serialPortName, szVerInfo);
    if (iRet != HM_DEV_OK || HM_DEV_ALREADY_OPEN) {
        SIUErrorHandler(iRet);
        return "ERROR: " + std::to_string(iRet);
    }
    iRet = SIU_Flicker(device, type);
    if (iRet != HM_DEV_OK) {
        SIUErrorHandler(iRet);
        return "ERROR: " + std::to_string(iRet);
    }
    return std::to_string(iRet);
}

std::string SIU_LightDown() {
    int iRet = 0;
    // turn down all leds
    iRet = SIU_Reset();
    if (iRet != HM_DEV_OK) {
        SIUErrorHandler(iRet);
        return "ERROR: " + std::to_string(iRet);
    }
    return std::to_string(iRet);
}
