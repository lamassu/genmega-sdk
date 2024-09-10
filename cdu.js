const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.getLastError = () => {
    const { data } = genmega._BAUGetLastError()
    return data
}

exports.open = serialPortName => {
    const { return_int, data } = genmega._CDUOpen(serialPortName)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    console.log('CDU Firmware Version: ', data)
    if (return_int < 0) console.error(`CDU OPEN: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.close = () => genmega._CDUClose()

exports.status = () => {
    const { return_int, data } = genmega._CDUStatus()
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU STATUS: ${return_code} (${return_int}): ${return_message}`)
    if (data === "") console.log(`CDU STATUS EMPTY!`)
    const [
      iLineStatus,
      iCstNum,
      iDispenseType,
      iJamStatus,
      iCst1Status,
      iCst2Status,
      iCst3Status,
      iCst4Status,
      iCst5Status,
      iCst6Status,
      iShutterStatus,
      iShutterRemain,
      iStackerRemain,
      iTransporterRemain,
    ] = data
    const statuses = { iLineStatus, iCstNum, iDispenseType, iJamStatus, iCst1Status, iCst2Status, iCst3Status, iCst4Status, iCst5Status, iCst6Status, iShutterStatus, iShutterRemain, iStackerRemain, iTransporterRemain }
    return { return_int, return_code, return_message, statuses }
}

exports.verifyLicenseKey = licenseKey => {
    const { return_int } = genmega._CDUVerifyLicenseKey(licenseKey)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU VERIFY LICENSE KEY: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.reset = resetMode => {
    const { return_int } = genmega._CDUReset(resetMode)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU RESET: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.setCassetteNumber = cassetteNumber => {
    const { return_int } = genmega._CDUSetCassetteNumber(cassetteNumber)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU SET CASSETTE NUMBER: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.dispense = (dispenseData, numberOfCassettesEnabled) => {
    dispenseData = [0, 1, 2, 3, 4, 5].map(idx => dispenseData[idx] ?? 0)
    if (numberOfCassettesEnabled > dispenseData.length) numberOfCassettesEnabled = dispenseData.length
    const { return_int, data } = genmega._CDUDispense(dispenseData, numberOfCassettesEnabled)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU DISPENSE: ${return_code} (${return_int}): ${return_message}`)
    if (data === "") console.log(`CDU DISPENSE RESULT EMPTY!`)
    const result = data.split(";")
      .map(([
        iDispensedCount,
        iRejectedCount,
        iPassedCount,
        iSkewCount,
        iAbnormalSpaceCount,
        iLongCount,
        iShortCount,
        iDoubleNoteCount,
        iHalfSizeCount,
      ]) => ({ iDispensedCount, iRejectedCount, iPassedCount, iSkewCount, iAbnormalSpaceCount, iLongCount, iShortCount, iDoubleNoteCount, iHalfSizeCount }))
    return { return_int, return_code, return_message, result }
}

exports.present = () => {
    const { return_int } = genmega._CDUPreset()
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU PRESET: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.forceEject = () => {
    const { return_int } = genmega._CDUForceEject()
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU FORCE EJECT: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.shutterAction = action => {
    const { return_int } = genmega._CDUShutterAction(action)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU SHUTTER ACTION: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.retract = () => {
    const { return_int } = genmega._CDURetract()
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`CDU RETRACT: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}
