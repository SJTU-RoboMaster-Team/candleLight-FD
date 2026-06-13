//
// Created by DrownFish on 2026/6/13.
//
#include "hal_include.h"

extern void Error_Handler(void);

void HAL_MspInit(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    HAL_PWREx_DisableUCPDDeadBattery();
}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED = 0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    if (fdcanHandle->Instance == FDCAN1) {
        /** Initializes the peripherals clocks
        */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        /* FDCAN1 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**FDCAN1 GPIO Configuration
        PB8-BOOT0     ------> FDCAN1_RX
        PB9     ------> FDCAN1_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* FDCAN1 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
    } else if (fdcanHandle->Instance == FDCAN2) {
        /** Initializes the peripherals clocks
        */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        /* FDCAN2 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**FDCAN2 GPIO Configuration
        PB12     ------> FDCAN2_RX
        PB13     ------> FDCAN2_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* FDCAN2 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
    } else if (fdcanHandle->Instance == FDCAN3) {
        /** Initializes the peripherals clocks
        */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        /* FDCAN3 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**FDCAN3 GPIO Configuration
        PA15     ------> FDCAN3_TX
        PB3     ------> FDCAN3_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF11_FDCAN3;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF11_FDCAN3;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* FDCAN3 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN3_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN3_IT0_IRQn);
    }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle) {
    if (fdcanHandle->Instance == FDCAN1) {
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN1 GPIO Configuration
        PB8-BOOT0     ------> FDCAN1_RX
        PB9     ------> FDCAN1_TX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);

        /* FDCAN1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
    } else if (fdcanHandle->Instance == FDCAN2) {
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN2 GPIO Configuration
        PB12     ------> FDCAN2_RX
        PB13     ------> FDCAN2_TX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12 | GPIO_PIN_13);

        /* FDCAN2 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
    } else if (fdcanHandle->Instance == FDCAN3) {
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN3 GPIO Configuration
        PA15     ------> FDCAN3_TX
        PB3     ------> FDCAN3_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);

        /* FDCAN3 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN3_IT0_IRQn);
    }
}