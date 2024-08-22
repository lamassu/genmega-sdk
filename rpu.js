const genmega = require('./build/Release/genmega.node')

exports.RPUGetLastError = function RPUGetLastError () {
    const { data } = genmega._RPUGetLastError();
    return { data }
}

exports.RPUOpen = function RPUOpen (serialPortName) {
    const { iRet, data } = genmega._RPUOpen(serialPortName)
    console.log('RPU Firmware Version: ', data)
    if (iRet < 0) console.error('RPU OPEN: ', iRet)
    return { iRet }
}

exports.RPUClose = function RPUClose () {
    return genmega._RPUClose()
}

exports.RPUStatus = function RPUStatus () {
    const { iRet, data } = genmega._RPUStatus()
    if (iRet < 0) console.error(`RPU STATUS: ${iRet}`)
    if (data === "") console.log(`RPU STATUS EMPTY!`)
    const [
      LineStatus,
      PaperLoad,
      PaperTphLoad,
      PaperNearEnd,
      TphLever,
      PaperJam,
      CutterHome,
      PaperNormal,
    ] = data
    const result = { LineStatus, PaperLoad, PaperTphLoad, PaperNearEnd, TphLever, PaperJam, CutterHome, PaperNormal }
    return { iRet, result };
}

exports.RPUCutPaper = function RPUCutPaper () {
    const { iRet } = genmega._RPUCutPaper()
    if (iRet < 0) console.error('RPU CUT PAPER: ', iRet)
    return { iRet }
}

exports.RPUPrintText = function RPUPrintText (text) {
    const { iRet } = genmega._RPUPrintText(text)
    if (iRet < 0) console.error('RPU PRINT TEXT: ', iRet)
    return { iRet }
}
