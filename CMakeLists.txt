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
    -Wno-old-style-declaration
    -g3
    -Os
)

add_executable(${PROJECT_NAME})

add_subdirectory(source)
add_subdirectory(third-party)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F446ZETX_FLASH.ld)

# Specify dependency of target on linker script
set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX .elf
    LINK_DEPENDS "${LINKER_SCRIPT}"
)

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    LINKER:--print-memory-usage
    LINKER:-Map,${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
)
