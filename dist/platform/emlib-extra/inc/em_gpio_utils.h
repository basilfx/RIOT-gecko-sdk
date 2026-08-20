#ifndef __SILICON_LABS_EM_GPIO_UTILS_H__
#define __SILICON_LABS_EM_GPIO_UTILS_H__

#include "em_device.h"
#if defined(GPIO_COUNT) && (GPIO_COUNT > 0)

#include "em_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (_SILICON_LABS_32B_SERIES >= 2)
uint32_t GPIO_PortPin2Route(GPIO_Port_TypeDef port, uint8_t pin);
#endif

#ifdef __cplusplus
}
#endif

#endif /* defined(GPIO_COUNT) && (GPIO_COUNT > 0) */
#endif /* __SILICON_LABS_EM_GPIO_UTILS_H__ */
