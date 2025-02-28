const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.scan = (serialPortName, mobilePhoneMode) => {
  return new Promise(resolve => {
    /* There's a timeout at ~30s, but we never learn of it... */
    let timeout = setTimeout(() => {
      timeout = null
      const decoded = null
      const return_int = -9
      console.log("BCSScan timeout callback called")
      resolve({ decoded, return_int })
      exports.cancelScan()
    }, 31000)

    genmega._BCSScan(
      serialPortName,
      mobilePhoneMode,
      (return_int, decoded) => {
        console.log("BCSScan result callback called with return_int", return_int, "and decoded", decoded, "(timedout?", !timeout ,")")
        if (timeout) {
          clearTimeout(timeout)
          console.log("BCSScan resolving with return_int", return_int, "and decoded", decoded)
          resolve({ decoded, return_int })
        }
      }
    )
  })
  .then(({ decoded, return_int }) => ({
    decoded,
    return_int,
    return_code: return_codes[return_int],
    return_message: return_messages[return_int],
  }))
}

exports.cancelScan = () => genmega._BCSCancelScan()
