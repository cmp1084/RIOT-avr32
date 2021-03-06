/*
 * Copyright (C) 2020 Simplemachines.it
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_mizar32
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Mizar32
 *
 * @author      Emil Eriksson <cmp1084@gmail.com>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph_conf.h"
#include "periph_cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Put here board specific definitions:
 - LEDs/buttons macros,
 - on-board drivers parameters
 - xtimer configuration
 */

/**
 * @brief   Initialize board specific hardware
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
