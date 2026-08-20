/***************************************************************************//**
 * @file
 * @brief Timer/counter (TIMER) utility API.
 ******************************************************************************/

#ifndef EM_TIMER_UTILS_H
#define EM_TIMER_UTILS_H

#include "em_device.h"
#if defined(TIMER_COUNT) && (TIMER_COUNT > 0)

#include "em_timer.h"
#include "em_gpio_utils.h"
#include "sl_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup timer_utils
 * @{
 ******************************************************************************/

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

TIMER_Prescale_TypeDef TIMER_PrescalerCalc(uint32_t freq, uint32_t freq_timer);

#if (_SILICON_LABS_32B_SERIES >= 2)
void TIMER_CCRoute(TIMER_TypeDef *timer, uint8_t ch, GPIO_Port_TypeDef port,
                   uint8_t pin);
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
/***************************************************************************//**
 * @brief
 *   Convert a channel index number to the route bit field.
 *
 * @note
 *   The channel index number must exist.
 *
 * @param[in] ch
 *   The channel index number.
 *
 * @return
 *   Route bit field corresponding to channel index number.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_Channel2Route(uint8_t ch)
{
#ifdef _SILICON_LABS_32B_SERIES_0
  return (TIMER_ROUTE_CC0PEN << ch);
#else
  return (TIMER_ROUTEPEN_CC0PEN << ch);
#endif
}

/***************************************************************************//**
 * @brief
 *   Convert a timer prescaler into a divisor.
 *
 * @note
 *   The prescaler must be a valid prescaler (timerPrescale1 to
 *   timerPrescale1024).
 *
 * @param[in] prescaler
 *   The timer prescaler.
 *
 * @return
 *   Integer divisor in the range 1 to 1024, corresponding to the prescaler.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_Prescaler2Div(TIMER_Prescale_TypeDef prescaler)
{
  EFM_ASSERT(prescaler <= timerPrescale1024);

  return (1 << ((uint8_t) prescaler));
}
#else /* (_SILICON_LABS_32B_SERIES < 2) */
/***************************************************************************//**
 * @brief
 *   Convert a timer prescaler into a divisor.
 *
 * @note
 *   Unlike series 0/1, the prescaler field is a linear divider, so any value
 *   from 1 to 1024 (not just powers of two) is a valid divisor.
 *
 * @param[in] prescaler
 *   The timer prescaler.
 *
 * @return
 *   Integer divisor in the range 1 to 1024, corresponding to the prescaler.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_Prescaler2Div(TIMER_Prescale_TypeDef prescaler)
{
  EFM_ASSERT(prescaler <= timerPrescale1024);

  return ((uint32_t) prescaler) + 1;
}
#endif /* (_SILICON_LABS_32B_SERIES < 2) */

/** @} (end addtogroup timer_utils) */

#ifdef __cplusplus
}
#endif

#endif /* defined(TIMER_COUNT) && (TIMER_COUNT > 0) */
#endif /* EM_TIMER_UTILS_H */
