CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = a.out

# Auto-detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

# Compile & Run all .c files in a directory
run:
	$(CC) $(CFLAGS) $(wildcard $(dir)/*.c) -o $(TARGET) $(LDFLAGS) && ./$(TARGET)

# Compile and run single c file
single:
	$(CC) $(CFLAGS) $(file) -o $(TARGET) $(LDFLAGS) && ./$(TARGET)

# Clean
clean:
	rm -f $(TARGET)

.PHONY: run clean
