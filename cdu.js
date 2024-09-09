const genmega = require('./build/Release/genmega.node')

exports.getLastError = () => {
    const { data } = genmega._BAUGetLastError()
    return { data }
}

exports.open = serialPortName => {
    const { iRet, data } = genmega._CDUOpen(serialPortName)
    console.log('CDU Firmware Version: ', data)
    if (iRet < 0) console.error('CDU OPEN: ', iRet)
    return { iRet }
}

exports.close = () => genmega._CDUClose()

exports.status = () => {
    const { iRet, data } = genmega._CDUStatus()
    if (iRet < 0) console.error(`CDU STATUS: ${iRet}`)
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
    return { iRet, result }
}

exports.verifyLicenseKey = licenseKey => {
    const { iRet } = genmega._CDUVerifyLicenseKey(licenseKey)
    if (iRet < 0) console.error('CDU VERIFY LICENSE KEY: ', iRet)
    return { iRet }
}

exports.reset = resetMode => {
    const { iRet } = genmega._CDUReset(resetMode)
    if (iRet < 0) console.error('CDU RESET: ', iRet)
    return { iRet }
}

exports.setCassetteNumber = cassetteNumber => {
    const { iRet } = genmega._CDUSetCassetteNumber(cassetteNumber)
    if (iRet < 0) console.error('CDU SET CASSETTE NUMBER: ', iRet)
    return { iRet }
}

exports.dispense = (dispenseData, numberOfCassettesEnabled) => {
    dispenseData = [0, 1, 2, 3, 4, 5].map(idx => dispenseData[idx] ?? 0)
    if (numberOfCassettesEnabled > dispenseData.length) numberOfCassettesEnabled = dispenseData.length
    const { iRet, data } = genmega._CDUDispense(dispenseData, numberOfCassettesEnabled)
    if (iRet < 0) console.error(`CDU DISPENSE: ${iRet}`)
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
    return { iRet, result }
}

exports.present = () => {
    const { iRet } = genmega._CDUPreset()
    if (iRet < 0) console.error('CDU PRESET: ', iRet)
    return { iRet }
}

exports.forceEject = () => {
    const { iRet } = genmega._CDUForceEject()
    if (iRet < 0) console.error('CDU FORCE EJECT: ', iRet)
    return { iRet }
}

exports.shutterAction = action => {
    const { iRet } = genmega._CDUShutterAction(action)
    if (iRet < 0) console.error('CDU SHUTTER ACTION: ', iRet)
    return { iRet }
}

exports.retract = () => {
    const { iRet } = genmega._CDURetract()
    if (iRet < 0) console.error('CDU RETRACT: ', iRet)
    return { iRet }
}
