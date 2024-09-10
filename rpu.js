const genmega = require('./build/Release/genmega.node')

exports.getLastError = () => {
    const { data } = genmega._RPUGetLastError();
    return data
}

exports.open = serialPortName => {
    const { return_int, data } = genmega._RPUOpen(serialPortName)
    console.log('RPU Firmware Version: ', data)
    if (return_int < 0) console.error('RPU OPEN: ', return_int)
    return { return_int }
}

exports.close = () => genmega._RPUClose()

exports.status = () => {
    const { return_int, data } = genmega._RPUStatus()
    if (return_int < 0) console.error(`RPU STATUS: ${return_int}`)
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
    return { return_int, result };
}

exports.cutPaper = () => {
    const { return_int } = genmega._RPUCutPaper()
    if (return_int < 0) console.error('RPU CUT PAPER: ', return_int)
    return { return_int }
}

exports.printText = text => {
    const { return_int } = genmega._RPUPrintText(text)
    if (return_int < 0) console.error('RPU PRINT TEXT: ', return_int)
    return { return_int }
}
