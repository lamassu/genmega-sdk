const genmega = require('./build/Release/genmega.node')

exports.CDUGetLastError = function CDUGetLastError () {
    const { data } = genmega._BAUGetLastError()
    return { data }
}

exports.CDUOpen = function CDUOpen (serialPortName) {
    const { iRet, data } = genmega._CDUOpen(serialPortName)
    console.log('CDU Firmware Version: ', data)
    if(iRet < 0) console.error('CDU OPEN: ', iRet) 
    return { iRet }
}

exports.CDUClose = function CDUClose () {
    return genmega._CDUClose()
}

exports.CDUStatus = function CDUStatus () {
    const result = {}
    const { iRet, data } = genmega._CDUStatus()
    if(iRet < 0) console.error(`CDU STATUS: ${iRet}`)
    if(data === "") console.log(`CDU STATUS EMPTY!`)
    const values = data.split("")
    result.iLineStatus = values[0]
    result.iCstNum = values[1]
    result.iDispenseType = values[2]
    result.iJamStatus = values[3]
    result.iCst1Status = values[4]
    result.iCst2Status = values[5]
    result.iCst3Status = values[6]
    result.iCst4Status = values[7]
    result.iCst5Status = values[8]
    result.iCst6Status = values[9]
    result.iShutterStatus = values[10]
    result.iShutterRemain = values[11]
    result.iStackerRemain = values[12]
    result.iTransporterRemain = values[13]
    return { iRet, result }
}

exports.CDUVerifyLicenseKey = function CDUVerifyLicenseKey (licenseKey) {
    const { iRet } = genmega._CDUVerifyLicenseKey(licenseKey)
    if(iRet < 0) console.error('CDU VERIFY LICENSE KEY: ', iRet) 
    return { iRet }
}

exports.CDUReset = function CDUReset (resetMode) {
    const { iRet } = genmega._CDUReset(resetMode)
    if(iRet < 0) console.error('CDU RESET: ', iRet) 
    return { iRet }
}

exports.CDUSetCassetteNumber = function CDUSetCassetteNumber (cassetteNumber) {
    const { iRet } = genmega._CDUSetCassetteNumber(cassetteNumber)
    if(iRet < 0) console.error('CDU SET CASSETTE NUMBER: ', iRet) 
    return { iRet }
}

exports.CDUDispense = function CDUDispense (dispenseData, numberOfCassettesEnabled) {
    const result = []
    const { iRet, data } = genmega._CDUDispense(dispenseData, numberOfCassettesEnabled)
    if(iRet < 0) console.error(`CDU DISPENSE: ${iRet}`)
    if(data === "") console.log(`CDU DISPENSE RESULT EMPTY!`)
    const dispenseResultByCassette = data.split(";")
    for(let i = 0; i < numberOfCassettesEnabled; i++) {
        const values = dispenseResultByCassette[i].split("")
        result.push({
            iDispensedCount: values[0],
            iRejectedCount: values[1],
            iPassedCount: values[2],
            iSkewCount: values[3],
            iAbnormalSpaceCount: values[4],
            iLongCount: values[5],
            iShortCount: values[6],
            iDoubleNoteCount: values[7],
            iHalfSizeCount: values[8]
        })
    }
    return { iRet, result }
}

exports.CDUPresent = function CDUPresent () {
    const { iRet } = genmega._CDUPreset()
    if(iRet < 0) console.error('CDU PRESET: ', iRet) 
    return { iRet }
}

exports.CDUForceEject = function CDUForceEject () {
    const { iRet } = genmega._CDUForceEject()
    if(iRet < 0) console.error('CDU FORCE EJECT: ', iRet) 
    return { iRet }
}

exports.CDUShutterAction = function CDUShutterAction (action) {
    const { iRet } = genmega._CDUShutterAction(action)
    if(iRet < 0) console.error('CDU SHUTTER ACTION: ', iRet) 
    return { iRet }
}
