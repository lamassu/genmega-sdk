#include <napi.h>
#include <iostream>
#include <string>

#include "devices/barcode-scanner.hpp"


// BCS: Barcode Scanner

Napi::String BarcodeScan(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    int presentationMode = 0, mobilePhoneMode = 0; // presentation mode enables getting barcode data continuously, not interesting for our use case
    
    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    // mobile mode
    mobilePhoneMode = info[1].ToNumber();

    return Napi::String::New(env, BCS_Scan(szPortName, mobilePhoneMode, presentationMode));
}

Napi::String BarcodeCancelScan(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BCS_CancelScan());
}


// BAU: Bill Acceptor Unit

Napi::String BillValidatorStatus(const Napi::CallbackInfo &info) { 
    Napi::Env env = info.Env();

    char szPortName[128];

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return Napi::String::New(env, BAU_Status(szPortName));
}

Napi::String BillValidatorInit(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    char szSetData[512];

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());
    // currency and denomination data
    std::string denominationData = (std::string)info[1].ToString();
    strcpy(szSetData, denominationData.c_str());

    return Napi::String::New(env, BAU_Init(szPortName, szSetData));
}

Napi::String BillValidatorEnable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int iBillResult = 0;
    return Napi::String::New(env, BAU_Enable(iBillResult));
}

Napi::String BillValidatorStack() {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BAU_Stack());
}

Napi::String BillValidatorDisable() {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BAU_Disable());
}

Napi::String BillValidatorReject() {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BAU_Reject());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // set keys on `exports` object
    exports.Set(Napi::String::New(env, "BarcodeScan"), Napi::Function::New(env, BarcodeScan));
    exports.Set(Napi::String::New(env, "BarcodeCancelScan"), Napi::Function::New(env, BarcodeCancelScan));
    exports.Set(Napi::String::New(env, "BillValidatorStatus"), Napi::Function::New(env, BillValidatorStatus));
    exports.Set(Napi::String::New(env, "BillValidatorInit"), Napi::Function::New(env, BillValidatorInit));
    exports.Set(Napi::String::New(env, "BillValidatorEnable"), Napi::Function::New(env, BillValidatorEnable));
    exports.Set(Napi::String::New(env, "BillValidatorStack"), Napi::Function::New(env, BillValidatorStack));
    exports.Set(Napi::String::New(env, "BillValidatorDisable"), Napi::Function::New(env, BillValidatorDisable));
    exports.Set(Napi::String::New(env, "BillValidatorReject"), Napi::Function::New(env, BillValidatorReject));

    // return `exports` object
    return exports;
}

NODE_API_MODULE(genmega, Init);
