const genmega = require('./build/Release/genmega.node')

exports.CDUGetLastError = function CDUGetLastError () {
    const { data } = genmega._BAUGetLastError()
    return { data }
}

exports.CDUOpen = function CDUOpen (serialPortName) {
    const { iRet, data } = genmega._CDUOpen(serialPortName)
    console.log('CDU Firmware Version: ', data)
    if (iRet < 0) console.error('CDU OPEN: ', iRet)
    return { iRet }
}

exports.CDUClose = function CDUClose () {
    return genmega._CDUClose()
}

exports.CDUStatus = function CDUStatus () {
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

exports.CDUVerifyLicenseKey = function CDUVerifyLicenseKey (licenseKey) {
    const { iRet } = genmega._CDUVerifyLicenseKey(licenseKey)
    if (iRet < 0) console.error('CDU VERIFY LICENSE KEY: ', iRet)
    return { iRet }
}

exports.CDUReset = function CDUReset (resetMode) {
    const { iRet } = genmega._CDUReset(resetMode)
    if (iRet < 0) console.error('CDU RESET: ', iRet)
    return { iRet }
}

exports.CDUSetCassetteNumber = function CDUSetCassetteNumber (cassetteNumber) {
    const { iRet } = genmega._CDUSetCassetteNumber(cassetteNumber)
    if (iRet < 0) console.error('CDU SET CASSETTE NUMBER: ', iRet)
    return { iRet }
}

exports.CDUDispense = function CDUDispense (rawDispenseData, numberOfCassettesEnabled) {
    const dispenseData = [0, 1, 2, 3, 4, 5].map(idx => rawDispenseData[idx] ?? 0)
    const { iRet, data } = genmega._CDUDispense(dispenseData, numberOfCassettesEnabled)
    if (iRet < 0) console.error(`CDU DISPENSE: ${iRet}`)
    if (data === "") console.log(`CDU DISPENSE RESULT EMPTY!`)
    const dispenseResultByCassette = data.split(";")
    const result = []
    for(let i = 0; i < numberOfCassettesEnabled; i++) {
        const [
            iDispensedCount,
            iRejectedCount,
            iPassedCount,
            iSkewCount,
            iAbnormalSpaceCount,
            iLongCount,
            iShortCount,
            iDoubleNoteCount,
            iHalfSizeCount,
        ] = dispenseResultByCassette[i]
        result.push({ iDispensedCount, iRejectedCount, iPassedCount, iSkewCount, iAbnormalSpaceCount, iLongCount, iShortCount, iDoubleNoteCount, iHalfSizeCount })
    }
    return { iRet, result }
}

exports.CDUPresent = function CDUPresent () {
    const { iRet } = genmega._CDUPreset()
    if (iRet < 0) console.error('CDU PRESET: ', iRet)
    return { iRet }
}

exports.CDUForceEject = function CDUForceEject () {
    const { iRet } = genmega._CDUForceEject()
    if (iRet < 0) console.error('CDU FORCE EJECT: ', iRet)
    return { iRet }
}

exports.CDUShutterAction = function CDUShutterAction (action) {
    const { iRet } = genmega._CDUShutterAction(action)
    if (iRet < 0) console.error('CDU SHUTTER ACTION: ', iRet)
    return { iRet }
}
