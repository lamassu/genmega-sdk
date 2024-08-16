#ifndef LEDS_HPP
#define LEDS_HPP

#include "result.hpp"

operationResult SIUOpen (const char * serialPortName);
operationResult SIUClose ();
operationResult SIUFlicker (int device, int type);
operationResult SIUReset ();

#endif
