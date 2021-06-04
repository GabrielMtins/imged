
# Copyright (C) 2021  Gabriel Martins

# This file is part of imged

# imged is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# imged is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
    
# You should have received a copy of the GNU Lesser General Public License
# along with imged.  If not, see <https://www.gnu.org/licenses/>

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
