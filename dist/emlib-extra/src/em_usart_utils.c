#include "em_usart_utils.h"
#if defined(USART_COUNT) && (USART_COUNT > 0)

#include "em_assert.h"

/***************************************************************************//**
 * @brief
 *   Convert data bits to the enum value in USART_Databits_TypeDef.
 *
 * @param[in] bits
 *   The number of bits.
 *
 * @return
 *   Corresponding enum value.
 ******************************************************************************/
__INLINE USART_Databits_TypeDef USART_DataBits2Def(uint8_t bits)
{
  EFM_ASSERT(bits >= 4 && bits <= 16);

  return (USART_Databits_TypeDef) ((bits - 3) << _USART_FRAME_DATABITS_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Convert stop bits (expressed as halves) to the enum value in
 *   USART_Stopbits_TypeDef.
 *
 * @param[in] half_bits
 *   The number of half bits (e.g. 1 bit equals 2 half bits).
 *
 * @return
 *   Corresponding enum value.
 ******************************************************************************/
__INLINE USART_Stopbits_TypeDef USART_StopBits2Def(uint8_t half_bits)
{
  EFM_ASSERT(half_bits >= 1 && half_bits <= 4);

  return (USART_Stopbits_TypeDef) ((half_bits - 1) << _USART_FRAME_STOPBITS_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Convert a number to the enum value in USART_Parity_TypeDef.
 *
 * @param[in] number
 *   Odd numbers map to odd parity, even numbers to even parity and zero to no
 *   parity.
 *
 * @return
 *   Corresponding enum value.
 ******************************************************************************/
__INLINE USART_Parity_TypeDef USART_Parity2Def(uint8_t number)
{
  return (USART_Parity_TypeDef) ((number == 0 ? number : (number % 2) + 2) << _USART_FRAME_PARITY_SHIFT);
}

#endif /* defined(USART_COUNT) && (USART_COUNT > 0) */
