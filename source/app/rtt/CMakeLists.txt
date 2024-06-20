cmake_minimum_required(VERSION 3.21)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
)

target_sources(${PROJECT_NAME} PRIVATE
    SEGGER_RTT.c
    SEGGER_RTT_printf.c
)
