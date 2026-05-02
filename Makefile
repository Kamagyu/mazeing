NAME = main
CC = gcc

SRC_DIR = src
BUILD_DIR = build

SRC = $(SRC_DIR)/main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS = -Wall -Wextra -O2
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

TARGET = $(BUILD_DIR)/$(NAME)

SIZE ?= 800

all: $(TARGET)

run: $(TARGET)
	./$(TARGET) $(SIZE)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean