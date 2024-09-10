const genmega = require('./build/Release/genmega.node')

exports.getLastError = () => {
    const { data } = genmega._BAUGetLastError()
    return { data }
}

exports.open = serialPortName => {
    const { return_int, data } = genmega._CDUOpen(serialPortName)
    console.log('CDU Firmware Version: ', data)
    if (return_int < 0) console.error('CDU OPEN: ', return_int)
    return { return_int }
}

exports.close = () => genmega._CDUClose()

exports.status = () => {
    const { return_int, data } = genmega._CDUStatus()
    if (return_int < 0) console.error(`CDU STATUS: ${return_int}`)
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
    const result = { iLineStatus, iCstNum, iDispenseType, iJamStatus, iCst1Status, iCst2Status, iCst3Status, iCst4Status, iCst5Status, iCst6Status, iShutterStatus, iShutterRemain, iStackerRemain, iTransporterRemain }
    return { return_int, result }
}

exports.verifyLicenseKey = licenseKey => {
    const { return_int } = genmega._CDUVerifyLicenseKey(licenseKey)
    if (return_int < 0) console.error('CDU VERIFY LICENSE KEY: ', return_int)
    return { return_int }
}

exports.reset = resetMode => {
    const { return_int } = genmega._CDUReset(resetMode)
    if (return_int < 0) console.error('CDU RESET: ', return_int)
    return { return_int }
}

exports.setCassetteNumber = cassetteNumber => {
    const { return_int } = genmega._CDUSetCassetteNumber(cassetteNumber)
    if (return_int < 0) console.error('CDU SET CASSETTE NUMBER: ', return_int)
    return { return_int }
}

exports.dispense = (dispenseData, numberOfCassettesEnabled) => {
    dispenseData = [0, 1, 2, 3, 4, 5].map(idx => dispenseData[idx] ?? 0)
    if (numberOfCassettesEnabled > dispenseData.length) numberOfCassettesEnabled = dispenseData.length
    const { return_int, data } = genmega._CDUDispense(dispenseData, numberOfCassettesEnabled)
    if (return_int < 0) console.error(`CDU DISPENSE: ${return_int}`)
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
    return { return_int, result }
}

exports.present = () => {
    const { return_int } = genmega._CDUPreset()
    if (return_int < 0) console.error('CDU PRESET: ', return_int)
    return { return_int }
}

exports.forceEject = () => {
    const { return_int } = genmega._CDUForceEject()
    if (return_int < 0) console.error('CDU FORCE EJECT: ', return_int)
    return { return_int }
}

exports.shutterAction = action => {
    const { return_int } = genmega._CDUShutterAction(action)
    if (return_int < 0) console.error('CDU SHUTTER ACTION: ', return_int)
    return { return_int }
}

exports.retract = () => {
    const { return_int } = genmega._CDURetract()
    if (return_int < 0) console.error('CDU RETRACT: ', return_int)
    return { return_int }
}
