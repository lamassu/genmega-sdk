const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.getLastError = () => {
    const { data } = genmega._RPUGetLastError();
    return data
}

exports.open = serialPortName => {
    const { data, return_int } = genmega._RPUOpen(serialPortName)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    console.log('RPU Firmware Version: ', data)
    if (return_int < 0) console.error(`RPU OPEN: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.close = () => genmega._RPUClose()

exports.status = () => {
    const { data, return_int } = genmega._RPUStatus()
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`RPU STATUS: ${return_code} (${return_int}): ${return_message}`)
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
    return { return_int, return_code, return_message, result }
}

exports.cutPaper = () => {
    const { data, return_int } = genmega._RPUCutPaper()
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`RPU CUT PAPER: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}

exports.printText = text => {
    const { data, return_int } = genmega._RPUPrintText(text)
    const return_code = return_codes[return_int]
    const return_message = return_messages[return_int]
    if (return_int < 0) console.error(`RPU PRINT TEXT: ${return_code} (${return_int}): ${return_message}`)
    return { return_int, return_code, return_message }
}
