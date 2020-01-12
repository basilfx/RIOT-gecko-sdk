/***************************************************************************//**
 * @file
 * @brief Auxiliary header for the RAIL library. Includes consistent definitions
 *   of features available across different chips.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef __RAIL_FEATURES_H__
#define __RAIL_FEATURES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "em_device.h"

/**
 * @addtogroup RAIL_API RAIL API
 * @{
 */

/******************************************************************************
 * RAIL Features
 *****************************************************************************/
/**
 * @addtogroup Features
 * @brief Overview of support for various features across hardware platforms.
 *        These defines can be used at compile time to determine which
 *        features are available on your platform. However, keep in mind that
 *        these defines hold true for chip families. Your specific part
 *        may have further restrictions (band limitations, power amplifier
 *        restrictions, and so on) on top of those listed below. In general, an
 *        attempt to call an API that is not supported on your chip family as
 *        listed below will result in a \ref RAIL_STATUS_INVALID_CALL.
 * @{
 */

/// Boolean to indicate whether the selected chip supports both SubGHz and 2.4 GHz bands.
#define RAIL_FEAT_DUAL_BAND_RADIO                                         \
  ((_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_DUALBAND) \
   || ((FEAT_RF_2G4 == 1) && (FEAT_RF_SUBG == 1)))

/// Boolean to indicate whether the selected chip supports SubGHz bands.
#define RAIL_FEAT_SUBGIG_RADIO                                               \
  (((_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_DUALBAND)   \
    || (_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_SUBGHZ)) \
   || (FEAT_RF_SUBG == 1))

/// Boolean to indicate whether the selected chip supports the 2.4 GHz band.
#define RAIL_FEAT_2G4_RADIO                                                 \
  (((_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_DUALBAND)  \
    || (_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_2G4HZ)) \
   || (FEAT_RF_2G4 == 1))

/// Boolean to indicate whether the selected chip supports antenna diversity.
#define RAIL_FEAT_ANTENNA_DIVERSITY \
  ((_SILICON_LABS_32B_SERIES_1_CONFIG >= 2) || (_SILICON_LABS_32B_SERIES == 2))

/// Boolean to indicate whether the selected chip supports Z-Wave.
#define RAIL_FEAT_ZWAVE_SUPPORTED \
  ((_SILICON_LABS_32B_SERIES_1_CONFIG >= 3) && (RAIL_FEAT_SUBGIG_RADIO))

/// Boolean to indicate whether the selected chip supports channel hopping.
#define RAIL_FEAT_CHANNEL_HOPPING \
  ((_SILICON_LABS_32B_SERIES_1_CONFIG >= 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG >= 1))

/// Boolean to indicate whether the selected chip supports the BLE coded PHY.
#define RAIL_FEAT_BLE_CODED                 \
  ((_SILICON_LABS_32B_SERIES_1_CONFIG == 3) \
   || (_SILICON_LABS_32B_SERIES_2_CONFIG == 1))

/// Boolean to indicate whether the selected chip supports BLE PHY switch to RX
/// functionality, which is used to switch BLE PHYs at a specific time
/// to receive auxiliary packets.
#define RAIL_FEAT_BLE_PHY_SWITCH_TO_RX (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)

/// Boolean to indicate whether the selected chip supports the
/// 802.15.4 Wi-Fi Coexistence PHY.
#define RAIL_FEAT_802154_COEX_PHY \
  (_SILICON_LABS_32B_SERIES_1_CONFIG > 1)

/// Boolean to indicate whether the selected chip supports BLE
/// Angle-of-Arrival/Departure features.
#define RAIL_FEAT_BLE_AOX_SUPPORTED                                                   \
  ((_SILICON_LABS_32B_SERIES_1_CONFIG == 3 || _SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
   && (RAIL_FEAT_2G4_RADIO))

// IEEE 802.15.4 features
// Some features may not be available on all platforms
// due to radio hardware limitations.

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4E-2012 feature subset needed for Zigbee R22 GB868.
#define RAIL_FEAT_IEEE802154_E_GB868_SUPPORTED 1

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4E-2012 Enhanced ACKing.
#define RAIL_FEAT_IEEE802154_E_ENH_ACK_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 feature subset needed for Zigbee R22 GB868.
#define RAIL_FEAT_IEEE802154_G_GB868_SUPPORTED \
  (RAIL_FEAT_SUBGIG_RADIO)

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 reception of unwhitened frames.
#define RAIL_FEAT_IEEE802154_G_UNWHITENED_RX_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG > 1)

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 transmission of unwhitened frames.
#define RAIL_FEAT_IEEE802154_G_UNWHITENED_TX_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG > 1)

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 reception and transmission of frames
/// with 4-byte CRC.
#define RAIL_FEAT_IEEE802154_G_4BYTE_CRC_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG > 1)

/// Boolean to indicate whether the selected chip supports
/// canceling the frame-pending lookup event
/// \ref RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
/// when the radio transitions to a state that renders the
/// the reporting of this event moot (i.e. too late for
/// the stack to influence the outgoing ACK).
#define RAIL_FEAT_IEEE802154_CANCEL_FP_LOOKUP_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)

/// Boolean to indicate whether the selected chip supports
/// early triggering of the frame-pending lookup event
/// \ref RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
/// just after MAC address fields have been received.
#define RAIL_FEAT_IEEE802154_EARLY_FP_LOOKUP_SUPPORTED 1

/// Boolean to indicate whether the selected chip supports
/// receiving IEEE 802.15.4E-2012 MultiPurpose frames.
#define RAIL_FEAT_IEEE802154_MULTIPURPOSE_FRAME_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)

/// Boolean to indicate whether the selected chip supports
/// alternate power settings for the Power Amplifier.
#define RAIL_FEAT_ALTERNATE_POWER_TX_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_1_CONFIG > 1)

/// Boolean to indicate whether the selected chip supports
/// RFSENSE Selective(OOK) Mode.
#define RAIL_FEAT_RFSENSE_SELECTIVE_OOK_MODE_SUPPORTED \
  (_SILICON_LABS_32B_SERIES_2_CONFIG == 2)
/// Boolean to indicate whether the code supports Z-Wave
/// region information in PTI and
/// newer RAIL_ZWAVE_RegionConfig_t structure
#define RAIL_FEAT_ZWAVE_REGION_PTI 1

/** @} */ // end of group Features

/** @} */ // end of group RAIL_API

#ifdef __cplusplus
}
#endif

#endif // __RAIL_FEATURES_H__
