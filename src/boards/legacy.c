/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Pengutronix,
 *               Jonas Martin <kernel@pengutronix.de>
 * Copyright (c) 2026 Pengutronix,
 *               Marc Kleine-Budde <kernel@pengutronix.de>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "board.h"
#include "config.h"
#include "device.h"
#include "gpio.h"
#include "usbd_gs_can.h"

#ifdef CONFIG_FDCAN
static FDCAN_HandleTypeDef hfdcan1 = {
	.Instance = FDCAN1,
};

static FDCAN_HandleTypeDef hfdcan2 = {
	.Instance = FDCAN2,
};

static FDCAN_HandleTypeDef hfdcan3 = {
	.Instance = FDCAN3,
};
#endif

static void __maybe_unused legacy_phy_power_set(can_data_t *channel, bool enable)
{
	UNUSED(channel);

	if (enable) {
		if (IS_ENABLED(CONFIG_PHY_STANDBY)) {
			HAL_GPIO_WritePin(nCANSTBY_Port, nCANSTBY_Pin,
							  !GPIO_INIT_STATE(nCANSTBY_Active_High));
		}
		if (IS_ENABLED(CONFIG_PHY_SILENT)) {
			HAL_GPIO_WritePin(CAN_S_GPIO_Port, CAN_S_Pin, GPIO_PIN_RESET);
		}
	} else {
		if (IS_ENABLED(CONFIG_PHY_STANDBY)) {
			HAL_GPIO_WritePin(nCANSTBY_Port, nCANSTBY_Pin,
							  GPIO_INIT_STATE(nCANSTBY_Active_High));
		}
		if (IS_ENABLED(CONFIG_PHY_SILENT)) {
			HAL_GPIO_WritePin(CAN_S_GPIO_Port, CAN_S_Pin, GPIO_PIN_SET);
		}
	}
}

static void __maybe_unused legacy_termination_set(can_data_t *channel,
												  enum gs_can_termination_state state)
{
	UNUSED(channel);

	HAL_GPIO_WritePin(TERM_GPIO_Port, TERM_Pin, state ?
					  !GPIO_INIT_STATE(TERM_Active_High) : GPIO_INIT_STATE(TERM_Active_High));
}

const struct board_config config = {
#ifdef CONFIG_FDCAN
    .channel[0] = {
        .interface = &hfdcan1,
        .led_tx_port = LED_CAN1TX_GPIO_Port,
        .led_tx_pin = LED_CAN1TX_Pin,
        .led_tx_active_high = 1,
        .led_rx_port = LED_CAN1RX_GPIO_Port,
        .led_rx_pin = LED_CAN1RX_Pin,
        .led_rx_active_high = 1,
    },
    .channel[1] = {
        .interface = &hfdcan2,
        .led_tx_port = LED_CAN2TX_GPIO_Port,
        .led_tx_pin = LED_CAN2TX_Pin,
        .led_tx_active_high = 1,
        .led_rx_port = LED_CAN2RX_GPIO_Port,
        .led_rx_pin = LED_CAN2RX_Pin,
        .led_rx_active_high = 1,
    },
    .channel[2] = {
        .interface = &hfdcan3,
        .led_tx_port = LED_CAN3TX_GPIO_Port,
        .led_tx_pin = LED_CAN3TX_Pin,
        .led_tx_active_high = 1,
        .led_rx_port = LED_CAN3RX_GPIO_Port,
        .led_rx_pin = LED_CAN3RX_Pin,
        .led_rx_active_high = 1,
    },
#else
	.channel[0] = {
		.interface = CAN_INTERFACE,
        .led_tx_port = LEDTX_GPIO_Port,
        .led_tx_pin = LEDTX_Pin,
        .led_tx_active_high = 1,
        .led_rx_port = LEDRX_GPIO_Port,
        .led_rx_pin = LEDRX_Pin,
        .led_rx_active_high = 1,
	},
#endif
	SET_PHY_POWER_FN(legacy_phy_power_set)
	SET_TERMINATION_FN(legacy_termination_set)
};
