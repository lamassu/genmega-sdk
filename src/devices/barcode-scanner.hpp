#include <napi.h>

#ifndef BARCODE_SCANNER_HPP
#define BARCODE_SCANNER_HPP

void BCSScan(std::string serialPortName, int mobilePhoneMode, int presentationMode, Napi::Function callback);
void BCSCancelScan();

#endif