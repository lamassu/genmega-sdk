#include "result.hpp"

#ifndef BARCODE_SCANNER_HPP
#define BARCODE_SCANNER_HPP

operationResult BCS_Scan(char* serialPortName, int mobilePhoneMode, int presentationMode);
operationResult BCS_CancelScan();

#endif