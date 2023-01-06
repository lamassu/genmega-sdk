#ifndef BILL_DISPENSER_HPP
#define BILL_DISPENSER_HPP

std::string CDU_Init(char* serialPortName, char* cassetteData);
std::string CDU_Status(char* serialPortName);
std::string CDU_Dispense();

#endif