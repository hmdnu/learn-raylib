CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = a.out

# Auto-detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

# Compile & Run a specific file
run:
	$(CC) $(CFLAGS) $(file) -o $(TARGET) $(LDFLAGS) && ./$(TARGET)

# Clean
clean:
	rm -f $(TARGET)

.PHONY: run clean
