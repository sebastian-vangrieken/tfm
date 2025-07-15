CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRCS = src/main.c src/utils.c

BUILD_DIR = build

OBJS = $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/tfm

all: $(TARGET)

# Linking
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compiling
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# .o files won't end up in src dir
.SUFFIXES:

clean: 
	rm -rf $(BUILD_DIR)

.PHONY: all clean
