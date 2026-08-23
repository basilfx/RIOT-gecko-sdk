/***************************************************************************//**
 * @file
 * @brief Common utilities that do not belong to a specific peripheral.
 ******************************************************************************/

#ifndef EM_COMMON_UTILS_H
#define EM_COMMON_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup common_utils Common Utils - Common utilities
 * @brief Utilities that do not belong to a specific peripheral
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Create a structure to combine two designated initializers. With this
 *   macro, it is possible to create an initializer using default values, and
 *   to override values at compile time.
 *
 * @note
 *   The resulting variable is called `name`. The actual result is referred to
 *   by `name.conf`.
 ******************************************************************************/
#define EFM32_CREATE_INIT(name, type, defaults, ...) \
struct {                                             \
  type conf;                                         \
} name = {                                           \
  .conf = defaults,                                  \
  __VA_ARGS__                                        \
};

/** @} (end addtogroup common_utils) */

#ifdef __cplusplus
}
#endif

#endif /* EM_COMMON_UTILS_H */
