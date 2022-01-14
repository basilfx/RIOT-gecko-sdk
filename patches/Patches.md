# Patches

## Introduction
This document will explain the patches that are applied on the source code of the Gecko SDK. Patches are created using `git diff --no-prefix > file.patch`.

## List of patches

### 0001
Changes `I2C_Transfer` in `emlib/src/em_i2c.c` to return a different fault code to indicate it occurred during the transfer of the address. This way, the caller can identify whether the address is in use, or not.

This change is NOT compatible with the original source code.

### 0002
This patch changes `_GPIO_PORT_MASK` in `emlib/inc/em_gpio.h` to not rely on constant values where `GPIO_Port_TypeDef` enums are expected. With Clang as compiler, this would result in `tautological-constant-out-of-range-compare` errors due to implementation-defined behaviour.

This change is compatible with the original source code.

### 0003
This patch renames `GPIO_PinModeSet` into `GPIO_PinModeSetExt` and adds an additional parameter to not change the pin (output) state. The RIOT-OS GPIO peripheral interface requires that pin initialization should not modify the output state. The method `GPIO_PinModeSet` is added, which will will invoke `GPIO_PinModeSetExt` to behave as originally.

This change is compatible with the original source code.

### 0004
Fixes an [old-style function definition](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wold-style-definition) warning / error.

This change is compatible with the original source code.
