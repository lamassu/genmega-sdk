const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.lightUp = (serialPortName, device, type) => {
    const { return_int: return_intOpen, data } = genmega._SIUOpen(serialPortName);
    let return_code = return_codes[return_intOpen]
    let return_message = return_messages[return_intOpen]
    if (return_intOpen < 0) {
        console.error(`SIU OPEN: ${return_code} (${return_intOpen}): ${return_message}`)
        return { return_int: return_intOpen, return_code, return_message }
    }
    console.log('SIU Firmware Version: ', data)
    const { return_int } = genmega._SIUFlicker(device, type)
    return_code = return_codes[return_int]
    return_message = return_messages[return_int]
    return { return_int, return_code, return_message }
}

exports.lightDown = device => {
    const { return_int } = genmega._SIUReset()
    const return_code = return_codes[return_intOpen]
    const return_message = return_messages[return_intOpen]
    genmega._SIUClose()
    return { return_int, return_code, return_message }
}
