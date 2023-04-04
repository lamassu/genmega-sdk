#include <napi.h>

#ifndef BARCODE_SCANNER_HPP
#define BARCODE_SCANNER_HPP

void BCSScan(char* serialPortName, int mobilePhoneMode, int presentationMode, Napi::Function callback);
void BCSCancelScan();

#endif