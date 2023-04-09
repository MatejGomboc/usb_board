MAKEFLAGS += --no-builtin-rules --no-builtin-variables

PROJECT_NAME := usb_test

TARGET ?= Debug

SOURCES := \
	isr_vectors.s \
	reset_handler.s \
	default_handler.s \
	main.cpp

INCLUDES :=

LDSCRIPT := STM32F072CBTX.ld

ifndef PROJECT_NAME
$(error PROJECT_NAME is not defined)
endif

ifndef TARGET
$(error TARGET is not defined)
endif

TARGETS := Debug Release

ifneq ($(filter $(TARGET),$(TARGETS)), $(TARGET))
$(error TARGET must be set to either Debug or Release)
endif

ifndef SOURCES
$(error SOURCES is not defined)
endif

ifndef LDSCRIPT
$(error LDSCRIPT is not defined)
endif

BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src

AS := arm-none-eabi-gcc
CXX := arm-none-eabi-g++
LD := arm-none-eabi-g++
OBJCOPY := arm-none-eabi-objcopy
SIZE := arm-none-eabi-size
OBJDUMP := arm-none-eabi-objdump

#-masm-syntax-unified

ASFLAGS := -mcpu=cortex-m0 -march=armv6-m -x assembler-with-cpp -mthumb \
	$(addprefix -I/$(SRC_DIR)/,$(INCLUDES)) -MMD -MP -c -fstack-usage -Wmissing-include-dirs

CXXFLAGS := -mcpu=cortex-m0 -march=armv6-m -std=gnu++20 $(addprefix -I/$(SRC_DIR)/,$(INCLUDES)) -ffunction-sections \
	-fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -Wextra -pedantic -Wmissing-include-dirs -Wswitch-enum \
	-Wconversion -fstack-usage -nostdlib -mfloat-abi=soft -mthumb -MMD -MP -c -Wshadow -Wno-unused-variable -ffreestanding \
	-fno-threadsafe-statics -Wno-unused-parameter -Wold-style-cast -Wuseless-cast -Wsuggest-override

LDFLAGS := -mcpu=cortex-m0 -march=armv6-m -T"$(LDSCRIPT)" -nostdlib -Wl,-Map="$(BIN_DIR)/$(PROJECT_NAME).map" \
	-Wl,--cref -Wl,--gc-sections -static -Wl,--print-memory-usage -ffreestanding

ifeq ($(TARGET),Debug)
	ASFLAGS += -DDEBUG
	CFLAGS += -Og -ggdb3 -DDEBUG
	CXXFLAGS += -Og -ggdb3 -DDEBUG
else ifeq ($(TARGET), Release)
	CFLAGS += -Os
	CXXFLAGS += -Os
endif

all: $(BIN_DIR)/$(PROJECT_NAME).bin $(BIN_DIR)/$(PROJECT_NAME).asm

$(BIN_DIR)/$(PROJECT_NAME).bin: $(BIN_DIR)/$(PROJECT_NAME).elf | $(BIN_DIR)
	$(OBJCOPY) --gap-fill 0 -O binary -S $< $@

$(BIN_DIR)/$(PROJECT_NAME).asm: $(BIN_DIR)/$(PROJECT_NAME).elf | $(BIN_DIR)
	$(OBJDUMP) -S -d -l -C -z $< > $@

$(BIN_DIR)/$(PROJECT_NAME).elf: $(SOURCES:%=$(OBJ_DIR)/%.o) | $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $@ $^
	$(SIZE) -A $@

$(OBJ_DIR)/%.s.o: $(SRC_DIR)/%.s | $(OBJ_DIR)
	$(AS) $(ASFLAGS) -MT $@ -MF $(OBJ_DIR)/$*.d -o $@ $<

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MT $@ -MF $(OBJ_DIR)/$*.d -o $@ $<

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rfd $(BIN_DIR)
	rm -rfd $(OBJ_DIR)

.PHONY: all clean

-include $(OBJ_DIR)/*.d
