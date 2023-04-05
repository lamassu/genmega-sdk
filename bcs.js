const _ = require('lodash/fp')
const genmega = require('./build/Release/genmega.node')

exports.BCSScan = function BCSScan(serialPortName, mobilePhoneMode) {
    return new Promise((resolve, reject) => {
        genmega._BCSScan(serialPortName, mobilePhoneMode, (err, result) => {
          if (err < 0) return reject(err)
          return resolve(result)
        })
    })
}

exports.BCSCancelScan = function BCSCancelScan() {
    return genmega._BCSCancelScan()
}