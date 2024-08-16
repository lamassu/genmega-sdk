#include "leds.hpp"
#include <genmegadevice/HmDeviceIF.h>

operationResult SIUOpen (const char * serialPortName)
{
	operationResult result;
	unsigned char szVerInfo[10] = {0};
	result.iRet = SIU_Open(serialPortName, szVerInfo);
	result.data = std::string(reinterpret_cast<char const *>(szVerInfo));
	return result;
}

operationResult SIUClose ()
{
	operationResult result;
	SIU_Close();
	return result;
}

operationResult SIUFlicker (int device, int type)
{
	operationResult result;
	result.iRet = SIU_Flicker(device, type);
	return result;
}

operationResult SIUReset() {
	operationResult result;
	result.iRet = SIU_Reset();
	return result;
}
