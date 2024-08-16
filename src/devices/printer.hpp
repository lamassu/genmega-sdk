#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "result.hpp"

operationResult RPUOpen (const char * serialPortName);
operationResult RPUClose ();
operationResult RPUStatus ();
operationResult RPUPrintText (char * text);
operationResult RPUCutPaper ();
operationResult RPUGetLastError ();

#endif
