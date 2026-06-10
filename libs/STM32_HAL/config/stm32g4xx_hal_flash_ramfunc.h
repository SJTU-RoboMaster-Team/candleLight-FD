#pragma once

/* This project does not use the optional STM32G4 FLASH RAMFUNC APIs.
 * Keep this compatibility header so stm32g4xx_hal_flash.h can provide
 * latency macros required by the RCC HAL without importing unused sources.
 */
