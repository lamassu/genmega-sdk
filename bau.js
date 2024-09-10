const genmega = require('./build/Release/genmega.node')

exports.open = serialPortName => {
    const { return_int, data } = genmega.BAUOpenV2(serialPortName);
    console.log('BAU Firmware Version: ', data);
    if (return_int < 0) console.error('BAU OPEN: ', return_int);
    return { return_int };
}

exports.close = () => genmega.BAUCloseV2()

exports.reset = () => {
    const { return_int } = genmega.BAUResetV2();
    if (return_int < 0) console.error('BAU RESET: ', return_int);
    return { return_int };
}

exports.getLastError = () => {
    const { data } = genmega.BAUGetLastErrorV2();
    return { data };
}


exports.status = () => {
    const { return_int, data } = genmega.BAUStatusV2();
    if (return_int < 0) console.error(`BAU STATUS: ${return_int}`);
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
    return { return_int, result };
}

exports.setCapabilities = (escrow_enabled) => {
    const { return_int } = genmega.BAUSetCapabilitiesV2(escrow_enabled)
    if (return_int < 0) console.error(`BAU SET CAPABILITIES: ${return_int}`);
    return { return_int }
}

exports.setEnableDenom = (denominationData) => {
    const { return_int } = genmega.BAUSetEnableDenomV2(denominationData);
    if (return_int < 0) console.error(`BAU SET ENABLE DENOM: ${return_int}`);
    return { return_int };
}


exports.cancel = () => {
    const { return_int, data } = genmega.BAUCancelV2();
    if (return_int < 0) console.error(`BAU CANCEL BILL: ${return_int}`);
    return { return_int, data };
}

exports.acceptBill = mode => {
    const { return_int, data } = genmega.BAUAcceptBillV2(mode);
    if (return_int < 0) console.error(`BAU ACCEPT BILL: ${return_int}`);
    return { return_int, data }
}

exports.reject = () => {
    const { return_int } = genmega.BAUReturnBillV2();
    if (return_int < 0) console.error(`BAU RETURN BILL: ${return_int}`);
    return { return_int };
}

exports.stack = () => {
    const { return_int } = genmega.BAUStackBillV2();
    if (return_int < 0) console.error(`BAU STACK BILL: ${return_int}`);
    return { return_int };
}

exports.getSupportCurrency = () => {
    const { return_int, data } = genmega.BAUGetSupportCurrencyV2();
    if (return_int < 0) console.error(`BAU GET SUPPORT CURRENCY: ${return_int}`);
    return { return_int, data };
}
