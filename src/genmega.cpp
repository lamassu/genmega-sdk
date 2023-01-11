#include <napi.h>
#include <iostream>
#include <string>

#include "devices/barcode-scanner.hpp"
#include "devices/bill-validator.hpp"
#include "devices/bill-dispenser.hpp"


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

Napi::String BillValidatorStack(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BAU_Stack());
}

Napi::String BillValidatorDisable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BAU_Disable());
}

Napi::String BillValidatorReject(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::String::New(env, BAU_Reject());
}

// CDU: Bill Dispenser Unit

Napi::String BillDispenserInit(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    char szLicenseKey[20]={0};
    int cassetteNumber = 0;

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());
    // CDU license key
    std::string licenseKey = (std::string)info[1].ToString();
    strcpy(szLicenseKey, licenseKey.c_str());
    // number of cassettes
    cassetteNumber = info[2].ToNumber();

    return Napi::String::New(env, CDU_Init(szPortName, szLicenseKey, cassetteNumber));
}

Napi::String BillDispenserStatus(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return Napi::String::New(env, CDU_Status(szPortName));
}

Napi::String BillDispenserDispense(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    
    int numberNotesCassetteOne = info[0].ToNumber();
    int numberNotesCassetteTwo = info[1].ToNumber();

    return Napi::String::New(env, CDU_Dispense(numberNotesCassetteOne, numberNotesCassetteTwo));
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
    exports.Set(Napi::String::New(env, "BillDispenserInit"), Napi::Function::New(env, BillDispenserInit));
    exports.Set(Napi::String::New(env, "BillDispenserStatus"), Napi::Function::New(env, BillDispenserStatus));
    exports.Set(Napi::String::New(env, "BillDispenserDispense"), Napi::Function::New(env, BillDispenserDispense));

    // return `exports` object
    return exports;
}

NODE_API_MODULE(genmega, Init);
