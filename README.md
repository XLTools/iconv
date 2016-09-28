IConv
=====

Specific blocks dependent on the `_MSC_VER` macro have been defined thanks to Youngho's patches described [here](http://www.codeproject.com/Articles/302012/How-to-Build-libiconv-with-Microsoft-Visual-Studio).

The rest of the library has pre-built `config.h` headers from test build systems (CentOS 5, MSYS2, and various cross-compilers).

The library has been tested with the following build chains and systems:
- Centos 5 (Static Only)
- Ubuntu 16.04 (Static Only)

## Cross-Compilers

The cross-compiler settings were done using [MXE](https://github.com/mxe/mxe) on Ubuntu, using IConv downloaded from GNU with the following settings:

**Hosts**

- i686-w64-mingw32
- x86_64-w64-mingw32

```bash
./configure CC=/usr/bin/$HOST-gcc --host=$HOST
```
