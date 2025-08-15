CC = arm-none-eabi-gcc
OBJ_COPY = arm-none-eabi-objcopy
OBJ_DUMP = arm-none-eabi-objdump

OBJECT = main.o system.o gpio.o timer.o  os.o asm_os.o
BUILD_DIR = build
BUILD_OBJECT_DIR = $(BUILD_DIR)/object
BUILD_OBJECT = $(addprefix $(BUILD_OBJECT_DIR)/, $(OBJECT))

TARGET_NAME = main
TARGET = $(BUILD_DIR)/$(TARGET_NAME)
VPATH=src

SECTION_HEADER = $(BUILD_DIR)/header
DEASSEMBLE = $(BUILD_DIR)/deassemble
MEM_MAP = $(BUILD_DIR)/map
BINARY_FILE = $(BUILD_DIR)/main.bin

CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11 -O0 -Iinclude
LDFLAGS = -nostdlib -T linker_script.ld -Wl,-Map=$(MEM_MAP)

all: $(OBJECT)
	$(CC) $(LDFLAGS) -o $(TARGET) $(BUILD_OBJECT)
	$(OBJ_COPY) -O binary $(TARGET) $(BINARY_FILE)
	rm -f $(DEASSEMBLE) $(SECTION_HEADER)
	$(OBJ_DUMP) -D $(TARGET) >> $(DEASSEMBLE)
	$(OBJ_DUMP) -x $(TARGET) >> $(SECTION_HEADER)

asm_os.o: asm_os.s
	$(CC) $(CFLAGS) $< -o $(BUILD_OBJECT_DIR)/$@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(BUILD_OBJECT_DIR)/$@

clean:
	rm -rf $(BUILD_OBJECT) $(TARGET) $(BINARY_FILE) $(DEASSEMBLE) $(SECTION_HEADER) $(MEM_MAP)

flash:
	/mnt/data/My_Document/Coding/flasher/build/flasher
