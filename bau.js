const genmega = require('./build/Release/genmega.node')

exports.open = serialPortName => {
    const { iRet, data } = genmega.BAUOpenV2(serialPortName);
    console.log('BAU Firmware Version: ', data);
    if (iRet < 0) console.error('BAU OPEN: ', iRet);
    return { iRet };
}

exports.close = () => genmega.BAUCloseV2()

exports.reset = () => {
    const { iRet } = genmega.BAUResetV2();
    if (iRet < 0) console.error('BAU RESET: ', iRet);
    return { iRet };
}

exports.getLastError = () => {
    const { data } = genmega.BAUGetLastErrorV2();
    return { data };
}


exports.status = () => {
    const { iRet, data } = genmega.BAUStatusV2();
    if (iRet < 0) console.error(`BAU STATUS: ${iRet}`);
    if (data === "") console.log(`BAU STATUS EMPTY!`)

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

exports.setCapabilities = (escrow_enabled) => {
    const { iRet } = genmega.BAUSetCapabilitiesV2(escrow_enabled)
    if (iRet < 0) console.error(`BAU SET CAPABILITIES: ${iRet}`);
    return { iRet }
}

exports.setEnableDenom = (denominationData) => {
    const { iRet } = genmega.BAUSetEnableDenomV2(denominationData);
    if (iRet < 0) console.error(`BAU SET ENABLE DENOM: ${iRet}`);
    return { iRet };
}


exports.cancel = () => {
    const { iRet, data } = genmega.BAUCancelV2();
    if (iRet < 0) console.error(`BAU CANCEL BILL: ${iRet}`);
    return { iRet, data };
}

exports.acceptBill = mode => {
    const { iRet, data } = genmega.BAUAcceptBillV2(mode);
    if (iRet < 0) console.error(`BAU ACCEPT BILL: ${iRet}`);
    return { iRet, data }
}

exports.reject = () => {
    const { iRet } = genmega.BAUReturnBillV2();
    if (iRet < 0) console.error(`BAU RETURN BILL: ${iRet}`);
    return { iRet };
}

exports.stack = () => {
    const { iRet } = genmega.BAUStackBillV2();
    if (iRet < 0) console.error(`BAU STACK BILL: ${iRet}`);
    return { iRet };
}

exports.getSupportCurrency = () => {
    const { iRet, data } = genmega.BAUGetSupportCurrencyV2();
    if (iRet < 0) console.error(`BAU GET SUPPORT CURRENCY: ${iRet}`);
    return { iRet, data };
}
