#all:
#	gcc -I/usr/include/ncurses -Iinclude src/main.c src/project.c src/menus.c -o program -lncurses -lmenu

CC = gcc
SRC_DIR = src
INCLUDE_DIR = include
NCURSES_INCLUDE_DIR = /usr/include/ncurses
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/program

CFLAGS = -I$(INCLUDE_DIR) -I$(NCURSES_INCLUDE_DIR)
LIBS = -lncurses -lmenu

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
