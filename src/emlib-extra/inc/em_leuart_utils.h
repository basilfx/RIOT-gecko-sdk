#ifndef __SILICON_LABS_EM_LEUART_UTILS_H__
#define __SILICON_LABS_EM_LEUART_UTILS_H__

#include "em_device.h"
#if defined(LEUART_COUNT) && (LEUART_COUNT > 0)

#include "em_leuart.h"

#ifdef __cplusplus
extern "C" {
#endif

LEUART_Databits_TypeDef LEUART_DataBits2Def(uint8_t bits);
LEUART_Stopbits_TypeDef LEUART_StopBits2Def(uint8_t half_bits);
LEUART_Parity_TypeDef LEUART_Parity2Def(uint8_t number);

#ifdef __cplusplus
}
#endif

#endif /* defined(LEUART_COUNT) && (LEUART_COUNT > 0) */
#endif /* __SILICON_LABS_EM_LEUART_UTILS_H__ */
