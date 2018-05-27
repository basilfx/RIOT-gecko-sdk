# Patches

## Introduction
This document will explain the patches that are applied on the source code of the Gecko SDK.

## List of patches

### 0001
Changes `I2C_Transfer` in `emlib/src/em_i2c.c` to return a different fault code to indicate it occurred during the transfer of the address. This way, the caller can identify whether the address is in use, or not. This change is incompatible with original source code.
