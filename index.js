exports.bau = require('./bau')
exports.bcs = require('./bcs')
exports.cdu = require('./cdu')
const rpu = require('./rpu')
const siu = require('./siu')

exports.RPUOpen = rpu.RPUOpen
exports.RPUClose = rpu.RPUClose
exports.RPUStatus = rpu.RPUStatus
exports.RPUCutPaper = rpu.RPUCutPaper
exports.RPUPrintText = rpu.RPUPrintText
exports.SIULightUp = siu.SIULightUp
exports.SIULightDown = siu.SIULightDown
