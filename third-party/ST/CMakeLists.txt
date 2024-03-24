cmake_minimum_required(VERSION 3.21)
project(target-st LANGUAGES C CXX ASM)

# Suppress warnings for ST code
add_compile_options(
    -Wno-unused-parameter
)

add_library(st OBJECT
    ${PROJECT_SOURCE_DIR}/Core/Src/main.c
    ${PROJECT_SOURCE_DIR}/Core/Src/stm32f4xx_it.c
    ${PROJECT_SOURCE_DIR}/Core/Src/system_stm32f4xx.c
    ${PROJECT_SOURCE_DIR}/startup_stm32f446xx.s
    ${PROJECT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c
    ${PROJECT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c
    ${PROJECT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c
    ${PROJECT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c
)

# Note: may be able to change some of these paths to PRIVATE
target_include_directories(st PUBLIC
    ${PROJECT_SOURCE_DIR}/Core/Inc
    ${PROJECT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Include
)

# Required to find app_main.h. Not sure if there's a better way to do this...
target_include_directories(st PRIVATE
    ${CMAKE_SOURCE_DIR}/source
)
