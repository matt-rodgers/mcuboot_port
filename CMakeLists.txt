cmake_minimum_required(VERSION 3.21)
project(stm32-starter LANGUAGES C CXX ASM)

# Set project name (used for naming output files)
set(PROJECT_NAME application)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export all compile commands to a JSON file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

# Global compile options
add_compile_options(
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    -g3
    -Os
)

# List source files
add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/source/app_main.c
    ${CMAKE_SOURCE_DIR}/source/LED_LedDriver.c
    ${CMAKE_SOURCE_DIR}/source/board.c
    ${CMAKE_SOURCE_DIR}/source/newlib_stubs.c
)

# Add subdirectories
add_subdirectory(third-party/ST)
target_link_libraries(${PROJECT_NAME} PRIVATE st)

# List include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/source
)

# Define location of linker script. Note this is in ST subdirectory, not sure if there's
# a better way to add this in the subdirectory's CMakeLists file.
set(LINKER_SCRIPTS
    ${CMAKE_SOURCE_DIR}/third-party/ST/STM32F446ZEHx_FLASH.ld
)

# Specify dependency of target on linker script
set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX .elf
    LINK_DEPENDS "${LINKER_SCRIPTS}"
)

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE
    -T${CMAKE_SOURCE_DIR}/third-party/ST/STM32F446ZEHx_FLASH.ld
    LINKER:--print-memory-usage
    LINKER:-Map,${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
)
