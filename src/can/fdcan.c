//
// Created by DrownFish on 2026/6/10.
//

#include <string.h>

#include "board.h"
#include "can.h"
#include "can_common.h"
#include "config.h"
#include "device.h"
#include "gs_usb.h"
#include "timer.h"

extern void Error_Handler(void);

static uint8_t fdcan_dlc_to_len(uint32_t dlc) {
    static const uint8_t dlc_to_len[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
    };

    if (dlc < ARRAY_SIZE(dlc_to_len))
        return dlc_to_len[dlc];

    return 0;
}

const struct gs_device_bt_const CAN_btconst = {
    .feature =
    GS_CAN_FEATURE_LISTEN_ONLY |
    GS_CAN_FEATURE_LOOP_BACK |
    GS_CAN_FEATURE_ONE_SHOT |
    GS_CAN_FEATURE_HW_TIMESTAMP |
    GS_CAN_FEATURE_IDENTIFY |
    GS_CAN_FEATURE_FD |
    GS_CAN_FEATURE_BT_CONST_EXT |
    GS_CAN_FEATURE_PAD_PKTS_TO_MAX_PKT_SIZE |
    (IS_ENABLED(CONFIG_TERMINATION) ? GS_CAN_FEATURE_TERMINATION : 0) |
#ifdef CONFIG_CAN_FILTER
    GS_CAN_FEATURE_FILTER |
#endif
    0,
    .fclk_can = CAN_CLOCK_SPEED,
    .btc = {
        .tseg1_min = 1,
        .tseg1_max = 16,
        .tseg2_min = 1,
        .tseg2_max = 8,
        .sjw_max = 4,
        .brp_min = 1,
        .brp_max = 1024,
        .brp_inc = 1,
    },
};

const struct gs_device_bt_const_extended CAN_btconst_ext = {
    .feature =
    GS_CAN_FEATURE_LISTEN_ONLY |
    GS_CAN_FEATURE_LOOP_BACK |
    GS_CAN_FEATURE_ONE_SHOT |
    GS_CAN_FEATURE_HW_TIMESTAMP |
    GS_CAN_FEATURE_IDENTIFY |
    GS_CAN_FEATURE_FD |
    GS_CAN_FEATURE_BT_CONST_EXT |
    GS_CAN_FEATURE_PAD_PKTS_TO_MAX_PKT_SIZE |
    (IS_ENABLED(CONFIG_TERMINATION) ? GS_CAN_FEATURE_TERMINATION : 0) |
#ifdef CONFIG_CAN_FILTER
    GS_CAN_FEATURE_FILTER |
#endif
    0,
    .fclk_can = CAN_CLOCK_SPEED,
    .btc = {
        .tseg1_min = 1,
        .tseg1_max = 256,
        .tseg2_min = 1,
        .tseg2_max = 128,
        .sjw_max = 128,
        .brp_min = 1,
        .brp_max = 512,
        .brp_inc = 1,
    },
    .dbtc = {
        .tseg1_min = 1,
        .tseg1_max = 32,
        .tseg2_min = 1,
        .tseg2_max = 16,
        .sjw_max = 16,
        .brp_min = 1,
        .brp_max = 32,
        .brp_inc = 1,
    },
};

#ifdef CONFIG_CAN_FILTER
const struct gs_device_filter_info CAN_filter_info = {
    .dev = GS_DEVICE_FILTER_DEV_FDCAN,
};
#endif

void general_fdcan_init_config(const can_data_t* channel) {
    channel->instance->Init.ClockDivider = FDCAN_CLOCK_DIV1;
    channel->instance->Init.FrameFormat = FDCAN_FRAME_FD_BRS;
    channel->instance->Init.Mode = FDCAN_MODE_NORMAL;
    channel->instance->Init.AutoRetransmission = DISABLE;
    channel->instance->Init.TransmitPause = DISABLE;
    channel->instance->Init.ProtocolException = DISABLE;
    channel->instance->Init.NominalPrescaler = 4;
    channel->instance->Init.NominalSyncJumpWidth = 5;
    channel->instance->Init.NominalTimeSeg1 = 34;
    channel->instance->Init.NominalTimeSeg2 = 5;
    channel->instance->Init.DataPrescaler = 1;
    channel->instance->Init.DataSyncJumpWidth = 4;
    channel->instance->Init.DataTimeSeg1 = 15;
    channel->instance->Init.DataTimeSeg2 = 4;
    channel->instance->Init.StdFiltersNbr = 1;
    channel->instance->Init.ExtFiltersNbr = 1;
    channel->instance->Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
}

void can_init(can_data_t* channel, const struct board_channel_config* channel_config) {
    device_can_init(channel, channel_config);
    general_fdcan_init_config(channel);
}

#ifdef CONFIG_CAN_FILTER
void can_set_filter(can_data_t* channel, const struct gs_device_filter* filter) {
    channel->filter.fdcan = filter->fdcan;
}
#endif

void can_set_bittiming(can_data_t* channel, const struct gs_device_bittiming* timing) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;

    fdcan->Init.NominalPrescaler = timing->brp;
    fdcan->Init.NominalSyncJumpWidth = timing->sjw;
    fdcan->Init.NominalTimeSeg1 = timing->prop_seg + timing->phase_seg1;
    fdcan->Init.NominalTimeSeg2 = timing->phase_seg2;
}

void can_set_data_bittiming(can_data_t* channel, const struct gs_device_bittiming* timing) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;

    fdcan->Init.DataPrescaler = timing->brp;
    fdcan->Init.DataSyncJumpWidth = timing->sjw;
    fdcan->Init.DataTimeSeg1 = timing->prop_seg + timing->phase_seg1;
    fdcan->Init.DataTimeSeg2 = timing->phase_seg2;
}

static bool can_apply_filter(const can_data_t* channel) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;
    FDCAN_FilterTypeDef filter = {0};

    filter.IdType = FDCAN_STANDARD_ID;
    filter.FilterIndex = 0;
    filter.FilterType = FDCAN_FILTER_MASK;
    filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    filter.FilterID1 = 0x000;
    filter.FilterID2 = 0x000;

    if (HAL_FDCAN_ConfigFilter(fdcan, &filter) != HAL_OK) {
        Error_Handler();
    }

    filter.IdType = FDCAN_EXTENDED_ID;
    filter.FilterIndex = 0;
    filter.FilterType = FDCAN_FILTER_MASK;
    filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    filter.FilterID1 = 0x00000000;
    filter.FilterID2 = 0x00000000;

    if (HAL_FDCAN_ConfigFilter(fdcan, &filter) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_FDCAN_ConfigGlobalFilter(fdcan,
                                     FDCAN_ACCEPT_IN_RX_FIFO0,
                                     FDCAN_ACCEPT_IN_RX_FIFO0,
                                     FDCAN_FILTER_REMOTE,
                                     FDCAN_FILTER_REMOTE) != HAL_OK) {
        Error_Handler();
    }

    return true;
}

void can_enable(can_data_t* channel) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;

    if (HAL_FDCAN_Init(fdcan) != HAL_OK) {
        Error_Handler();
    }
    can_apply_filter(channel);

    if (HAL_FDCAN_Start(fdcan) != HAL_OK) {
        Error_Handler();
    }

    board_phy_power_set(channel, true);
}

void can_disable(can_data_t* channel) {
    board_phy_power_set(channel, false);
    HAL_FDCAN_Stop(channel->instance);
}

bool can_is_enabled(can_data_t* channel) {
    const FDCAN_HandleTypeDef* fdcan = channel->instance;
    return fdcan->ErrorCode == HAL_FDCAN_ERROR_NONE && fdcan->State == HAL_FDCAN_STATE_BUSY;
}

bool can_is_rx_pending(can_data_t* channel) {
    return HAL_FDCAN_GetRxFifoFillLevel(channel->instance, FDCAN_RX_FIFO0) > 0;
}

bool can_receive(can_data_t* channel, struct gs_host_frame* rx_frame) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;
    FDCAN_RxHeaderTypeDef header = {0};
    uint8_t data[64] = {0};

    if (HAL_FDCAN_GetRxMessage(fdcan, FDCAN_RX_FIFO0, &header, data) != HAL_OK) {
        return false;
    }

    rx_frame->echo_id = 0xFFFFFFFF;
    rx_frame->can_id = header.Identifier;
    rx_frame->can_dlc = header.DataLength;
    rx_frame->channel = can_channel_get_nr(channel);
    rx_frame->flags = 0;

    if (header.IdType == FDCAN_EXTENDED_ID) {
        rx_frame->can_id |= CAN_EFF_FLAG;
    }

    if (header.RxFrameType == FDCAN_REMOTE_FRAME) {
        rx_frame->can_id |= CAN_RTR_FLAG;
    }

    if (header.FDFormat == FDCAN_FD_CAN) {
        rx_frame->flags |= GS_CAN_FLAG_FD;
    }

    if (header.BitRateSwitch == FDCAN_BRS_ON) {
        rx_frame->flags |= GS_CAN_FLAG_BRS;
    }

    memcpy(rx_frame->canfd->data, data, fdcan_dlc_to_len(header.DataLength));

    return true;
}

bool can_send(can_data_t* channel, struct gs_host_frame* frame) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;
    FDCAN_TxHeaderTypeDef header = {0};

    header.Identifier = (frame->can_id & CAN_EFF_FLAG) ? (frame->can_id & 0x1FFFFFFF) : (frame->can_id & 0x7FF);
    header.IdType = (frame->can_id & CAN_EFF_FLAG) ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
    header.TxFrameType = (frame->can_id & CAN_RTR_FLAG) ? FDCAN_REMOTE_FRAME : FDCAN_DATA_FRAME;
    header.DataLength = frame->can_dlc;
    header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    header.BitRateSwitch = (frame->flags & GS_CAN_FLAG_BRS) ? FDCAN_BRS_ON : FDCAN_BRS_OFF;
    header.FDFormat = (frame->flags & GS_CAN_FLAG_FD) ? FDCAN_FD_CAN : FDCAN_CLASSIC_CAN;
    header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    header.MessageMarker = 0;

    if (HAL_FDCAN_AddMessageToTxFifoQ(fdcan, &header, frame->canfd->data) != HAL_OK) {
        return false;
    }

    return true;
}

uint32_t can_get_error_status(can_data_t* channel) {
    return HAL_FDCAN_GetError(channel->instance);
}

bool can_parse_error_status(can_data_t* channel, struct gs_host_frame* frame, uint32_t err) {
    (void)channel;
    (void)frame;
    (void)err;

    return false;
}
