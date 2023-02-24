#include <napi.h>
#include <iostream>
#include <string>

#include "devices/barcode-scanner.hpp"
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

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // set keys on `exports` object
    exports.Set(Napi::String::New(env, "BarcodeScan"), Napi::Function::New(env, BarcodeScan));
    exports.Set(Napi::String::New(env, "BarcodeCancelScan"), Napi::Function::New(env, BarcodeCancelScan));

    // return `exports` object
    return exports;
}

NODE_API_MODULE(genmega, Init);
