cmake_minimum_required(VERSION 3.21)

# CMSIS core
target_include_directories(${PROJECT_NAME} PRIVATE
    cmsis_core/Core/Include
)

# CMSIS device
target_include_directories(${PROJECT_NAME} PRIVATE
    cmsis_device_f4/Include
)

# ST drivers
target_include_directories(${PROJECT_NAME} PRIVATE
    stm32f4xx_hal_driver/Inc
)

target_sources(${PROJECT_NAME} PRIVATE
    stm32f4xx_hal_driver/Src/stm32f4xx_hal.c
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_cortex.c
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc.c
    stm32f4xx_hal_driver/Src/stm32f4xx_ll_gpio.c
    stm32f4xx_hal_driver/Src/stm32f4xx_ll_utils.c
)
