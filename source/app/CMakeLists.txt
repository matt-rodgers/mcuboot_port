cmake_minimum_required(VERSION 3.21)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    mcuboot_port/include
)

target_sources(${PROJECT_NAME} PRIVATE
    app_main.c
    serial.c
    led.c
    button.c
    mcuboot_port/src/keys.c
    mcuboot_port/src/flash_map_backend.c
    mcuboot_port/src/crc16.c
    mcuboot_port/src/base64.c
)

add_subdirectory(rtt)
