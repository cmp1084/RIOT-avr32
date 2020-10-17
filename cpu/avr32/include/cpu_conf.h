/*
 * Copyright (C) 2020 Simplemachines.it
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_avr32
 * @{
 *
 * @file
 * @brief           Implementation specific CPU configuration options
 *
 * @author          Emil Eriksson <cmp1084@gmail.com>
 */

#ifndef CPU_CONF_H
#define CPU_CONF_H
#ifdef __cplusplus
extern "C" {
#endif

#define THREAD_EXTRA_STACKSIZE_PRINTF    (128)

/**
 * @name           Kernel configuration
 *
 *                 Since printf seems to get memory allocated by the
 *                 linker/avr-libc the stack size tested successfully
 *                 even with pretty small stacks.
 * @{
 */
#ifndef THREAD_STACKSIZE_DEFAULT
#define THREAD_STACKSIZE_DEFAULT   (512)
#endif

/* keep THREAD_STACKSIZE_IDLE > THREAD_EXTRA_STACKSIZE_PRINTF
 * to avoid not printing of debug in interrupts
 */
#ifndef THREAD_STACKSIZE_IDLE
#define THREAD_STACKSIZE_IDLE      (128)
#endif
/** @} */
/**
 * @brief   Declare the heap_stats function as available
 */
#define HAVE_HEAP_STATS

/**
 * @brief   This arch uses the inlined IRQ API.
 */
//~ #define IRQ_API_INLINED     (1)
#undef IRQ_API_INLINED

#ifdef __cplusplus
}
#endif

#endif /* CPU_CONF_H */
/** @} */
