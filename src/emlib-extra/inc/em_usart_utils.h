#ifndef __SILICON_LABS_EM_USART_UTILS_H__
#define __SILICON_LABS_EM_USART_UTILS_H__

#include "em_device.h"
#if defined(USART_COUNT) && (USART_COUNT > 0)

#include "em_usart.h"

#ifdef __cplusplus
extern "C" {
#endif

USART_Databits_TypeDef USART_DataBits2Def(uint8_t bits);
USART_Stopbits_TypeDef USART_StopBits2Def(uint8_t half_bits);
USART_Parity_TypeDef USART_Parity2Def(uint8_t number);

#ifdef __cplusplus
}
#endif

#endif /* defined(USART_COUNT) && (USART_COUNT > 0) */
#endif /* __SILICON_LABS_EM_USART_UTILS_H__ */
