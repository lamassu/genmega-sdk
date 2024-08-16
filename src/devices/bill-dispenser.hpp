#ifndef BILL_DISPENSER_HPP
#define BILL_DISPENSER_HPP

#include "result.hpp"

operationResult CDUOpen (const char * serialPortName);
operationResult CDUClose ();
operationResult CDUReset (int resetMode);
operationResult CDUStatus ();
operationResult CDUSetCassetteNumber (int cassetteNumber);
operationResult CDUDispense (int dispenseCount[6], int numberOfCassettesEnabled);
operationResult CDUPresent ();
operationResult CDUShutterAction (int action);
operationResult CDUForceEject ();
operationResult CDUGetLastError ();
operationResult CDUVerifyLicenseKey (char * licenseKey); // TODO(siiky): make sure licenseKey has the required minimum size

#endif
