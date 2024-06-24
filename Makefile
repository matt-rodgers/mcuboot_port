JLINK_CMD = JLinkExe -device STM32F446ZE -if SWD -speed 4000 -autoconnect 1

# Make application
.PHONY: app
app:
	cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-STM32F446-gcc.cmake && \
	cmake --build build -- -j 8

# Remove all CMake build files
.PHONY: clean
clean:
	rm -rf build

.PHONY: flash
flash:
	$(JLINK_CMD) -commandfile flash.jlink

.PHONY: sign_app
sign_app:
	python third-party/mcuboot/scripts/imgtool.py sign \
		--header-size 0x200 \
		--align 4 \
		--slot-size 0x20000 \
		--version 1.0.0 \
		--pad-header \
		--key key.pem \
		--confirm \
		~/software/starter-stm32/build-app/application.bin \
		build/app_signed.bin

.PHONY: flash_app
flash_app:
	$(JLINK_CMD) -commandfile flash_app.jlink
