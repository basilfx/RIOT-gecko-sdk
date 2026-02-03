# Gecko SDK for RIOT-OS
Minimal distribution of the Silicon Labs Gecko SDK for EFM32/EFR32/EZR32 microcontrollers, prepared for usage with [RIOT-OS](https://github.com/RIOT-OS/RIOT).

## Version
The current version of the Gecko SDK is 4.5.0.

## Contents
The following is included in the `dist/` folder:

* platform/common - vendor library
* platform/Device - vendor headers
* platform/emlib - vendor library (patched)
* platform/emlib-extra - library
* platform/radio - vendor library

## Copyright
The vendor files in the `dist/` are copyrighted by Silicon Labs. The remaining files are covered by the `LICENSE.md` file (MIT license).

## Changes
Refer to `build.sh` to see what changes are applied to the files distributed in `dist/`.
