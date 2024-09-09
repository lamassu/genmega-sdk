const genmega = require('./build/Release/genmega.node')

exports.scan = (serialPortName, mobilePhoneMode) => {
  return new Promise(resolve => {
    /* There's a timeout at ~30s, but we never learn of it... */
    const timeout = setTimeout(() => {
      exports.cancelScan()
      return resolve({ iRet: -9, code: null })
    }, 31000)

    genmega._BCSScan(
      serialPortName,
      mobilePhoneMode,
      (iRet, code) => {
        clearTimeout(timeout)
        console.log("BCSScan resolving with iRet", iRet, "and code", code)
        return resolve({ iRet, code })
      }
    )
  })
}

exports.cancelScan = () => genmega._BCSCancelScan()
