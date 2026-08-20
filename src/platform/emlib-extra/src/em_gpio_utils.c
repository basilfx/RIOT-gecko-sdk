#include "em_gpio_utils.h"
#if defined(GPIO_COUNT) && (GPIO_COUNT > 0)

#include "em_assert.h"

#if (_SILICON_LABS_32B_SERIES >= 2)
/***************************************************************************//**
 * @brief
 *   Combine a port and pin number into the value expected by a series 2
 *   GPIO peripheral route register (e.g. GPIO->TIMERROUTE[n].CC0ROUTE or
 *   GPIO->USARTROUTE[n].TXROUTE).
 *
 * @note
 *   Every series 2 GPIO route register places the port number in the low
 *   byte and the pin number at bit 16, regardless of which peripheral the
 *   route register belongs to.
 *
 * @param[in] port
 *   The GPIO port number.
 *
 * @param[in] pin
 *   The GPIO pin number.
 *
 * @return
 *   The route register value with the port and pin fields set.
 ******************************************************************************/
uint32_t GPIO_PortPin2Route(GPIO_Port_TypeDef port, uint8_t pin)
{
  EFM_ASSERT(GPIO_PORT_PIN_VALID(port, pin));

  return ((uint32_t) port) | (((uint32_t) pin) << 16);
}
#endif /* (_SILICON_LABS_32B_SERIES >= 2) */

#endif /* defined(GPIO_COUNT) && (GPIO_COUNT > 0) */
