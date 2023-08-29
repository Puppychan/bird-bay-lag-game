#--------------------------------------Makefile-------------------------------------
BUILD_DIR = ./object
SRC_DIR = ./src

CFILES = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Add -I ./gcclib to GCCFLAGS: to include all necessary header files
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -I ./gcclib
LDFLAGS = -nostdlib -nostartfiles

all: clean kernel8.img

$(BUILD_DIR)/start.o: $(SRC_DIR)/start.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: $(BUILD_DIR)/start.o $(OFILES)
	aarch64-none-elf-ld $(LDFLAGS) $(BUILD_DIR)/start.o $(OFILES) -T $(SRC_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf
	aarch64-none-elf-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

clean:
# Window: remove comment this line
# del *.img .\object\kernel8.elf .\object\*.o
	rm -f *.img ./object/kernel8.elf ./object/*.o

run:
# Window: remove comment this line
# qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial stdio

test: all run