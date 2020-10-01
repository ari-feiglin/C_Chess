PROJECT_NAME = Chess
CC = gcc
IDIR = ./include
OBJ_DIR = ./obj
SRC_DIR = ./src
CFLAGS = -I$(IDIR)

DEPS = $(wildcard $(IDIR)/*.h)
_OBJ = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(_OBJ))

all: $(PROJECT_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

$(PROJECT_NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(PROJECT_NAME)

.PHONY: clean
