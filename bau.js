const _ = require('lodash/fp')
const genmega = require('./build/Release/genmega.node')

const SENDONLY = 1
const RECVONLY = 2

exports.BAUOpen = function BAUOpen(serialPortName) {
    const { iRet, data } = genmega.BAUOpenV2(serialPortName);
    console.log('BAU Firmware Version: ', data);
    if(iRet < 0) console.error('BAU OPEN: ', iRet); 
    return iRet;
}

exports.BAUClose = function BAUClose() {
    genmega.BAUCloseV2();
    return '0';
}

exports.BAUReset = function BAUReset() {
    const { iRet } = genmega.BAUResetV2();
    return iRet;
}

exports.BAUGetLastError = function BAUGetLastError() {
    const { data } = genmega.BAUGetLastErrorV2();
    return data;
}


exports.BAUStatus = function BAUStatus() {
    const result = {};
    const { iRet, data } = genmega.BAUStatusV2();
    if(iRet < 0) console.error(`BAU STATUS: ${iRet}`);
    const values = data.split("")
    //Alternatively, we can just return the current state 
    //but for testing purposes, we want to check if only one state is active
    result.bLineStatus = values[0];
    result.bAccepting = values[1];
    result.bEscrow = values[2];
    result.bStacking = values[3];
    result.bReturning = values[4];
    result.bJammed = values[5];
    result.bStackerFull = values[6];
    result.bCassetteAttached = values[7];
    result.bPaused = values[8];
    result.bCalibration = values[9];
    result.bFailure = values[10];
    result.bPushNoPush = values[11];
    result.bFlashDownload = values[12];
    return result;
}

exports.BAUSetEnableDenom = function BAUSetEnableDenom(denominationData) {
    const { iRet } = genmega.BAUSetEnableDenomV2(denominationData);
    if(iRet < 0) console.error(`BAU SET ENABLE DENOM: ${iRet}`); 
    return iRet;
}


exports.BAUCancel = function BAUCancel() {
    const { iRet, data } = genmega.BAUCancelV2();
    if(iRet < 0) console.error(`BAU CANCEL BILL: ${iRet}`); 
    return data;
}


exports.BAUEnable = function BAUEnable() {
    let interval;
    let result = { iRet: 0, data: "" };

    return new Promise((resolve, reject) => {
        const { iRet, data } = genmega.BAUAcceptBillV2(SENDONLY);
        if(iRet < 0) throw reject(new Error(`BAU ENABLE: ${iRet}`)); 
        if(data != '0') return resolve(data);
        interval = setInterval(() => {
            const { iRet, data } = genmega.BAUAcceptBillV2(RECVONLY);
            if(data != '0' && iRet != 3) {
              result.data = data;
              result.iRet = iRet;
              clearInterval(interval);
              if (result.data && (result.iRet == 0)) {
                  return resolve(result.data);
              } else reject(new Error(`BAU ENABLE: ${result.iRet}`)); 
            } 
          }, 2000);
      })
}

exports.BAUReject = function BAUReject() {
    const { iRet } = genmega.BAUReturnBillV2();
    if(iRet < 0) console.error(`BAU RETURN BILL: ${iRet}`); 
    return iRet;
}

exports.BAUStack = function BAUStack() {
    const { iRet } = genmega.BAUStackBillV2();
    if(iRet < 0) console.error(`BAU STACK BILL: ${iRet}`); 
    return iRet;
}

exports.BAUGetSupportCurrency = function BAUGetSupportCurrency() {
    const { iRet, data } = genmega.BAUGetSupportCurrencyV2();
    if(iRet < 0) console.error(`BAU GET SUPPORT CURRENCY: ${iRet}`); 
    return data;
}

