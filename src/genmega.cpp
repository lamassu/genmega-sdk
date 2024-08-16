#include <napi.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "devices/result.hpp"
#include "devices/barcode-scanner.hpp"
#include "devices/bill-validator.hpp"
#include "devices/bill-dispenser.hpp"
#include "devices/printer.hpp"
#include "devices/leds.hpp"

Napi::Object mapToNapiObject (operationResult result, const Napi::CallbackInfo &info)
{
	Napi::Object obj = Napi::Object::New(info.Env());
	obj.Set("iRet", result.iRet);
	obj.Set("data", result.data);
	return obj;
}

Napi::Value _BCSScan (const Napi::CallbackInfo &info)
{
	std::string serialPortName = info[0].ToString();
	int mobilePhoneMode = info[1].ToNumber();
	int presentationMode = 0; // presentation mode enables getting barcode data continuously, not interesting for our use case
	Napi::Function callback = info[2].As<Napi::Function>();
	BCSScan(serialPortName, mobilePhoneMode, presentationMode, callback);
	return info.Env().Undefined();
}

Napi::Value _BCSCancelScan (const Napi::CallbackInfo &info)
{
	BCSCancelScan();
	return info.Env().Undefined();
}

// BAU new v2

Napi::Object BAUGetLastErrorV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUGetLastError(), info);
}

Napi::Object BAUOpenV2 (const Napi::CallbackInfo &info)
{
	std::string serialPortName = info[0].ToString();
	return mapToNapiObject(BAUOpen(serialPortName.c_str()), info);
}

Napi::Object BAUResetV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUReset(), info);
}

Napi::Object BAUCloseV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUClose(), info);
}

Napi::Object BAUStatusV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUStatus(), info);
}

Napi::Object BAUSetCapabilitiesV2 (const Napi::CallbackInfo &info)
{
	unsigned char escrow_enabled = info[0].ToBoolean().Value();
	return mapToNapiObject(BAUSetCapabilities(escrow_enabled), info);
}

Napi::Object BAUSetEnableDenomV2 (const Napi::CallbackInfo &info)
{
	std::string denominationData = info[0].ToString();
	char * szSetData = new char [denominationData.length() + 1];
	std::strcpy(szSetData, denominationData.c_str());
	Napi::Object ret = mapToNapiObject(BAUSetEnableDenom(szSetData), info);
	delete[] szSetData;
	return ret;
}

Napi::Object BAUAcceptBillV2 (const Napi::CallbackInfo &info)
{
	int acceptMode = info[0].ToNumber();
	return mapToNapiObject(BAUAcceptBill(acceptMode), info);
}

Napi::Object BAUCancelV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUCancel(), info);
}

Napi::Object BAUReturnBillV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUReturnBill(), info);
}

Napi::Object BAUStackBillV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUStackBill(), info);
}

Napi::Object BAUGetSupportCurrencyV2 (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(BAUGetSupportCurrency(), info);
}

// CDU new v2

Napi::Object _CDUGetLastError (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(CDUGetLastError(), info);
}

Napi::Object _CDUOpen (const Napi::CallbackInfo &info)
{
	std::string serialPortName = info[0].ToString();
	return mapToNapiObject(CDUOpen(serialPortName.c_str()), info);
}

Napi::Object _CDUClose (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(CDUClose(), info);
}

Napi::Object _CDUStatus (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(CDUStatus(), info);
}

Napi::Object _CDUVerifyLicenseKey (const Napi::CallbackInfo &info)
{
	std::string licenseKey = info[0].ToString();
	char * szLicenseKey = new char [licenseKey.length() + 1];
	std::strcpy(szLicenseKey, licenseKey.c_str());
	Napi::Object ret = mapToNapiObject(CDUVerifyLicenseKey(szLicenseKey), info);
	delete[] szLicenseKey;
	return ret;
}

Napi::Object _CDUReset (const Napi::CallbackInfo &info)
{
	int resetMode = info[0].ToNumber();
	return mapToNapiObject(CDUReset(resetMode), info);
}

Napi::Object _CDUSetCassetteNumber (const Napi::CallbackInfo &info)
{
	int cassetteNumber = info[0].ToNumber();
	return mapToNapiObject(CDUSetCassetteNumber(cassetteNumber), info);
}

Napi::Object _CDUDispense (const Napi::CallbackInfo &info)
{
	Napi::Array dispenseCountArray = info[0].As<Napi::Array>();
	int numberOfCassettesEnabled = info[1].ToNumber();

	int dispenseCount[6] = {0};
	int len = dispenseCountArray.Length();
	for (int i = 0; i < len; i++)
		dispenseCount[i] = dispenseCountArray.Get(i).ToNumber();

	return mapToNapiObject(CDUDispense(dispenseCount, numberOfCassettesEnabled), info);
}

Napi::Object _CDUPresent (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(CDUPresent(), info);
}

Napi::Object _CDUForceEject (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(CDUForceEject(), info);
}

Napi::Object _CDUShutterAction (const Napi::CallbackInfo &info)
{
	int action = info[0].ToNumber();
	return mapToNapiObject(CDUShutterAction(action), info);
}

// RPU

Napi::Object _RPUGetLastError (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(RPUGetLastError(), info);
}

Napi::Object _RPUOpen (const Napi::CallbackInfo &info)
{
	std::string serialPortName = info[0].ToString();
	return mapToNapiObject(RPUOpen(serialPortName.c_str()), info);
}

Napi::Object _RPUClose (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(RPUClose(), info);
}

Napi::Object _RPUStatus (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(RPUStatus(), info);
}

Napi::Object _RPUCutPaper (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(RPUCutPaper(), info);
}

Napi::Object _RPUPrintText (const Napi::CallbackInfo &info)
{
	Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();

	const size_t length = buffer.Length();
	char * textContent = new char [length + 1];
	std::memcpy(textContent, buffer.Data(), length);
	textContent[length] = '\0';
	Napi::Object ret = mapToNapiObject(RPUPrintText(textContent), info);
	delete[] textContent;
	return ret;
}

// SIU

Napi::Object _SIUOpen (const Napi::CallbackInfo &info)
{
	std::string serialPortName = info[0].ToString();
	return mapToNapiObject(SIUOpen(serialPortName.c_str()), info);
}

Napi::Object _SIUFlicker (const Napi::CallbackInfo &info)
{
	int device = info[0].ToNumber();
	int actionType = info[1].ToNumber();
	return mapToNapiObject(SIUFlicker(device, actionType), info);
}

Napi::Object _SIUClose (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(SIUClose(), info);
}

Napi::Object _SIUReset (const Napi::CallbackInfo &info)
{
	return mapToNapiObject(SIUReset(), info);
}


Napi::Object Init (Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "_BCSScan"), Napi::Function::New(env, _BCSScan));
	exports.Set(Napi::String::New(env, "_BCSCancelScan"), Napi::Function::New(env, _BCSCancelScan));
	exports.Set(Napi::String::New(env, "BAUGetLastErrorV2"), Napi::Function::New(env, BAUGetLastErrorV2));
	exports.Set(Napi::String::New(env, "BAUOpenV2"), Napi::Function::New(env, BAUOpenV2));
	exports.Set(Napi::String::New(env, "BAUResetV2"), Napi::Function::New(env, BAUResetV2));
	exports.Set(Napi::String::New(env, "BAUCloseV2"), Napi::Function::New(env, BAUCloseV2));
	exports.Set(Napi::String::New(env, "BAUStatusV2"), Napi::Function::New(env, BAUStatusV2));
	exports.Set(Napi::String::New(env, "BAUSetCapabilitiesV2"), Napi::Function::New(env, BAUSetCapabilitiesV2));
	exports.Set(Napi::String::New(env, "BAUSetEnableDenomV2"), Napi::Function::New(env, BAUSetEnableDenomV2));
	exports.Set(Napi::String::New(env, "BAUAcceptBillV2"), Napi::Function::New(env, BAUAcceptBillV2));
	exports.Set(Napi::String::New(env, "BAUCancelV2"), Napi::Function::New(env, BAUCancelV2));
	exports.Set(Napi::String::New(env, "BAUReturnBillV2"), Napi::Function::New(env, BAUReturnBillV2));
	exports.Set(Napi::String::New(env, "BAUStackBillV2"), Napi::Function::New(env, BAUStackBillV2));
	exports.Set(Napi::String::New(env, "BAUGetSupportCurrencyV2"), Napi::Function::New(env, BAUGetSupportCurrencyV2));
	exports.Set(Napi::String::New(env, "_CDUGetLastError"), Napi::Function::New(env, _CDUGetLastError));
	exports.Set(Napi::String::New(env, "_CDUOpen"), Napi::Function::New(env, _CDUOpen));
	exports.Set(Napi::String::New(env, "_CDUClose"), Napi::Function::New(env, _CDUClose));
	exports.Set(Napi::String::New(env, "_CDUStatus"), Napi::Function::New(env, _CDUStatus));
	exports.Set(Napi::String::New(env, "_CDUVerifyLicenseKey"), Napi::Function::New(env, _CDUVerifyLicenseKey));
	exports.Set(Napi::String::New(env, "_CDUReset"), Napi::Function::New(env, _CDUReset));
	exports.Set(Napi::String::New(env, "_CDUSetCassetteNumber"), Napi::Function::New(env, _CDUSetCassetteNumber));
	exports.Set(Napi::String::New(env, "_CDUDispense"), Napi::Function::New(env, _CDUDispense));
	exports.Set(Napi::String::New(env, "_CDUPresent"), Napi::Function::New(env, _CDUPresent));
	exports.Set(Napi::String::New(env, "_CDUForceEject"), Napi::Function::New(env, _CDUForceEject));
	exports.Set(Napi::String::New(env, "_CDUShutterAction"), Napi::Function::New(env, _CDUShutterAction));
	exports.Set(Napi::String::New(env, "_RPUGetLastError"), Napi::Function::New(env, _RPUGetLastError));
	exports.Set(Napi::String::New(env, "_RPUOpen"), Napi::Function::New(env, _RPUOpen));
	exports.Set(Napi::String::New(env, "_RPUClose"), Napi::Function::New(env, _RPUClose));
	exports.Set(Napi::String::New(env, "_RPUStatus"), Napi::Function::New(env, _RPUStatus));
	exports.Set(Napi::String::New(env, "_RPUCutPaper"), Napi::Function::New(env, _RPUCutPaper));
	exports.Set(Napi::String::New(env, "_RPUPrintText"), Napi::Function::New(env, _RPUPrintText));
	exports.Set(Napi::String::New(env, "_SIUOpen"), Napi::Function::New(env, _SIUOpen));
	exports.Set(Napi::String::New(env, "_SIUFlicker"), Napi::Function::New(env, _SIUFlicker));
	exports.Set(Napi::String::New(env, "_SIUClose"), Napi::Function::New(env, _SIUClose));
	exports.Set(Napi::String::New(env, "_SIUReset"), Napi::Function::New(env, _SIUReset));
	return exports;
}

NODE_API_MODULE(genmega, Init);
