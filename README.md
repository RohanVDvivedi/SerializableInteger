# SerializableInteger
This library provides 2 utilities for my downstream projects.
 * ***A large fixed width serializable unsigned integer***
  - It can be used as counters, log sequence numbers, transaction ids etc, where the number is expected to increment for almost forever and you believe that 64 bits are just not enough. If you want something more than what this library provdes, then instead use [GNU MP](https://gmplib.org/) instead.
 * ***Little endian Serialize and Deserialize routines for c stdint's uintX_t and intX_t***
  - it allows you to serialize integers into bytes lesser than X (lets stay y < X) bytes, while still preserving its value (assuming that you are only using little endian first y bytes of a integer that is X bytes wide), This allows a more compact integer, discarding the unused most significant bytes.

## Setup instructions
**Install dependencies :**
 * [Cutlery](https://github.com/RohanVDvivedi/Cutlery)

**Download source code :**
 * `git clone https://github.com/RohanVDvivedi/SerializableInteger.git`

**Build from source :**
 * `cd SerializableInteger`
 * `make clean all`

**Install from the build :**
 * `sudo make install`
 * ***Once you have installed from source, you may discard the build by*** `make clean`

## Using The library
 * add `-lcutlery` linker flag, while compiling your application
 * do not forget to include appropriate public api headers as and when needed. this includes
   * `#include<large_uints.h>`
   * `#include<large_uint.h>`
   * `#include<serial_int.h>`

## Instructions for uninstalling library

**Uninstall :**
 * `cd SerializableInteger`
 * `sudo make uninstall`
