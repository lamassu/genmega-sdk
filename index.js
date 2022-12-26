const genmega = require('./build/Release/genmega.node')

exports.BarcodeScan = genmega.BarcodeScan
exports.BarcodeCancelScan = genmega.BarcodeCancelScan
exports.BillValidatorStatus = genmega.BillValidatorStatus
exports.BillValidatorEnable = genmega.BillValidatorEnable
exports.BillValidatorDisable = genmega.BillValidatorDisable
exports.BillValidatorStack = genmega.BillValidatorStack
exports.BillValidatorReject = genmega.BillValidatorReject
exports.BillValidatorInit = genmega.BillValidatorInit