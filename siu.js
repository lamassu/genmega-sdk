const genmega = require('./build/Release/genmega.node')

const LED_OFF = 0

exports.SIULightUp = function SIULightUp (serialPortName, device, type) {
    const { iRet: iRetOpen, data } = genmega._SIUOpen(serialPortName);
    console.log('SIU Firmware Version: ', data)
    if(iRetOpen < 0) {
        console.error('SIU OPEN: ', iRetOpen)
        return { iRetOpen }
    }
    const { iRet } = genmega._SIUFlicker(device, type)
    return { iRet }
}

exports.SIULightDown = function SIULightDown (device) {
    const { iRet } = genmega._SIUReset()
    genmega._SIUClose()
    return { iRet }
}
