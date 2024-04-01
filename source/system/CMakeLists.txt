cmake_minimum_required(VERSION 3.21)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
)

target_sources(${PROJECT_NAME} PRIVATE
    startup_stm32f446zetx.s
    main.c
    stm32f4xx_hal_msp.c
    syscalls.c
    sysmem.c
    system_stm32f4xx.c
    stm32f4xx_it.c
)
