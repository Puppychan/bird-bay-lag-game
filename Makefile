#--------------------------------------Makefile-------------------------------------
BUILD_DIR := ./object
SRC_DIR := ./src
DATA_DIR := ./data

CFILES := $(wildcard $(SRC_DIR)/*.c)
OFILES := $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/data.o

GCCFLAGS := -Wall -O2 -ffreestanding -nostdinc -nostdlib -I ./gcclib
LDFLAGS := -nostdlib

MAC_EXCEPTIONS = ! -name "printf.o" ! -name "mbox.o" ! -name "string.o"
WIN_EXCEPTIONS = if not "%%f"=="object\printf.o" if not "%%f"=="object\mbox.o" if not "%%f"=="object\string.o"

all: kernel8.img

# Ensure necessary directories exist:
$(BUILD_DIR):
	mkdir "$(BUILD_DIR)"

$(BUILD_DIR)/data.o: $(DATA_DIR)/data.c | $(BUILD_DIR)
	echo "Compiling data.c..."
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/start.o: $(SRC_DIR)/start.S | $(BUILD_DIR)
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: $(BUILD_DIR)/start.o $(OFILES)
	aarch64-none-elf-ld $(LDFLAGS) $(BUILD_DIR)/start.o $(OFILES) -T $(SRC_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf
	aarch64-none-elf-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

# Remove all files in the object directory except data.o
clean:
ifeq ($(OS),Windows_NT)
	del /Q *.img .\object\kernel8.elf
	for %%f in (object\*.o) do if not "%%f"=="object\data.o" $(WIN_EXCEPTIONS) del /Q "%%f"
else
	rm -f *.img $(BUILD_DIR)/kernel8.elf
	find $(BUILD_DIR) -type f ! -name 'data.o' $(MAC_EXCEPTIONS) -delete
endif

cleanall:
ifeq ($(OS),Windows_NT)
# if exist .\object (del /Q .\object\kernel8.elf .\object\*.o)
	if exist .\object (del /Q .\object\kernel8.elf)
	for %%f in (object\*.o) do $(WIN_EXCEPTIONS) del /Q "%%f"

else
# rm -f *.img $(BUILD_DIR)/kernel8.elf $(BUILD_DIR)/*.o
# -d checks if directory exists, `; \ ` is used to continue on next line
	rm -f *.img $(BUILD_DIR)/kernel8.elf
	if [ -d "$(BUILD_DIR)" ]; then \
		find $(BUILD_DIR) -type f $(MAC_EXCEPTIONS) -delete; \
	fi
endif

run:
ifeq ($(OS),Windows_NT)
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio
else
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial stdio
endif

test: clean all run
cleanall-run: cleanall all run
