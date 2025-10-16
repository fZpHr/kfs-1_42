# === CONFIGURATION ===

# Output binary name
TARGET := kernel.bin
BUILD_DIR := build

# Tools (host GCC + NASM)
CC := gcc
LD := ld
AS := nasm
OBJCOPY := objcopy

# Flags to make GCC act like a freestanding compiler
CFLAGS := -m32 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -nostartfiles
ASFLAGS := -f elf32

# Sources
C_SOURCES := kernel.c ascii.c 
ASM_SOURCES := boot.asm
OBJS := $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/ascii.o 

ISO_DIR := iso
ISO_BOOT := $(ISO_DIR)/boot
ISO := kfs.iso

# === RULES ===

all: $(TARGET)

# Link object files into ELF, then convert to flat binary
$(TARGET): $(OBJS)
	@echo "[LD] Linking kernel.elf"
	@mkdir -p $(BUILD_DIR)
	@$(LD) -m elf_i386 -T linker.ld -o $(BUILD_DIR)/kernel.elf $(OBJS)
	@echo "[OBJCOPY] Creating kernel.bin"
	@$(OBJCOPY) -O binary $(BUILD_DIR)/kernel.elf $@

# Compile C source to object
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	@echo "[GCC] Compiling $<"
	@$(CC) $(CFLAGS) -I includes -c $< -o $@

# Assemble ASM source to object
$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(BUILD_DIR)
	@echo "[NASM] Assembling $<"
	@$(AS) $(ASFLAGS) $< -o $@

iso: $(BUILD_DIR)/kernel.elf
	mkdir -p $(ISO_BOOT)/grub
	cp $(BUILD_DIR)/kernel.elf $(ISO_BOOT)/
	cp grub.cfg $(ISO_BOOT)/grub/
	grub-mkrescue -o $(ISO) $(ISO_DIR)

run: iso
	qemu-system-i386 -cdrom $(ISO)

# Clean build artifacts
clean:
	@echo "[CLEAN]"
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean iso run
