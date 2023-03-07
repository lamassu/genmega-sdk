#include "result.hpp"

#ifndef PRINTER_HPP
#define PRINTER_HPP

operationResult RPUGetLastError();
operationResult RPUOpen(char* serialPortName);
operationResult RPUClose();
operationResult RPUStatus();
operationResult RPUCutPaper();
operationResult RPUPrintText(char* text);

#endif
