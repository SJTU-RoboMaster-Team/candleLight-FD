project(STM32_USB_Device_Library)

set(SOURCES
    Core/Inc/usbd_def.h
    Core/Inc/usbd_ctlreq.h
    Core/Src/usbd_ctlreq.c
    Core/Inc/usbd_ioreq.h
    Core/Src/usbd_ioreq.c
    Core/Inc/usbd_core.h
    Core/Src/usbd_core.c
)

set(INCLUDE_DIRS
    Core/Inc/
    config/
)

if(NOT DEFINED BUILD_canable OR BUILD_canable OR
   NOT DEFINED BUILD_canalyze OR BUILD_canalyze OR
   NOT DEFINED BUILD_cannette OR BUILD_cannette OR
   NOT DEFINED BUILD_cantact OR BUILD_cantact OR
   NOT DEFINED BUILD_falcan OR BUILD_falcan OR
   NOT DEFINED BUILD_usb2can OR BUILD_usb2can)
    add_library(STM32_USB_Device_Library_STM32F042x6 STATIC ${SOURCES})
    target_include_directories(STM32_USB_Device_Library_STM32F042x6 PUBLIC ${INCLUDE_DIRS})
    target_compile_options(STM32_USB_Device_Library_STM32F042x6 PRIVATE ${CPUFLAGS_F0} -Wno-unused-parameter -DSTM32F0)
    target_link_libraries(STM32_USB_Device_Library_STM32F042x6 PRIVATE STM32_HAL_STM32F042x6)
endif()

if(NOT DEFINED BUILD_CANable_MKS OR BUILD_CANable_MKS OR
   NOT DEFINED BUILD_CONVERTDEVICE_xCAN OR BUILD_CONVERTDEVICE_xCAN OR
   NOT DEFINED BUILD_DSD_TECH_SH_C30A OR BUILD_DSD_TECH_SH_C30A OR
   NOT DEFINED BUILD_FYSETC_UCAN OR BUILD_FYSETC_UCAN OR
   NOT DEFINED BUILD_can_module_com_classic OR BUILD_can_module_com_classic OR
   NOT DEFINED BUILD_candleLight OR BUILD_candleLight)
    add_library(STM32_USB_Device_Library_STM32F072xB STATIC ${SOURCES})
    target_include_directories(STM32_USB_Device_Library_STM32F072xB PUBLIC ${INCLUDE_DIRS})
    target_compile_options(STM32_USB_Device_Library_STM32F072xB PRIVATE ${CPUFLAGS_F0} -Wno-unused-parameter -DSTM32F0)
    target_link_libraries(STM32_USB_Device_Library_STM32F072xB PRIVATE STM32_HAL_STM32F072xB)
endif()

if(NOT DEFINED BUILD_STM32F4_DevBoard OR BUILD_STM32F4_DevBoard)
    add_library(STM32_USB_Device_Library_STM32F407xE STATIC ${SOURCES})
    target_include_directories(STM32_USB_Device_Library_STM32F407xE PUBLIC ${INCLUDE_DIRS})
    target_compile_options(STM32_USB_Device_Library_STM32F407xE PRIVATE ${CPUFLAGS_F4} -Wno-unused-parameter -DSTM32F4)
    target_link_libraries(STM32_USB_Device_Library_STM32F407xE PRIVATE STM32_HAL_STM32F407xE)
endif()

if(BUILD_CONVERTDEVICE_xCANFD OR BUILD_budgetcan)
    add_library(STM32_USB_Device_Library_STM32G0B1xx STATIC ${SOURCES})
    target_include_directories(STM32_USB_Device_Library_STM32G0B1xx PUBLIC ${INCLUDE_DIRS})
    target_compile_options(STM32_USB_Device_Library_STM32G0B1xx PRIVATE ${CPUFLAGS_G0} -Wno-unused-parameter -DSTM32G0)
    target_link_libraries(STM32_USB_Device_Library_STM32G0B1xx PRIVATE STM32_HAL_STM32G0B1xx)
endif()

if(NOT DEFINED BUILD_JiaoLoong_G4_3FDCAN OR BUILD_JiaoLoong_G4_3FDCAN)
    add_library(STM32_USB_Device_Library_STM32G474xx STATIC ${SOURCES})
    target_include_directories(STM32_USB_Device_Library_STM32G474xx PUBLIC ${INCLUDE_DIRS})
    target_compile_options(STM32_USB_Device_Library_STM32G474xx PRIVATE ${CPUFLAGS_G4} -Wno-unused-parameter -DSTM32G4)
    target_link_libraries(STM32_USB_Device_Library_STM32G474xx PRIVATE STM32_HAL_STM32G474xx)
endif()
