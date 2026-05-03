NAME = main
CC = gcc

SRC_DIR = src
BUILD_DIR = build

WSIZE ?= 800
MSIZE ?= 51

SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ:= $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS = -Wall -Wextra -O2 -Iinclude -Dmaze_size=$(MSIZE)
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

TARGET = $(BUILD_DIR)/$(NAME)

all: clean $(TARGET)
	./$(TARGET) $(WSIZE)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET) $(WSIZE)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@



.PHONY: all run clean
