#include "result.hpp"

#ifndef BILL_VALIDATOR_HPP
#define BILL_VALIDATOR_HPP

operationResult BAUGetLastError();
operationResult BAUOpen(char* serialPortName);
operationResult BAUReset();
operationResult BAUClose();
operationResult BAUStatus();
operationResult BAUSetEnableDenom(char* denominationData);
operationResult BAUAcceptBill(int mode);
operationResult BAUCancel();
operationResult BAUReturnBill();
operationResult BAUStackBill();
operationResult BAUGetSupportCurrency();

#endif
