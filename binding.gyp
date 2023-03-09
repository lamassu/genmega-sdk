{
  "targets": [
    {
      "target_name": "genmega",
      "sources": [ "src/genmega.cpp", "src/devices/barcode-scanner.cpp", "src/devices/bill-validator.cpp", "src/devices/bill-dispenser.cpp", "src/devices/printer.cpp", "src/devices/leds.cpp" ],
      "cflags_cc!": [ "-g", "-O", "-Wno-unused-result", "-Wimplicit-function-declaration", "-pthread" ],
      "libraries": [ "-lgenmegadevice64", "-lgenemv64_api", "-lm", "-lusb-1.0", "-ldl" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}
