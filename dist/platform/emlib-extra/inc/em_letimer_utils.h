/***************************************************************************//**
 * @file
 * @brief Low Energy Timer (LETIMER) utility API.
 ******************************************************************************/

#ifndef EM_LETIMER_UTILS_H
#define EM_LETIMER_UTILS_H

#include "em_device.h"
#if defined(LETIMER_COUNT) && (LETIMER_COUNT > 0)

#include "em_letimer.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup letimer_utils LETIMER Utils - Low Energy Timer utilities
 * @brief Low Energy Timer (LETIMER) utility API
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get the max count of the low energy timer.
 *
 * @note
 *   All LETIMER instances of a device share the same counter width, therefore
 *   the counter field mask is used.
 *
 * @param[in] letimer
 *   Pointer to the LETIMER peripheral register block.
 *
 * @return
 *   The max count value of the low energy timer. This is 0xFFFF for 16 bit
 *   timers (Series 0 and 1) and 0xFFFFFF for 24 bit timers (Series 2).
 ******************************************************************************/
__STATIC_INLINE uint32_t LETIMER_MaxCount(const LETIMER_TypeDef *letimer)
{
  (void) letimer;

  return _LETIMER_CNT_MASK;
}

/** @} (end addtogroup letimer_utils) */

#ifdef __cplusplus
}
#endif

#endif /* defined(LETIMER_COUNT) && (LETIMER_COUNT > 0) */
#endif /* EM_LETIMER_UTILS_H */
