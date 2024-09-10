operationResult SIUOpen (const char * serialPortName)
{
	operationResult result;
	unsigned char szVerInfo[10] = {0};
	result.return_int = SIU_Open(serialPortName, szVerInfo);
	result.data = std::string(reinterpret_cast<char const *>(szVerInfo));
	return result;
}

operationResult SIUClose ()
{
	operationResult result;
	SIU_Close();
	return result;
}

operationResult SIUFlicker (int device, int type)
{
	operationResult result;
	result.return_int = SIU_Flicker(device, type);
	return result;
}

operationResult SIUReset() {
	operationResult result;
	result.return_int = SIU_Reset();
	return result;
}
