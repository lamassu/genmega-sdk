#include "result.hpp"

#ifndef BILL_DISPENSER_HPP
#define BILL_DISPENSER_HPP

operationResult CDUGetLastError();
operationResult CDUOpen(char* serialPortName);
operationResult CDUClose();
operationResult CDUStatus();
operationResult CDUVerifyLicenseKey(char* licenseKey);
operationResult CDUReset(int resetMode);
operationResult CDUSetCassetteNumber(int cassetteNumber);
operationResult CDUDispense(int* dispenseCount, int numberOfCassettesEnabled);
operationResult CDUPresent();
operationResult CDUForceEject();
operationResult CDUShutterAction(int action);

#endif
