#ifndef BARCODE_SCANNER_HPP
#define BARCODE_SCANNER_HPP

std::string BCS_Scan(char* serialPortName, int mobilePhoneMode, int presentationMode);
std::string BCS_CancelScan();

#endif