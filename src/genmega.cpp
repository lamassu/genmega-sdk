#include <napi.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "devices/barcode-scanner.hpp"
#include "devices/bill-validator.hpp"
#include "devices/bill-dispenser.hpp"
#include "devices/printer.hpp"
#include "devices/leds.hpp"
#include "devices/result.hpp"


Napi::Object mapToNapiObject (operationResult result, Napi::Env env) {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("iRet", result.iRet);
    obj.Set("data", result.data);

    return obj;
}

Napi::Value _BCSScan(const Napi::CallbackInfo &info) {

    char szPortName[128];
    int presentationMode = 0, mobilePhoneMode = 0; // presentation mode enables getting barcode data continuously, not interesting for our use case
    
    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    // mobile mode
    mobilePhoneMode = info[1].ToNumber();

    // scan callback
    Napi::Function callback = info[2].As<Napi::Function>();
    
    BCSScan(szPortName, mobilePhoneMode, presentationMode, callback);

    return info.Env().Undefined();
}

Napi::Value _BCSCancelScan(const Napi::CallbackInfo &info) {

    BCSCancelScan();
    return info.Env().Undefined();
}


// BAU new v2

Napi::Object BAUGetLastErrorV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    
    return mapToNapiObject(BAUGetLastError(), env);
}

Napi::Object BAUOpenV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return mapToNapiObject(BAUOpen(szPortName), env);
}

Napi::Object BAUResetV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUReset(), env);
}

Napi::Object BAUCloseV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUClose(), env);
}

Napi::Object BAUStatusV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUStatus(), env);
}

Napi::Object BAUSetEnableDenomV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szSetData[512];

    // currency and denomination data
    std::string denominationData = (std::string)info[0].ToString();
    strcpy(szSetData, denominationData.c_str());

    return mapToNapiObject(BAUSetEnableDenom(szSetData), env);
}

Napi::Object BAUAcceptBillV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int acceptMode = info[0].ToNumber();

    return mapToNapiObject(BAUAcceptBill(acceptMode), env);
}

Napi::Object BAUCancelV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUCancel(), env);
}

Napi::Object BAUReturnBillV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUReturnBill(), env);
}

Napi::Object BAUStackBillV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUStackBill(), env);
}

Napi::Object BAUGetSupportCurrencyV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUGetSupportCurrency(), env);
}

// CDU new v2

Napi::Object _CDUGetLastError(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUGetLastError(), env);
}

Napi::Object _CDUOpen(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128] = {0};

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return mapToNapiObject(CDUOpen(szPortName), env);
}

Napi::Object _CDUClose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUClose(), env);
}

Napi::Object _CDUStatus(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUStatus(), env); 
}

Napi::Object _CDUVerifyLicenseKey(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szLicenseKey[16] = {0};

    // CDU license key
    std::string licenseKey = (std::string)info[0].ToString();
    strcpy(szLicenseKey, licenseKey.c_str());


    return mapToNapiObject(CDUVerifyLicenseKey(szLicenseKey), env);
}

Napi::Object _CDUReset(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int resetMode = info[0].ToNumber();

    return mapToNapiObject(CDUReset(resetMode), env);
}

Napi::Object _CDUSetCassetteNumber(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int cassetteNumber = info[0].ToNumber();

    return mapToNapiObject(CDUSetCassetteNumber(cassetteNumber), env);
}

Napi::Object _CDUDispense(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int dispenseCount[6] = {0};

    Napi::Array dispenseCountArray = info[0].As<Napi::Array>();
    int len = dispenseCountArray.Length();
    for (int i = 0; i < len; i++) {
        dispenseCount[i] = dispenseCountArray.Get(i).ToNumber();
    }

    int numberOfCassettesEnabled = info[1].ToNumber();

    return mapToNapiObject(CDUDispense(dispenseCount, numberOfCassettesEnabled), env);
}

Napi::Object _CDUPresent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUPresent(), env);
}

Napi::Object _CDUForceEject(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUForceEject(), env);
}

Napi::Object _CDUShutterAction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int action = info[0].ToNumber();

    return mapToNapiObject(CDUShutterAction(action), env);
}

// RPU

Napi::Object _RPUGetLastError(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    
    return mapToNapiObject(RPUGetLastError(), env);
}

Napi::Object _RPUOpen(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return mapToNapiObject(RPUOpen(szPortName), env);
}

Napi::Object _RPUClose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(RPUClose(), env);
}

Napi::Object _RPUStatus(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(RPUStatus(), env); 
}

Napi::Object _RPUCutPaper(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(RPUCutPaper(), env); 
}

Napi::Object _RPUPrintText(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
    char* data = buffer.Data();
    const size_t length = buffer.Length();
    char textContent[length+1];

    for(size_t i = 0; i < length; i++) {
        textContent[i] = data[i];
    }

    textContent[length] = '\0';

    return mapToNapiObject(RPUPrintText(textContent), env); 
}

// SIU

Napi::Object _SIUOpen(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return mapToNapiObject(SIUOpen(szPortName), env);
}

Napi::Object _SIUFlicker(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int device = info[0].ToNumber();
    int actionType = info[1].ToNumber();

    return mapToNapiObject(SIUFlicker(device, actionType), env);
}

Napi::Object _SIUClose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(SIUClose(), env);
}

Napi::Object _SIUReset(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(SIUReset(), env);
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // set keys on `exports` object
    exports.Set(Napi::String::New(env, "_BCSScan"), Napi::Function::New(env, _BCSScan));
    exports.Set(Napi::String::New(env, "_BCSCancelScan"), Napi::Function::New(env, _BCSCancelScan));
    exports.Set(Napi::String::New(env, "BAUGetLastErrorV2"), Napi::Function::New(env, BAUGetLastErrorV2));
    exports.Set(Napi::String::New(env, "BAUOpenV2"), Napi::Function::New(env, BAUOpenV2));
    exports.Set(Napi::String::New(env, "BAUResetV2"), Napi::Function::New(env, BAUResetV2));
    exports.Set(Napi::String::New(env, "BAUCloseV2"), Napi::Function::New(env, BAUCloseV2));
    exports.Set(Napi::String::New(env, "BAUStatusV2"), Napi::Function::New(env, BAUStatusV2));
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

    // return `exports` object
    return exports;
}

NODE_API_MODULE(genmega, Init);
