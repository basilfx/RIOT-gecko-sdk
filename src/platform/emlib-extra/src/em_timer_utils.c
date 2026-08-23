#include "em_timer_utils.h"
#if defined(TIMER_COUNT) && (TIMER_COUNT > 0)

#include "em_timer.h"
#include "em_assert.h"
#include "em_gpio_utils.h"

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
__INLINE uint32_t TIMER_Channel2Route(uint8_t ch)
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
__INLINE uint32_t TIMER_Prescaler2Div(TIMER_Prescale_TypeDef prescaler)
{
  EFM_ASSERT(prescaler <= timerPrescale1024);

  return (1 << ((uint8_t) prescaler));
}

/***************************************************************************//**
 * @brief
 *   Calculate the timer prescaler for a given frequency and timer frequency.
 *
 * @note
 *   The resulting prescaler will result a frequency that is equal or higher
 *   than the desired frequency. If no prescaler is found, it will exceed
 *   timerPrescale1024.
 *
 * @param[in] freq
 *   The desired frequency (in Hz).
 *
 * @param[in] freq_timer
 *   The reference frequency of the timer (in Hz).
 *
 * @return
 *   Timer prescaler (timerPrescale1 to timerPrescale1024).
 ******************************************************************************/
TIMER_Prescale_TypeDef TIMER_PrescalerCalc(uint32_t freq, uint32_t freq_timer)
{
  uint8_t prescaler = 0;

  /* keep dividing the timer frequency until it is lower than the desired
     frequency */
  while (freq_timer && freq_timer > freq) {
    freq_timer = freq_timer / 2;
    prescaler = prescaler + 1;
  }

  /* the return type starts at 0 for the first prescaler (division by 1), so if
     no prescaler was found, prescaler - 1 will wrap around, which means only
     one comparison is needed to check for validity */
  return (TIMER_Prescale_TypeDef) ((uint8_t) prescaler - 1);
}
#else /* (_SILICON_LABS_32B_SERIES < 2) */
/***************************************************************************//**
 * @brief
 *   Route a compare/capture channel to a pin.
 *
 * @note
 *   The channel index number must exist.
 *
 * @param[in] timer
 *   A pointer to the TIMER peripheral register block.
 *
 * @param[in] ch
 *   The channel index number.
 *
 * @param[in] port
 *   The GPIO port number to route the channel to.
 *
 * @param[in] pin
 *   The GPIO pin number to route the channel to.
 ******************************************************************************/
void TIMER_CCRoute(TIMER_TypeDef *timer, uint8_t ch, GPIO_Port_TypeDef port,
                   uint8_t pin)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));
  EFM_ASSERT(TIMER_REF_CH_VALIDATE(timer, ch));

  GPIO_TIMERROUTE_TypeDef *route = &GPIO->TIMERROUTE[TIMER_NUM(timer)];
  uint32_t route_value = GPIO_PortPin2Route(port, pin);

  switch (ch) {
    case 0:
      route->CC0ROUTE = route_value;
      break;
    case 1:
      route->CC1ROUTE = route_value;
      break;
    case 2:
      route->CC2ROUTE = route_value;
      break;
    default:
      EFM_ASSERT(false);
      return;
  }

  route->ROUTEEN |= (0x1UL << ch);
}

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
__INLINE uint32_t TIMER_Prescaler2Div(TIMER_Prescale_TypeDef prescaler)
{
  EFM_ASSERT(prescaler <= timerPrescale1024);

  return ((uint32_t) prescaler) + 1;
}

/***************************************************************************//**
 * @brief
 *   Calculate the timer prescaler for a given frequency and timer frequency.
 *
 * @note
 *   Unlike series 0/1, the prescaler field is a linear divider, so the
 *   resulting frequency is the highest achievable frequency that does not
 *   exceed the desired frequency. If the desired frequency is higher than the
 *   timer frequency, timerPrescale1 is returned, since that is the closest
 *   the timer is able to get without exceeding the desired frequency. If no
 *   prescaler is found, it will exceed timerPrescale1024.
 *
 * @param[in] freq
 *   The desired frequency (in Hz).
 *
 * @param[in] freq_timer
 *   The reference frequency of the timer (in Hz).
 *
 * @return
 *   Timer prescaler (timerPrescale1 to timerPrescale1024).
 ******************************************************************************/
TIMER_Prescale_TypeDef TIMER_PrescalerCalc(uint32_t freq, uint32_t freq_timer)
{
  uint32_t divider;

  if (freq == 0 || freq_timer == 0) {
    /* signal an invalid prescaler the same way as on series 0/1: a value
     * beyond the largest valid one */
    return (TIMER_Prescale_TypeDef) (timerPrescale1024 + 1);
  }

  /* round the divider up, so the resulting frequency never exceeds the
   * desired frequency. the guard above guarantees that the timer frequency is
   * at least one, so this form cannot overflow */
  divider = ((freq_timer - 1) / freq) + 1;

  if (divider > 1024) {
    return (TIMER_Prescale_TypeDef) (timerPrescale1024 + 1);
  }

  return (TIMER_Prescale_TypeDef) (divider - 1);
}
#endif /* (_SILICON_LABS_32B_SERIES < 2) */

#endif /* defined(TIMER_COUNT) && (TIMER_COUNT > 0) */
