/***************************************************************************//**
 * @file
 * @brief PA power conversion curves used by Silicon Labs PA power conversion
 *   functions.
 * @details This file contains the curves needed convert PA power levels to
 *   dBm powers.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef __PA_CURVES_EFR32XG21_H_
#define __PA_CURVES_EFR32XG21_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RAIL_PA_CURVES_PIECEWISE_SEGMENTS (8U)

#define RAIL_PA_CURVES_2P4_HP_VBAT_MAX_POWER      200
#define RAIL_PA_CURVES_2P4_HP_VBAT_MIN_POWER      -260
#define RAIL_PA_CURVES_2P4_HP_VBAT_CURVES \
  { { 180, 2202, -276556 },               \
    { 80, 792, -47941 },                  \
    { 45, 452, -7893 },                   \
    { 27, 261, 6805 },                    \
    { 17, 163, 10609 },                   \
    { 10, 94, 10346 },                    \
    { 6, 58, 8754 },                      \
    { 4, 40, 7288 } }

#define RAIL_PA_CURVES_2P4_MP_VBAT_MAX_POWER      100
#define RAIL_PA_CURVES_2P4_MP_VBAT_MIN_POWER      -260
#define RAIL_PA_CURVES_2P4_MP_VBAT_CURVES \
  { { -1, 0, 0 },                         \
    { -1, 0, 0 },                         \
    { 90, 1782, -111892 },                \
    { 31, 382, 887 },                     \
    { 16, 160, 9764 },                    \
    { 9, 91, 9546 },                      \
    { 6, 53, 7926 },                      \
    { 3, -15, 1499 } }

#define RAIL_PA_CURVES_2P4_LP_VBAT_MAX_POWER      0
#define RAIL_PA_CURVES_2P4_LP_VBAT_MIN_POWER      -260
#define RAIL_PA_CURVES_2P4_LP \
  { { -1, 0, 0 },             \
    { -1, 0, 0 },             \
    { -1, 0, 0 },             \
    { -1, 0, 0 },             \
    { 64, 1695, 59675 },      \
    { 48, 793, 53881 },       \
    { 24, 263, 33942 },       \
    { 14, 105, 21800 } }

// *INDENT-OFF*
// Macro to declare the variables needed to initialize RAIL_TxPowerCurvesConfig_t for use in
// RAIL_InitTxPowerCurves, assuming battery powered operation
#define RAIL_DECLARE_TX_POWER_VBAT_CURVES_ALT                                  \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataHp = {                 \
    RAIL_PA_CURVES_2P4_HP_VBAT_MAX_POWER,                                      \
    RAIL_PA_CURVES_2P4_HP_VBAT_MIN_POWER,                                      \
    RAIL_PA_CURVES_2P4_HP_VBAT_CURVES,                                         \
  };                                                                           \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataMp = {                 \
    RAIL_PA_CURVES_2P4_MP_VBAT_MAX_POWER,                                      \
    RAIL_PA_CURVES_2P4_MP_VBAT_MIN_POWER,                                      \
    RAIL_PA_CURVES_2P4_MP_VBAT_CURVES,                                         \
  };                                                                           \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataLp = {                 \
    RAIL_PA_CURVES_2P4_LP_VBAT_MAX_POWER,                                      \
    RAIL_PA_CURVES_2P4_LP_VBAT_MIN_POWER,                                      \
    RAIL_PA_CURVES_2P4_LP,                                                     \
  };
// *INDENT-OFF*

#define RAIL_DECLARE_TX_POWER_CURVES_CONFIG_ALT                                \
  {                                                                            \
    .curves = {                                                                \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_HP_MIN,                                     \
        .max = RAIL_TX_POWER_LEVEL_HP_MAX,                                     \
        .conversion = { .powerCurve = &RAIL_piecewiseDataHp },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_MP_MIN,                                     \
        .max = RAIL_TX_POWER_LEVEL_MP_MAX,                                     \
        .conversion = { .powerCurve = &RAIL_piecewiseDataMp },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_LP_MIN,                                     \
        .max = RAIL_TX_POWER_LEVEL_LP_MAX,                                     \
        .conversion = { .powerCurve = &RAIL_piecewiseDataLp },               \
      },                                                                       \
    }                                                                          \
  }
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif

#endif
