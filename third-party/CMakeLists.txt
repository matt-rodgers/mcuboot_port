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
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_gpio.c
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_uart.c
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash.c
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash_ex.c
    stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash_ramfunc.c
    stm32f4xx_hal_driver/Src/stm32f4xx_ll_gpio.c
    stm32f4xx_hal_driver/Src/stm32f4xx_ll_utils.c
)

# MCUboot
set(MCUBOOT_DIR mcuboot/boot/bootutil)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${MCUBOOT_DIR}/include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${MCUBOOT_DIR}/src/boot_record.c
    ${MCUBOOT_DIR}/src/bootutil_misc.c
    ${MCUBOOT_DIR}/src/bootutil_misc.h
    ${MCUBOOT_DIR}/src/bootutil_priv.h
    ${MCUBOOT_DIR}/src/bootutil_public.c
    ${MCUBOOT_DIR}/src/caps.c
    ${MCUBOOT_DIR}/src/encrypted.c
    ${MCUBOOT_DIR}/src/fault_injection_hardening.c
    ${MCUBOOT_DIR}/src/fault_injection_hardening_delay_rng_mbedtls.c
    ${MCUBOOT_DIR}/src/image_ecdsa.c
    ${MCUBOOT_DIR}/src/image_ed25519.c
    ${MCUBOOT_DIR}/src/image_rsa.c
    ${MCUBOOT_DIR}/src/image_validate.c
    ${MCUBOOT_DIR}/src/loader.c
    ${MCUBOOT_DIR}/src/swap_misc.c
    ${MCUBOOT_DIR}/src/swap_move.c
    ${MCUBOOT_DIR}/src/swap_priv.h
    ${MCUBOOT_DIR}/src/swap_scratch.c
    ${MCUBOOT_DIR}/src/tlv.c
)

# Tinycrypt
set(TINYCRYPT_DIR mcuboot/ext/tinycrypt/lib)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${TINYCRYPT_DIR}/include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${TINYCRYPT_DIR}/source/aes_decrypt.c
    ${TINYCRYPT_DIR}/source/aes_encrypt.c
    ${TINYCRYPT_DIR}/source/cbc_mode.c
    ${TINYCRYPT_DIR}/source/ccm_mode.c
    ${TINYCRYPT_DIR}/source/cmac_mode.c
    ${TINYCRYPT_DIR}/source/ctr_mode.c
    ${TINYCRYPT_DIR}/source/ctr_prng.c
    ${TINYCRYPT_DIR}/source/ecc.c
    ${TINYCRYPT_DIR}/source/ecc_dh.c
    ${TINYCRYPT_DIR}/source/ecc_dsa.c
    ${TINYCRYPT_DIR}/source/ecc_platform_specific.c
    ${TINYCRYPT_DIR}/source/hmac.c
    ${TINYCRYPT_DIR}/source/hmac_prng.c
    ${TINYCRYPT_DIR}/source/sha256.c
    ${TINYCRYPT_DIR}/source/utils.c
)

# mbedtls ASN1 parser is also needed if using tinycrypt
set(MBEDTLS_ASN1_DIR mcuboot/ext/mbedtls-asn1)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${MBEDTLS_ASN1_DIR}/include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${MBEDTLS_ASN1_DIR}/src/asn1parse.c
    ${MBEDTLS_ASN1_DIR}/src/platform_util.c
)