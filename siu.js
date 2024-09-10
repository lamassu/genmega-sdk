const genmega = require('./build/Release/genmega.node')

exports.lightUp = (serialPortName, device, type) => {
    const { return_int: return_intOpen, data } = genmega._SIUOpen(serialPortName);
    if (return_intOpen < 0) {
        console.error('SIU OPEN: ', return_intOpen)
        return { return_intOpen }
    }
    console.log('SIU Firmware Version: ', data)
    const { return_int } = genmega._SIUFlicker(device, type)
    return { return_int }
}

exports.lightDown = device => {
    const { return_int } = genmega._SIUReset()
    genmega._SIUClose()
    return { return_int }
}
