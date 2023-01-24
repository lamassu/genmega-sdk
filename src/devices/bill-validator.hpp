#ifndef BILL_VALIDATOR_HPP
#define BILL_VALIDATOR_HPP

struct operationResult {
    int iRet;
    std::string data;
};

std::string BAU_Status(char* serialPortName);
std::string BAU_Enable();
std::string BAU_Disable();
std::string BAU_Stack();
std::string BAU_Reject();
std::string BAU_Init(char* serialPortName, char* denominationData);
operationResult BAUGetLastError();
operationResult BAUOpen(char* serialPortName);
operationResult BAUClose();
operationResult BAUStatus();
operationResult BAUSetEnableDenom(char* denominationData);
operationResult BAUAcceptBill(int mode);
operationResult BAUCancel();
operationResult BAUReturnBill();
operationResult BAUStackBill();

#endif