CC = gcc
EXEC ?= libimged.a

SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build

CCFLAGS := -I$(INCLUDE_DIR) -pedantic -std='c99' -Wall -Wextra -O2

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRC))
OBJECTS := $(addsuffix .o, $(OBJECTS))
INCLUDE := $(wildcard $(INCLUDE_DIR)/*.h)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@ $(CCFLAGS)

$(EXEC): $(OBJECTS)
	ar -crs $(EXEC) $(OBJECTS)

install:
	mkdir -p /usr/include/imged
	cp $(INCLUDE) /usr/include/imged/
	cp $(EXEC) /usr/local/lib/

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXEC)
