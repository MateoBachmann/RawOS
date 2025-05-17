# ISO-Dateiname
ISO_NAME = myos.iso

# Compiler & Linker
CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld

# Compiler- & Linker-Flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -Ttext 0x1000

# Verzeichnisse
SRC_DIR = src
BUILD_DIR = build
ISO_DIR = iso

# Quelldateien & Ziele
KERNEL_SRC = $(SRC_DIR)/kernel.c
BOOT_SRC = $(SRC_DIR)/boot.asm
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_BIN = $(BUILD_DIR)/kernel.bin

# Haupt-Target
all: $(ISO_NAME)

# Kernel (C) kompilieren
$(KERNEL_OBJ): $(KERNEL_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Bootloader (ASM) kompilieren
$(BOOT_OBJ): $(BOOT_SRC)
	mkdir -p $(BUILD_DIR)
	nasm -f elf32 $< -o $@

# Linken zu ausführbarem Kernel-Binary
$(KERNEL_BIN): $(KERNEL_OBJ) $(BOOT_OBJ)
	$(LD) $(LDFLAGS) -o $@ -e _start $^

# ISO-Struktur vorbereiten
prepare_iso: $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/kernel.bin
	cp boot/grub.cfg $(ISO_DIR)/boot/grub/grub.cfg

# ISO erstellen mit GRUB
$(ISO_NAME): prepare_iso
	grub-mkrescue -o $@ $(ISO_DIR)

# Aufräumen
clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR) $(ISO_NAME)
