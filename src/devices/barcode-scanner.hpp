#ifndef BARCODE_SCANNER_HPP
#define BARCODE_SCANNER_HPP

#include <napi.h>

void BCSScan (std::string serialPortName, int mobilePhoneMode, int presentationMode, Napi::Function callback);
void BCSCancelScan ();

#endif
