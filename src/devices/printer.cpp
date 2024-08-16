operationResult RPUOpen (const char * serialPortName)
{
	operationResult result;
	char szVerInfo[10] = {0};
	result.iRet = RPU_Open(serialPortName, szVerInfo);
	result.data = std::string(reinterpret_cast<char const *>(szVerInfo));
	return result;
}

operationResult RPUClose ()
{
	operationResult result;
	RPU_Close();
	return result;
}

operationResult RPUStatus ()
{
	operationResult result;
	RPU_STATUS RpuStatus;
	result.iRet = RPU_Status(&RpuStatus);
	if (result.iRet == HM_DEV_OK) {
		result.data.reserve(8); // number of fields
		#define getpropinto(propname) result.data.push_back(RpuStatus.propname ? '1' : '0')
		getpropinto(LineStatus);
		getpropinto(PaperLoad);
		getpropinto(PaperTphLoad);
		getpropinto(PaperNearEnd);
		getpropinto(TphLever);
		getpropinto(PaperJam);
		getpropinto(CutterHome);
		getpropinto(PaperNormal);
		#undef getpropinto
	}
	return result;
}

operationResult RPUPrintText (char * text)
{
	operationResult result;
	result.iRet = RPU_PrintText(text);
	return result;
}

operationResult RPUCutPaper ()
{
	operationResult result;
	result.iRet = RPU_CutPaper();
	return result;
}

operationResult RPUGetLastError ()
{
	operationResult result;
	char errmsg[10] = {0};
	RPU_GetLastError(errmsg);
	result.data = std::string(reinterpret_cast<char const *>(errmsg));
	return result;
}
