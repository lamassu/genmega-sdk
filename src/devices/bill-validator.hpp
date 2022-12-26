#ifndef BILL_VALIDATOR_HPP
#define BILL_VALIDATOR_HPP

std::string BAU_Status(char* serialPortName);
std::string BAU_Enable(int iBillResult);
std::string BAU_Disable();
std::string BAU_Stack();
std::string BAU_Reject();
std::string BAU_Init(char* serialPortName, char* denominationData);

#endif