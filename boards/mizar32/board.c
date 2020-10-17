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
 * @brief       Board specific implementations for the Mizar32 board
 *
 * @author      Emil Eriksson <cmp1084@gmail.com>
 *
 * @}
 */

#include <avr32/io.h>

#include "cpu.h"
#include "board.h"
#include "periph/gpio.h"

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();
}
