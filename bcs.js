const genmega = require('./build/Release/genmega.node')

exports.BCSScan = function BCSScan(serialPortName, mobilePhoneMode) {
  return new Promise(resolve => {
    /* There's a timeout at ~30s, but we never learn of it... */
    const timeout = setTimeout(() => {
      exports.BCSCancelScan()
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

exports.BCSCancelScan = function BCSCancelScan() {
    return genmega._BCSCancelScan()
}
