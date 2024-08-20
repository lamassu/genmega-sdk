std::string mapDispensedResultToString (DISPENSED_RESULT dispensed)
{
	return std::to_string(dispensed.iDispensedCount)
		+ std::to_string(dispensed.iRejectedCount)
		+ std::to_string(dispensed.iPassedCount)
		+ std::to_string(dispensed.iSkewCount)
		+ std::to_string(dispensed.iAbnormalSpaceCount)
		+ std::to_string(dispensed.iLongCount)
		+ std::to_string(dispensed.iShortCount)
		+ std::to_string(dispensed.iDoubleNoteCount)
		+ std::to_string(dispensed.iHalfSizeCount);
}


operationResult CDUOpen (const char * serialPortName)
{
	operationResult result;
	unsigned char szVerInfo[15] = {0};
	result.iRet = CDU_Open(serialPortName, szVerInfo);
	result.data = std::string(reinterpret_cast<char const *>(szVerInfo));
	return result;
}

operationResult CDUClose ()
{
	operationResult result;
	CDU_Close();
	return result;
}

operationResult CDUReset (int resetMode)
{
	operationResult result;
	result.iRet = CDU_Reset(resetMode);
	return result;
}

operationResult CDUStatus ()
{
	operationResult result;
	CDU_STATUS CduStatus;
	result.iRet = CDU_Status(&CduStatus);
	if (result.iRet == HM_DEV_OK) {
		result.data = std::to_string(CduStatus.iLineStatus)
			+ std::to_string(CduStatus.iCstNum)
			+ std::to_string(CduStatus.iDispenseType)
			+ std::to_string(CduStatus.iJamStatus)
			+ std::to_string(CduStatus.iCst1Status)
			+ std::to_string(CduStatus.iCst2Status)
			+ std::to_string(CduStatus.iCst3Status)
			+ std::to_string(CduStatus.iCst4Status)
			+ std::to_string(CduStatus.iCst5Status)
			+ std::to_string(CduStatus.iCst6Status)
			+ std::to_string(CduStatus.iShutterStatus)
			+ std::to_string(CduStatus.iShutterRemain)
			+ std::to_string(CduStatus.iStackerRemain)
			+ std::to_string(CduStatus.iTransporterRemain);
	}
	return result;
}

operationResult CDUSetCassetteNumber (int cassetteNumber)
{
	operationResult result;
	result.iRet = CDU_SetCassetteNum(cassetteNumber);
	return result;
}

operationResult CDUDispense (int dispenseData[6], int numberOfCassettesEnabled)
{
	operationResult result;
	DISPENSED_RESULT dispensedResult[6];
	result.iRet = CDU_Dispense(dispenseData, dispensedResult);

	result.data = mapDispensedResultToString(dispensedResult[0]);
	for (int i = 1; i < numberOfCassettesEnabled; i++) {
		result.data += ";";
		result.data += mapDispensedResultToString(dispensedResult[i]);
	}

	return result;
}

operationResult CDUPresent ()
{
	operationResult result;
	result.iRet = CDU_Present();
	return result;
}

operationResult CDUShutterAction (int action)
{
	operationResult result;
	result.iRet = CDU_ShutterAction(action);
	return result;
}

operationResult CDURetract ()
{
	operationResult result;
	result.iRet = CDU_Retract();
	return result;
}

operationResult CDUForceEject ()
{
	operationResult result;
	result.iRet = CDU_ForceEject();
	return result;
}

operationResult CDUGetLastError ()
{
	operationResult result;
	unsigned char errmsg[6] = {0};
	CDU_GetLastError(errmsg);
	result.data = std::string(reinterpret_cast<char const *>(errmsg));
	return result;
}

operationResult CDUVerifyLicenseKey (char* licenseKey)
{
	operationResult result;
	result.iRet = CDU_Verify_LicenseKey(licenseKey);
	return result;
}
