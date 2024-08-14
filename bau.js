const genmega = require('./build/Release/genmega.node')

exports.BAUOpen = function BAUOpen(serialPortName) {
    const { iRet, data } = genmega.BAUOpenV2(serialPortName);
    console.log('BAU Firmware Version: ', data);
    if(iRet < 0) console.error('BAU OPEN: ', iRet); 
    return { iRet };
}

exports.BAUClose = function BAUClose() {
    genmega.BAUCloseV2();
}

exports.BAUReset = function BAUReset() {
    const { iRet } = genmega.BAUResetV2();
    if(iRet < 0) console.error('BAU RESET: ', iRet); 
    return { iRet };
}

exports.BAUGetLastError = function BAUGetLastError() {
    const { data } = genmega.BAUGetLastErrorV2();
    return { data };
}


exports.BAUStatus = function BAUStatus() {
    const { iRet, data } = genmega.BAUStatusV2();
    if(iRet < 0) console.error(`BAU STATUS: ${iRet}`);
    if(data === "") console.log(`BAU STATUS EMPTY!`)

    /* NOTE: order matters; see src/devices/bill-validator.cpp:BAUStatus() */
    const [
        bLineStatus,
        bIdling,
        bAccepting,
        bEscrow,
        bStacking,
        bReturning,
        bJammed,
        bStackerFull,
        bCassetteAttached,
        bPaused,
        bCalibration,
        bFailure,
        bPushNoPush,
        bFlashDownload,
    ] = data

    const result = { bLineStatus, bIdling, bAccepting, bEscrow, bStacking, bReturning, bJammed, bStackerFull, bCassetteAttached, bPaused, bCalibration, bFailure, bPushNoPush, bFlashDownload }
    return { iRet, result };
}

exports.BAUSetCapabilities = function BAUSetCapabilities(escrow_enabled) {
    const { iRet } = genmega.BAUSetCapabilitiesV2(escrow_enabled)
    if(iRet < 0) console.error(`BAU SET CAPABILITIES: ${iRet}`);
    return { iRet }
}

exports.BAUSetEnableDenom = function BAUSetEnableDenom(denominationData) {
    const { iRet } = genmega.BAUSetEnableDenomV2(denominationData);
    if(iRet < 0) console.error(`BAU SET ENABLE DENOM: ${iRet}`);
    return { iRet };
}


exports.BAUCancel = function BAUCancel() {
    const { iRet, data } = genmega.BAUCancelV2();
    if(iRet < 0) console.error(`BAU CANCEL BILL: ${iRet}`);
    return { iRet, data };
}

exports.BAUAcceptBill = function BAUAcceptBill(mode) {
    const { iRet, data } = genmega.BAUAcceptBillV2(mode);
    if(iRet < 0) console.error(`BAU ACCEPT BILL: ${iRet}`);
    return { iRet, data }
}

exports.BAUReject = function BAUReject() {
    const { iRet } = genmega.BAUReturnBillV2();
    if(iRet < 0) console.error(`BAU RETURN BILL: ${iRet}`); 
    return { iRet };
}

exports.BAUStack = function BAUStack() {
    const { iRet } = genmega.BAUStackBillV2();
    if(iRet < 0) console.error(`BAU STACK BILL: ${iRet}`); 
    return { iRet };
}

exports.BAUGetSupportCurrency = function BAUGetSupportCurrency() {
    const { iRet, data } = genmega.BAUGetSupportCurrencyV2();
    if(iRet < 0) console.error(`BAU GET SUPPORT CURRENCY: ${iRet}`); 
    return { iRet, data };
}

