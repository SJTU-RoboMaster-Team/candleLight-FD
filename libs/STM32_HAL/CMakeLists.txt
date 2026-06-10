project(STM32_HAL)

set(STM32F0_HALDIR stm32f0xx-hal-driver)
set(STM32F4_HALDIR stm32f4xx-hal-driver)
set(STM32G0_HALDIR stm32g0xx-hal-driver)
set(STM32G4_HALDIR stm32g4xx-hal-driver)

set(STM32F0_SOURCES
    config/stm32f0xx_hal_conf.h

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_def.h
    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_can.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_can.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_cortex.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_cortex.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_flash_ex.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_flash_ex.c
    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_flash.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_flash.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_gpio_ex.h
    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_gpio.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_gpio.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_pcd_ex.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_pcd_ex.c
    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_pcd.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_pcd.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_rcc.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_rcc.c
    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_rcc_ex.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_rcc_ex.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_tim_ex.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_tim_ex.c
    ${STM32F0_HALDIR}/Inc/stm32f0xx_hal_tim.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_hal_tim.c

    ${STM32F0_HALDIR}/Inc/stm32f0xx_ll_usb.h
    ${STM32F0_HALDIR}/Src/stm32f0xx_ll_usb.c

    src/cmsis/system_stm32f0xx.c
    ${STM32F0_HALDIR}/Inc/Legacy/stm32_hal_legacy.h

    include/cmsis/cmsis_compiler.h
    include/cmsis/cmsis_device.h
    include/cmsis/cmsis_gcc.h
    include/cmsis/cmsis_version.h
    include/cmsis/core_cm0.h
    include/cmsis/device/stm32f0xx.h
    include/cmsis/device/stm32f042x6.h
    include/cmsis/device/stm32f072xb.h
    include/cmsis/device/system_stm32f0xx.h
)


set(STM32F4_SOURCES
    config/stm32f4xx_hal_conf.h

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_def.h
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_can.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_can.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_cortex.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_cortex.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_flash_ex.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_flash_ex.c
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_flash.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_flash.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_gpio_ex.h
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_gpio.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_gpio.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_pcd_ex.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_pcd_ex.c
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_pcd.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_pcd.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_rcc.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_rcc.c
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_rcc_ex.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_rcc_ex.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_pwr.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_pwr.c
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_pwr_ex.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_pwr_ex.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_tim_ex.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_tim_ex.c
    ${STM32F4_HALDIR}/Inc/stm32f4xx_hal_tim.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_hal_tim.c

    ${STM32F4_HALDIR}/Inc/stm32f4xx_ll_usb.h
    ${STM32F4_HALDIR}/Src/stm32f4xx_ll_usb.c

    src/cmsis/system_stm32f4xx.c
    ${STM32F4_HALDIR}/Inc/Legacy/stm32_hal_legacy.h

    include/cmsis/cmsis_compiler.h
    include/cmsis/cmsis_device.h
    include/cmsis/cmsis_gcc.h
    include/cmsis/cmsis_version.h
    include/cmsis/core_cm4.h
    include/cmsis/device/stm32f4xx.h
    include/cmsis/device/stm32f407xx.h
    include/cmsis/device/system_stm32f4xx.h
)

set(STM32G0_SOURCES
    config/stm32g0xx_hal_conf.h

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_def.h
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_fdcan.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_fdcan.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_cortex.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_cortex.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_flash_ex.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_flash_ex.c
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_flash.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_flash.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_gpio_ex.h
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_gpio.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_gpio.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_pcd_ex.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_pcd_ex.c
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_pcd.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_pcd.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_rcc.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_rcc.c
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_rcc_ex.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_rcc_ex.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_pwr.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_pwr.c
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_pwr_ex.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_pwr_ex.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_tim_ex.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_tim_ex.c
    ${STM32G0_HALDIR}/Inc/stm32g0xx_hal_tim.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_hal_tim.c

    ${STM32G0_HALDIR}/Inc/stm32g0xx_ll_usb.h
    ${STM32G0_HALDIR}/Src/stm32g0xx_ll_usb.c

    src/cmsis/system_stm32g0xx.c
    ${STM32G0_HALDIR}/Inc/Legacy/stm32_hal_legacy.h

    include/cmsis/cmsis_compiler.h
    include/cmsis/cmsis_device.h
    include/cmsis/cmsis_gcc.h
    include/cmsis/cmsis_version.h
    include/cmsis/core_cm0plus.h
    include/cmsis/device/stm32g0xx.h
    include/cmsis/device/stm32g0b1xx.h
    include/cmsis/device/system_stm32g0xx.h
)

set(STM32G4_SOURCES
    config/stm32g4xx_hal_conf.h

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_def.h
    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_fdcan.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_fdcan.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_cortex.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_cortex.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_gpio_ex.h
    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_gpio.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_gpio.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_pcd_ex.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_pcd_ex.c
    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_pcd.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_pcd.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_rcc.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_rcc.c
    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_rcc_ex.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_rcc_ex.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_pwr.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_pwr.c
    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_pwr_ex.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_pwr_ex.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_tim_ex.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_tim_ex.c
    ${STM32G4_HALDIR}/Inc/stm32g4xx_hal_tim.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_hal_tim.c

    ${STM32G4_HALDIR}/Inc/stm32g4xx_ll_usb.h
    ${STM32G4_HALDIR}/Src/stm32g4xx_ll_usb.c

    src/cmsis/system_stm32g4xx.c
    ${STM32G4_HALDIR}/Inc/Legacy/stm32_hal_legacy.h

    include/cmsis/cmsis_compiler.h
    include/cmsis/cmsis_device.h
    include/cmsis/cmsis_gcc.h
    include/cmsis/cmsis_version.h
    include/cmsis/core_cm4.h
    include/cmsis/device/stm32g4xx.h
    include/cmsis/device/stm32g474xx.h
    include/cmsis/device/system_stm32g4xx.h
)

set(INCLUDE_DIRS
    include/
    include/cmsis
    include/cmsis/device
    config/
)

if(NOT DEFINED BUILD_canable OR BUILD_canable OR
   NOT DEFINED BUILD_canalyze OR BUILD_canalyze OR
   NOT DEFINED BUILD_cannette OR BUILD_cannette OR
   NOT DEFINED BUILD_cantact OR BUILD_cantact OR
   NOT DEFINED BUILD_falcan OR BUILD_falcan OR
   NOT DEFINED BUILD_usb2can OR BUILD_usb2can)
    add_library(STM32_HAL_STM32F042x6 STATIC ${STM32F0_SOURCES})
    target_include_directories(STM32_HAL_STM32F042x6 PUBLIC ${INCLUDE_DIRS} ${STM32F0_HALDIR}/Inc)
    target_compile_options(STM32_HAL_STM32F042x6 PRIVATE ${CPUFLAGS_F0} -Wno-unused-parameter)
    target_compile_definitions(STM32_HAL_STM32F042x6 PUBLIC STM32F042x6)
endif()

if(NOT DEFINED BUILD_CANable_MKS OR BUILD_CANable_MKS OR
   NOT DEFINED BUILD_CONVERTDEVICE_xCAN OR BUILD_CONVERTDEVICE_xCAN OR
   NOT DEFINED BUILD_DSD_TECH_SH_C30A OR BUILD_DSD_TECH_SH_C30A OR
   NOT DEFINED BUILD_FYSETC_UCAN OR BUILD_FYSETC_UCAN OR
   NOT DEFINED BUILD_can_module_com_classic OR BUILD_can_module_com_classic OR
   NOT DEFINED BUILD_candleLight OR BUILD_candleLight)
    add_library(STM32_HAL_STM32F072xB STATIC ${STM32F0_SOURCES})
    target_include_directories(STM32_HAL_STM32F072xB PUBLIC ${INCLUDE_DIRS} ${STM32F0_HALDIR}/Inc)
    target_compile_options(STM32_HAL_STM32F072xB PRIVATE ${CPUFLAGS_F0} -Wno-unused-parameter)
    target_compile_definitions(STM32_HAL_STM32F072xB PUBLIC STM32F072xB)
endif()

if(NOT DEFINED BUILD_STM32F4_DevBoard OR BUILD_STM32F4_DevBoard)
    add_library(STM32_HAL_STM32F407xE STATIC ${STM32F4_SOURCES})
    target_include_directories(STM32_HAL_STM32F407xE PUBLIC ${INCLUDE_DIRS} ${STM32F4_HALDIR}/Inc)
    target_compile_options(STM32_HAL_STM32F407xE PRIVATE ${CPUFLAGS_F4} -Wno-unused-parameter)
    target_compile_definitions(STM32_HAL_STM32F407xE PUBLIC STM32F407xx)
endif()

if(BUILD_CONVERTDEVICE_xCANFD OR BUILD_budgetcan)
    add_library(STM32_HAL_STM32G0B1xx STATIC ${STM32G0_SOURCES})
    target_include_directories(STM32_HAL_STM32G0B1xx PUBLIC ${INCLUDE_DIRS} ${STM32G0_HALDIR}/Inc)
    target_compile_options(STM32_HAL_STM32G0B1xx PRIVATE ${CPUFLAGS_G0} -Wno-unused-parameter)
    target_compile_definitions(STM32_HAL_STM32G0B1xx PUBLIC STM32G0B1xx)
endif()

if(NOT DEFINED BUILD_JiaoLoong_G4_3FDCAN OR BUILD_JiaoLoong_G4_3FDCAN)
    add_library(STM32_HAL_STM32G474xx STATIC ${STM32G4_SOURCES})
    target_include_directories(STM32_HAL_STM32G474xx PUBLIC ${INCLUDE_DIRS} ${STM32G4_HALDIR}/Inc)
    target_compile_options(STM32_HAL_STM32G474xx PRIVATE ${CPUFLAGS_G4} -Wno-unused-parameter)
    target_compile_definitions(STM32_HAL_STM32G474xx PUBLIC STM32G474xx)
endif()

