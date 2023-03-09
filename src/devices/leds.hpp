#include "result.hpp"

#ifndef LEDS_HPP
#define LEDS_HPP

operationResult SIUOpen(char* serialPortName);
operationResult SIUFlicker(int device, int type);
operationResult SIUClose();
operationResult SIUReset();

#endif