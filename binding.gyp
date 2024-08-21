{
  "targets": [
    {
      "target_name": "genmega",
      "sources": [ "src/genmega.cpp" ],
      "cflags_cc!": [ "-Os", "-Wall", "-Wextra", "-pthread" ],
      "libraries": [ "-l:libgenmegadevice64.a", "-l:libgenemv64_api.a", "-lm", "-lusb-1.0", "-ldl" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}
