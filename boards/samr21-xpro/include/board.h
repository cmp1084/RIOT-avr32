/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_samr21-xpro
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Atmel SAM R21 Xplained Pro
 *              board
 *
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 * @author      Sebastian Meiling <s@mlng.net>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph_conf.h"
#include "periph_cpu.h"

#include "edbg_eui.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    xtimer configuration
 * @{
 */
#define XTIMER_DEV          TIMER_DEV(1)
#define XTIMER_CHAN         (0)
/** @} */

/**
 * @name    ztimer configuration
 * @{
 */
#define CONFIG_ZTIMER_USEC_TYPE    ZTIMER_TYPE_PERIPH_TIMER
#define CONFIG_ZTIMER_USEC_DEV     TIMER_DEV(1)
/* timer_set() may underflow for values smaller than 9, set 10 as margin */
#define CONFIG_ZTIMER_USEC_MIN     (10)
/** @} */

/**
 * @name    AT86RF233 configuration
 *
 * {spi bus, spi speed, cs pin, int pin, reset pin, sleep pin}
 */
#define AT86RF2XX_PARAM_CS         GPIO_PIN(PB, 31)
#define AT86RF2XX_PARAM_INT        GPIO_PIN(PB, 0)
#define AT86RF2XX_PARAM_SLEEP      GPIO_PIN(PA, 20)
#define AT86RF2XX_PARAM_RESET      GPIO_PIN(PB, 15)

/**
 * @brief    EDBG provides a EUI-64, the same that is printed on the board
 */
static inline int _edbg_get_eui64(const void *arg, eui64_t *addr)
{
    (void) arg;

    /* EDBG can take a while to respond on cold boot */
    unsigned tries = 10000;
    while (--tries && edbg_get_eui64(addr)) {}
    return tries ? 0 : -1;
}

/**
 * @name    EUI sources on the board
 *          EUI-64 inside EDBG for the internal radio
 * @{
 */
#define EUI64_PROVIDER_FUNC   _edbg_get_eui64
#define EUI64_PROVIDER_TYPE   NETDEV_AT86RF2XX
#define EUI64_PROVIDER_INDEX  0
/** @} */

/**
 * @name    OpenWSN timing constants
 *
 * @{
 */
/* Measured 800us + ~10% */
#define PORT_maxTxDataPrepare   (900/PORT_US_PER_TICK)
/* Measured 450us + ~10% */
#define PORT_maxRxAckPrepare    (500/PORT_US_PER_TICK)
/* Measured 500us + ~10% */
#define PORT_maxRxDataPrepare   (550/PORT_US_PER_TICK)
/* Measured 660us + ~10% */
#define PORT_maxTxAckPrepare    (750/PORT_US_PER_TICK)
/* Measured 650us with openwsn_sctimer_rtt */
#define PORT_delayTx            (650/PORT_US_PER_TICK)
/** @} */

/**
 * @name    LED pin definitions and handlers
 * @{
 */
#define LED0_PIN            GPIO_PIN(0, 19)

#define LED_PORT            PORT->Group[0]
#define LED0_MASK           (1 << 19)

#define LED0_ON             (LED_PORT.OUTCLR.reg = LED0_MASK)
#define LED0_OFF            (LED_PORT.OUTSET.reg = LED0_MASK)
#define LED0_TOGGLE         (LED_PORT.OUTTGL.reg = LED0_MASK)
/** @} */

/**
 * @name    SW0 (Button) pin definitions
 * @{
 */
#define BTN0_PORT           PORT->Group[0]
#define BTN0_PIN            GPIO_PIN(0, 28)
#define BTN0_MODE           GPIO_IN_PU
/** @} */

/**
 * @name    Antenna configuration pin interface
 * @{
 */
#define RFCTL1_PIN          GPIO_PIN(0, 9)
#define RFCTL2_PIN          GPIO_PIN(0, 12)
/** @} */

/**
 * @brief   Antenna configuration values
 */
enum {
    RFCTL_ANTENNA_BOARD,
    RFCTL_ANTENNA_EXT,
};

/**
 * @name    Default antenna configuration
 * @{
 */
#ifndef RFCTL_ANTENNA_DEFAULT
#define RFCTL_ANTENNA_DEFAULT      RFCTL_ANTENNA_BOARD
#endif
/** @} */

/**
 * @brief   Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

/**
 * @brief   Set antenna switch
 */
void board_antenna_config(uint8_t antenna);
#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
