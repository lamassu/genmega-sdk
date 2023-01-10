#ifndef BILL_DISPENSER_HPP
#define BILL_DISPENSER_HPP

std::string CDU_Init(char* serialPortName, char* licenseKey, char, int cassetteNumber);
std::string CDU_Status(char* serialPortName);
std::string CDU_Dispense(int *dispenseData);

#endif