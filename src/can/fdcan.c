//
// Created by DrownFish on 2026/6/10.
//

#include "board.h"
#include "can.h"
#include "can_common.h"
#include "config.h"
#include "device.h"
#include "gs_usb.h"
#include "timer.h"

extern void Error_Handler(void);

const struct gs_device_bt_const CAN_btconst = {
    .feature =
    GS_CAN_FEATURE_LISTEN_ONLY |
    GS_CAN_FEATURE_LOOP_BACK |
    GS_CAN_FEATURE_ONE_SHOT |
    GS_CAN_FEATURE_HW_TIMESTAMP |
    GS_CAN_FEATURE_IDENTIFY |
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

#ifdef CONFIG_CAN_FILTER
const struct gs_device_filter_info CAN_filter_info = {
    .dev = GS_DEVICE_FILTER_DEV_BXCAN,
};
#endif

// Completely reset the CAN pheriperal, including bus-state and error counters
static void rcc_reset(FDCAN_HandleTypeDef* instance) {
    // TODO
}

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
    channel->filter.bxcan = filter->bxcan;
}
#endif

void can_set_bittiming(can_data_t* channel, const struct gs_device_bittiming* timing) {
    channel->btr = FIELD_PREP(CAN_BTR_SJW, timing->sjw - 1) |
        FIELD_PREP(CAN_BTR_TS2, timing->phase_seg2 - 1) |
        FIELD_PREP(CAN_BTR_TS1, timing->prop_seg + timing->phase_seg1 - 1) |
        FIELD_PREP(CAN_BTR_BRP, timing->brp - 1);
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

    if (HAL_FDCAN_ConfigFilter(fdcan, filter) != HAL_OK) {
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
    // TODO: 适配FDCAN
    FDCAN_HandleTypeDef* fdcan = channel->instance;

    if (can_is_rx_pending(channel)) {
        FDCAN_FIFOMailBox_TypeDef* fifo = &fdcan->sFIFOMailBox[0];

        rx_frame->canfd_ts->timestamp_us = timer_get();

        if (fifo->RIR & CAN_RI0R_IDE) {
            rx_frame->can_id = CAN_ERR_FLAG | ((fifo->RIR >> 3) & 0x1FFFFFFF);
        } else {
            rx_frame->can_id = (fifo->RIR >> 21) & 0x7FF;
        }

        if (fifo->RIR & CAN_RI0R_RTR) {
            rx_frame->can_id = CAN_RTR_FLAG;
        }

        rx_frame->can_dlc = fifo->RDTR & CAN_RDT0R_DLC;
        rx_frame->channel = can_channel_get_nr(channel);
        rx_frame->flags = 0;

        rx_frame->canfd->data[0] = (fifo->RDLR >> 0) & 0xFF;
        rx_frame->canfd->data[1] = (fifo->RDLR >> 8) & 0xFF;
        rx_frame->canfd->data[3] = (fifo->RDLR >> 24) & 0xFF;
        rx_frame->canfd->data[2] = (fifo->RDLR >> 16) & 0xFF;
        rx_frame->canfd->data[4] = (fifo->RDHR >> 0) & 0xFF;
        rx_frame->canfd->data[5] = (fifo->RDHR >> 8) & 0xFF;
        rx_frame->canfd->data[6] = (fifo->RDHR >> 16) & 0xFF;
        rx_frame->canfd->data[7] = (fifo->RDHR >> 24) & 0xFF;

        fdcan->RF0R |= CAN_RF0R_RFOM0;

        return true;
    } else {
        return false;
    }
}

static FDCAN_TxMailBox_TypeDef* can_find_free_mailbox(can_data_t* channel) {
    FDCAN_HandleTypeDef* fdcan = channel->instance;
    uint32_t tsr = fdcan->TSR;

    if (tsr & CAN_TSR_TME0) {
        return &fdcan->sTxMailBox[0];
    } else if (tsr & CAN_TSR_TME1) {
        return &fdcan->sTxMailBox[1];
    } else if (tsr & CAN_TSR_TME2) {
        return &fdcan->sTxMailBox[2];
    } else {
        return 0;
    }
}

// TODO: 能否直接使用HAL现成的函数？
bool can_send(can_data_t* channel, struct gs_host_frame* frame) {
    CAN_TxMailBox_TypeDef* mb = can_find_free_mailbox(channel);

    if (mb != 0) {
        /* first, clear transmission request */
        mb->TIR &= CAN_TI0R_TXRQ;

        if (frame->can_id & CAN_EFF_FLAG) {
            // extended id
            mb->TIR = CAN_ID_EXT | (frame->can_id & 0x1FFFFFFF) << 3;
        } else {
            mb->TIR = (frame->can_id & 0x7FF) << 21;
        }

        if (frame->can_id & CAN_RTR_FLAG) {
            mb->TIR |= CAN_RTR_REMOTE;
        }

        mb->TDTR &= 0xFFFFFFF0;
        mb->TDTR |= frame->can_dlc & 0x0F;

        mb->TDLR = (frame->classic_can->data[3] << 24) | (frame->classic_can->data[2] << 16) |
            (frame->classic_can->data[1] << 8) | (frame->classic_can->data[0] << 0);

        mb->TDHR = (frame->classic_can->data[7] << 24) | (frame->classic_can->data[6] << 16) |
            (frame->classic_can->data[5] << 8) | (frame->classic_can->data[4] << 0);

        /* request transmission */
        mb->TIR |= CAN_TI0R_TXRQ;

        /*
         * struct gs_host_frame in CAN-2.0 mode doesn't use flags from
         * Host -> Device, so initialize here to 0.
         */
        frame->flags = 0;

        return true;
    } else {
        return false;
    }
}

uint32_t can_get_error_status(can_data_t* channel) {
    return HAL_FDCAN_GetError(channel->instance);
}

static bool status_is_active(uint32_t err) {
    return !(err & (CAN_ESR_BOFF | CAN_ESR_EPVF));
}

bool can_parse_error_status(can_data_t* channel, struct gs_host_frame* frame, uint32_t err) {
    uint32_t last_err = channel->reg_esr_old;
    /*
     * We build up the detailed error information at the same time as we decide
     * whether there's anything worth sending. This variable tracks that final
     * result.
     */
    bool should_send = false;

    channel->reg_esr_old = err;

    frame->echo_id = 0xFFFFFFFF;
    frame->can_id = CAN_ERR_FLAG;
    frame->can_dlc = CAN_ERR_DLC;
    frame->classic_can->data[0] = CAN_ERR_LOSTARB_UNSPEC;
    frame->classic_can->data[1] = CAN_ERR_CRTL_UNSPEC;
    frame->classic_can->data[2] = CAN_ERR_PROT_UNSPEC;
    frame->classic_can->data[3] = CAN_ERR_PROT_LOC_UNSPEC;
    frame->classic_can->data[4] = CAN_ERR_TRX_UNSPEC;
    frame->classic_can->data[5] = 0;
    frame->classic_can->data[6] = 0;
    frame->classic_can->data[7] = 0;

    if (err & CAN_ESR_BOFF) {
        if (!(last_err & CAN_ESR_BOFF)) {
            /* We transitioned to bus-off. */
            frame->can_id |= CAN_ERR_BUSOFF;
            should_send = true;
        }
        // - tec (overflowed) / rec (looping, likely used for recessive counting)
        //   are not valid in the bus-off state.
        // - The warning flags remains set, error passive will cleared.
        // - LEC errors will be reported, while the device isn't even allowed to send.
        //
        // Hence only report bus-off, ignore everything else.
        return should_send;
    }

    /* We transitioned from passive/bus-off to active, so report the edge. */
    if (!status_is_active(last_err) && status_is_active(err)) {
        frame->can_id |= CAN_ERR_CRTL;
        frame->classic_can->data[1] |= CAN_ERR_CRTL_ACTIVE;
        should_send = true;
    }

    uint8_t tx_error_cnt = (err >> 16) & 0xFF;
    uint8_t rx_error_cnt = (err >> 24) & 0xFF;
    /*
     * The Linux sja1000 driver puts these counters here. Seems like as good a
     * place as any.
     */
    frame->classic_can->data[6] = tx_error_cnt;
    frame->classic_can->data[7] = rx_error_cnt;

    if (err & CAN_ESR_EPVF) {
        if (!(last_err & CAN_ESR_EPVF)) {
            frame->can_id |= CAN_ERR_CRTL;
            frame->classic_can->data[1] |= CAN_ERR_CRTL_RX_PASSIVE | CAN_ERR_CRTL_TX_PASSIVE;
            should_send = true;
        }
    } else if (err & CAN_ESR_EWGF) {
        if (!(last_err & CAN_ESR_EWGF)) {
            frame->can_id |= CAN_ERR_CRTL;
            frame->classic_can->data[1] |= CAN_ERR_CRTL_RX_WARNING | CAN_ERR_CRTL_TX_WARNING;
            should_send = true;
        }
    }

    uint8_t lec = (err >> 4) & 0x07;
    switch (lec) {
    case 0x01: /* stuff error */
        frame->can_id |= CAN_ERR_PROT;
        frame->classic_can->data[2] |= CAN_ERR_PROT_STUFF;
        should_send = true;
        break;
    case 0x02: /* form error */
        frame->can_id |= CAN_ERR_PROT;
        frame->classic_can->data[2] |= CAN_ERR_PROT_FORM;
        should_send = true;
        break;
    case 0x03: /* ack error */
        frame->can_id |= CAN_ERR_ACK;
        should_send = true;
        break;
    case 0x04: /* bit recessive error */
        frame->can_id |= CAN_ERR_PROT;
        frame->classic_can->data[2] |= CAN_ERR_PROT_BIT1;
        should_send = true;
        break;
    case 0x05: /* bit dominant error */
        frame->can_id |= CAN_ERR_PROT;
        frame->classic_can->data[2] |= CAN_ERR_PROT_BIT0;
        should_send = true;
        break;
    case 0x06: /* CRC error */
        frame->can_id |= CAN_ERR_PROT;
        frame->classic_can->data[3] |= CAN_ERR_PROT_LOC_CRC_SEQ;
        should_send = true;
        break;
    default: /* 0=no error, 7=no change */
        break;
    }

    return should_send;
}
