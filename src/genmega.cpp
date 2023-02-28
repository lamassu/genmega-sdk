#include <napi.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "devices/barcode-scanner.hpp"
#include "devices/bill-validator.hpp"
#include "devices/bill-dispenser.hpp"
#include "devices/result.hpp"


Napi::Object mapToNapiObject (operationResult result, Napi::Env env) {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("iRet", result.iRet);
    obj.Set("data", result.data);

    return obj;
}

Napi::Object BarcodeScan(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    int presentationMode = 0, mobilePhoneMode = 0; // presentation mode enables getting barcode data continuously, not interesting for our use case
    
    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    // mobile mode
    mobilePhoneMode = info[1].ToNumber();

    return mapToNapiObject(BCS_Scan(szPortName, mobilePhoneMode, presentationMode), env);
}

Napi::Object BarcodeCancelScan(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BCS_CancelScan(), env);
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

Napi::Object CDUGetLastErrorV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUGetLastError(), env);
}

Napi::Object CDUOpenV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return mapToNapiObject(CDUOpen(szPortName), env);
}

Napi::Object CDUCloseV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUClose(), env);
}

Napi::Object CDUStatusV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUStatus(), env); 
}

Napi::Object CDUVerifyLicenseKeyV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szLicenseKey[20]={0};

    // CDU license key
    std::string licenseKey = (std::string)info[1].ToString();
    strcpy(szLicenseKey, licenseKey.c_str());


    return mapToNapiObject(CDUVerifyLicenseKey(szLicenseKey), env);
}

Napi::Object CDUResetV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int resetMode = info[0].ToNumber();

    return mapToNapiObject(CDUReset(resetMode), env);
}

Napi::Object CDUSetCassetteNumberV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int cassetteNumber = info[0].ToNumber();

    return mapToNapiObject(CDUSetCassetteNumber(cassetteNumber), env);
}

Napi::Object CDUDispenseV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int numberNotesCassetteOne = info[0].ToNumber();
    int numberNotesCassetteTwo = info[1].ToNumber();

    return mapToNapiObject(CDUDispense(numberNotesCassetteOne, numberNotesCassetteTwo), env);
}

Napi::Object CDUPresentV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(CDUPresent(), env);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // set keys on `exports` object
    exports.Set(Napi::String::New(env, "BarcodeScan"), Napi::Function::New(env, BarcodeScan));
    exports.Set(Napi::String::New(env, "BarcodeCancelScan"), Napi::Function::New(env, BarcodeCancelScan));
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
    exports.Set(Napi::String::New(env, "CDUGetLastErrorV2"), Napi::Function::New(env, CDUGetLastErrorV2));
    exports.Set(Napi::String::New(env, "CDUOpenV2"), Napi::Function::New(env, CDUOpenV2));
    exports.Set(Napi::String::New(env, "CDUCloseV2"), Napi::Function::New(env, CDUCloseV2));
    exports.Set(Napi::String::New(env, "CDUStatusV2"), Napi::Function::New(env, CDUStatusV2));
    exports.Set(Napi::String::New(env, "CDUVerifyLicenseKeyV2"), Napi::Function::New(env, CDUVerifyLicenseKeyV2));
    exports.Set(Napi::String::New(env, "CDUResetV2"), Napi::Function::New(env, CDUResetV2));
    exports.Set(Napi::String::New(env, "CDUSetCassetteNumberV2"), Napi::Function::New(env, CDUSetCassetteNumberV2));
    exports.Set(Napi::String::New(env, "CDUDispenseV2"), Napi::Function::New(env, CDUDispenseV2));
    exports.Set(Napi::String::New(env, "CDUPresentV2"), Napi::Function::New(env, CDUPresentV2));

    // return `exports` object
    return exports;
}

NODE_API_MODULE(genmega, Init);
