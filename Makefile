JLINK_CMD = JLinkExe -device STM32F446ZE -if SWD -speed 4000 -autoconnect 1

# Make application
.PHONY: app
app:
	cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-STM32F446-gcc.cmake && \
	cmake --build build --target application -- -j 8

# Remove all CMake build files
.PHONY: clean
clean:
	rm -rf build

.PHONY: flash
flash:
	$(JLINK_CMD) -commandfile flash.jlink
