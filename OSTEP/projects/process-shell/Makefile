CC = gcc
CFLAGS = -Wall -Wextra #-Werror

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# List all the C source files in the directory
C_SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generate corresponding object file names
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRCS))

# The final executable name
EXECUTABLE = $(BIN_DIR)/wish

all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
