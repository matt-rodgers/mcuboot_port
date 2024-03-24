# set CMAKE_SYSTEM_NAME to define build as CMAKE_CROSSCOMPILING
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION Cortex-M4-STM32F446)
set(CMAKE_SYSTEM_PROCESSOR arm)

# setting either of the compilers builds the absolute paths for the other tools:
#   ar, nm, objcopy, objdump, ranlib, readelf -- but not as, ld, size
# if the compiler cannot be found the try_compile() function will fail the build
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

find_program(CROSS_GCC_PATH "arm-none-eabi-gcc")
get_filename_component(TOOLCHAIN ${CROSS_GCC_PATH} PATH)

set(CMAKE_C_COMPILER ${TOOLCHAIN}/arm-none-eabi-gcc)
set(CMAKE_Cxx_COMPILER ${TOOLCHAIN}/arm-none-eabi-g++)
set(TOOLCHAIN_as ${TOOLCHAIN}/arm-none-eabi-as CACHE STRING "arm-none-eabi-as")
set(TOOLCHAIN_LD ${TOOLCHAIN}/arm-none-eabi-ld CACHE STRING "arm-none-eabi-ld")
set(TOOLCHAIN_SIZE ${TOOLCHAIN}/arm-none-eabi-size CACHE STRING "arm-none-eabi-size")

# --specs=nano.specs is both a compiler and linker option
set(ARM_OPTIONS -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb --specs=nano.specs)

add_compile_options(
  ${ARM_OPTIONS}
  -ffunction-sections
  -fdata-sections
  -MMD
  -MP)

# Definitions copied from CubeMX project
add_compile_definitions(
  STM32F446xx
  USE_FULL_ASSERT
  USE_FULL_LL_DRIVER
  HSE_VALUE=25000000
  HSE_STARTUP_TIMEOUT=100
  LSE_STARTUP_TIMEOUT=5000
  LSE_VALUE=32768
  EXTERNAL_CLOCK_VALUE=12288000
  HSI_VALUE=16000000
  LSI_VALUE=32000
  VDD_VALUE=3300
  PREFETCH_ENABLE=1
  INSTRUCTION_CACHE_ENABLE=1
  DATA_CACHE_ENABLE=1
)

# use this to avoid running the linker during test compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# use these options to verify the linker can create an ELF file
# when not doing a static link

add_link_options(
  ${ARM_OPTIONS}
  --specs=nosys.specs
  LINKER:--gc-sections)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
