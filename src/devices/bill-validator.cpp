operationResult BAUOpen (const char * serialPortName)
{
	operationResult result;
	unsigned char szVerInfo[10] = {0};
	result.return_int = BAU_Open(serialPortName, szVerInfo);
	result.data = std::string(reinterpret_cast<char const *>(szVerInfo));
	return result;
}

operationResult BAUClose ()
{
	operationResult result;
	BAU_Close();
	return result;
}

operationResult BAUReset ()
{
	operationResult result;
	result.return_int = BAU_Reset();
	return result;
}

operationResult BAUStatus ()
{
	operationResult result;
	BAU_STATUS BauStatus;
	result.return_int = BAU_Status(&BauStatus);
	if (result.return_int == HM_DEV_OK) {
		result.data.reserve(14); // number of fields
		#define getpropinto(propname) result.data.push_back(BauStatus.propname ? '1' : '0')
		/* NOTE: order matters; see ../../bau.js:BAUStatus() */
		getpropinto(bLineStatus);
		getpropinto(bIdling);
		getpropinto(bAccepting);
		getpropinto(bEscrow);
		getpropinto(bStacking);
		getpropinto(bReturning);
		getpropinto(bJammed);
		getpropinto(bStackerFull);
		getpropinto(bCassetteAttached);
		getpropinto(bPaused);
		getpropinto(bCalibration);
		getpropinto(bFailure);
		getpropinto(bPushNoPush);
		getpropinto(bFlashDownload);
		#undef getpropinto
	}
	return result;
}

operationResult BAUSetCapabilities (unsigned char escrow_enabled)
{
	operationResult result;
	unsigned char denominations = BAU_NOTE1|BAU_NOTE2|BAU_NOTE3|BAU_NOTE4|BAU_NOTE5|BAU_NOTE6|BAU_NOTE7;
	int directions = BAU_FOURWAY;
	escrow_enabled = escrow_enabled ? BAU_OKESCROW : BAU_NOESCROW;
	result.return_int = BAU_SetCapabilities(denominations, directions, escrow_enabled);
	return result;
}

operationResult BAUAcceptBill (int mode)
{
	operationResult result;
	int iBillResult = 0;
	result.return_int = BAU_AcceptBill(mode, &iBillResult);
	result.data = std::to_string(iBillResult);
	return result;
}

operationResult BAUCancel ()
{
	operationResult result;
	int iBillResult = 0;
	result.return_int = BAU_Cancel(&iBillResult);
	result.data = std::to_string(iBillResult);
	return result;
}

operationResult BAUStackBill ()
{
	operationResult result;
	result.return_int = BAU_StackBill();
	return result;
}

operationResult BAUReturnBill ()
{
	operationResult result;
	result.return_int = BAU_ReturnBill();
	return result;
}

operationResult BAUSetEnableDenom (char * denominationData)
{
	operationResult result;
	result.return_int = BAU_SetEnableDenom(denominationData);
	return result;
}

operationResult BAUGetSupportCurrency ()
{
	operationResult result;
	char szDenomData[512];
	result.return_int = BAU_GetSupportCurrency(szDenomData);
	result.data = std::string(reinterpret_cast<char const *>(szDenomData));
	return result;
}

operationResult BAUGetLastError ()
{
	operationResult result;
	unsigned char errmsg[6] = {0};
	BAU_GetLastError(errmsg);
	result.data = std::string(reinterpret_cast<char const *>(errmsg));
	return result;
}
