CC = gcc

CFLAGS = -O3 -Wall -Wextra -march=native
DEBUG_CFLAGS = -g -O0 -Wall -Wextra

SRC = $(wildcard src/*.c)

OBJ = $(SRC:src/%.c=build/%.o)
DEBUG_OBJ = $(SRC:src/%.c=build/debug_%.o)

TARGET = bin/engine
DEBUG_TARGET = bin/engine_debug

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

$(DEBUG_TARGET): $(DEBUG_OBJ)
	mkdir -p bin
	$(CC) $(DEBUG_CFLAGS) -o $@ $^

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

build/debug_%.o: src/%.c
	mkdir -p build
	$(CC) $(DEBUG_CFLAGS) -Iinclude -c $< -o $@

debug: $(DEBUG_TARGET)

run: all
	./$(TARGET)

debug-run: debug
	./$(DEBUG_TARGET)

clean:
	rm -rf build bin