#ifndef BILL_VALIDATOR_HPP
#define BILL_VALIDATOR_HPP

#include "result.hpp"

operationResult BAUOpen (const char * serialPortName);
operationResult BAUClose ();
operationResult BAUReset();
operationResult BAUStatus();
operationResult BAUSetCapabilities(unsigned char escrow_enabled);
operationResult BAUAcceptBill(int mode);
operationResult BAUCancel();
operationResult BAUStackBill();
operationResult BAUReturnBill();
operationResult BAUSetEnableDenom(char* denominationData);
operationResult BAUGetSupportCurrency();
operationResult BAUGetLastError();

#endif
