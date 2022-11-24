const genmega = require('./build/Release/genmega.node');

function test () {
   genmega.BarcodeScan("/dev/ttyS7", 1)
   genmega.BarcodeCancelScan()
}

function delay (time) {
    return new Promise(resolve => setTimeout(resolve, time));
} 

test()