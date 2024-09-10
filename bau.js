const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.open = serialPortName => {
    const { return_int, data } = genmega.BAUOpenV2(serialPortName);
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    console.log('BAU Firmware Version: ', data);
    if (return_int < 0) console.error('BAU OPEN: ', return_int);
    return { return_int, return_code, return_message };
}

exports.close = () => genmega.BAUCloseV2()

exports.reset = () => {
    const { return_int } = genmega.BAUResetV2();
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU RESET: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message };
}

exports.getLastError = () => {
    const { data } = genmega.BAUGetLastErrorV2();
    return data
}


exports.status = () => {
    const { return_int, data } = genmega.BAUStatusV2();
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU STATUS: ${return_code} (${return_int}): ${return_message}`)
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
    return { return_int, return_code, return_message, result };
}

exports.setCapabilities = (escrow_enabled) => {
    const { return_int } = genmega.BAUSetCapabilitiesV2(escrow_enabled)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU SET CAPABILITIES: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.setEnableDenom = (denominationData) => {
    const { return_int } = genmega.BAUSetEnableDenomV2(denominationData);
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU SET ENABLE DENOM: ${return_code} (${return_int}): ${return_message}`);
    return { return_int, return_code, return_message }
}


exports.cancel = () => {
    const { return_int, data } = genmega.BAUCancelV2();
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU CANCEL BILL: ${return_code} (${return_int}): ${return_message}`);
    return { return_int, return_code, return_message, data }
}

exports.acceptBill = mode => {
    const { return_int, data } = genmega.BAUAcceptBillV2(mode);
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU ACCEPT BILL: ${return_code} (${return_int}): ${return_message}`);
    return { return_int, return_code, return_message, data }
}

exports.reject = () => {
    const { return_int } = genmega.BAUReturnBillV2();
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU RETURN BILL: ${return_code} (${return_int}): ${return_message}`);
    return { return_int, return_code, return_message }
}

exports.stack = () => {
    const { return_int } = genmega.BAUStackBillV2();
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU STACK BILL: ${return_code} (${return_int}): ${return_message}`);
    return { return_int, return_code, return_message }
}

exports.getSupportCurrency = () => {
    const { return_int, data } = genmega.BAUGetSupportCurrencyV2();
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`BAU GET SUPPORT CURRENCY: ${return_code} (${return_int}): ${return_message}`);
    return { return_int, return_code, return_message, data }
}
