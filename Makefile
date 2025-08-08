CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11 -O0 -Iinclude
LDFLAGS = -nostdlib -T linker_script.ld

OBJ_COPY = arm-none-eabi-objcopy

OBJECT = main.o system.o gpio.o
BUILD_DIR = build
BUILD_OBJECT_DIR = $(BUILD_DIR)/object
BUILD_OBJECT = $(addprefix $(BUILD_OBJECT_DIR)/, $(OBJECT))

TARGET_NAME = main
TARGET = $(BUILD_DIR)/$(TARGET_NAME)
VPATH=src

all: $(OBJECT)
	$(CC) $(LDFLAGS) -o $(TARGET) $(BUILD_OBJECT)
	$(OBJ_COPY) -O binary $(TARGET) $(TARGET).bin

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(BUILD_OBJECT_DIR)/$@

clean:
	rm $(BUILD_OBJECT) $(TARGET)

flash:
	/mnt/data/My_Document/Coding/flasher/build/flasher
