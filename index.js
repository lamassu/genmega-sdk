const genmega = require('./build/Release/genmega.node')
const bau = require('./bau')

exports.BarcodeScan = genmega.BarcodeScan
exports.BarcodeCancelScan = genmega.BarcodeCancelScan
exports.BAUGetLastError = bau.BAUGetLastError
exports.BAUOpen = bau.BAUOpen
exports.BAUReset = bau.BAUReset
exports.BAUClose = bau.BAUClose
exports.BAUStatus = bau.BAUStatus
exports.BAUSetEnableDenom = bau.BAUSetEnableDenom
exports.BAUAcceptBill = bau.BAUAcceptBill
exports.BAUCancel = bau.BAUCancel
exports.BAUReject = bau.BAUReject
exports.BAUStack = bau.BAUStack
exports.BAUGetSupportCurrency = bau.BAUGetSupportCurrency
