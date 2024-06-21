cmake_minimum_required(VERSION 3.21)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    mcuboot_port/include
)

target_sources(${PROJECT_NAME} PRIVATE
    app_main.c
    serial.c
    led.c
)

add_subdirectory(rtt)
