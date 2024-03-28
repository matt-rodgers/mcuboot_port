cmake_minimum_required(VERSION 3.21)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
)

target_sources(${PROJECT_NAME} PRIVATE
    app_main.c
    board.c
    LED_LedDriver.c
)
