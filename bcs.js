const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.getInfo = serialPortName => {
  const serialPortNameType = typeof serialPortName
  if (serialPortNameType !== 'string')
    throw new Error(`BCS serial port name must be a string; got ${serialPortName} (${serialPortNameType})`)
  const { data, return_int } = genmega._BCSGetInfo(serialPortName)
  return {
    data,
    return_int,
    return_code: return_codes[return_int],
    return_message: return_messages[return_int],
  }
}

exports.scan = (serialPortName, mobilePhoneMode, extensions = []) => {
  const serialPortNameType = typeof serialPortName
  if (serialPortNameType !== 'string')
    return Promise.reject(new Error(`BCS serial port name must be a string; got ${serialPortName} (${serialPortNameType})`))

  if (![0, 1].includes(mobilePhoneMode))
    return Promise.reject(new Error(`BCS mobile phone mode must be 0 or 1; got ${mobilePhoneMode}`))

  if (extensions.some(ext => typeof ext !== 'string'))
    return Promise.reject(new Error("BCS extensions must be strings"))

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
      extensions,
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
