const genmega = require('./build/Release/genmega.node')

exports.BCSScan = function BCSScan(serialPortName, mobilePhoneMode) {
    return new Promise((resolve, reject) =>
      genmega._BCSScan(
        serialPortName,
        mobilePhoneMode,
        (err, result) => (err < 0) ? reject(err) : resolve(result)
      )
    )
}

exports.BCSCancelScan = function BCSCancelScan() {
    return genmega._BCSCancelScan()
}
