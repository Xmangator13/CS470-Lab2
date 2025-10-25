#compiler to use
CC = gcc

#compiler flags: enable all warnings and use C99 standard
CFLAGS = -Wall -Wextra -std=c99

#name of the final executable
TARGET = lab2

#source file to compile
SRC = lab2.c

#build executable
all: $(TARGET)

#compile source into target using specified compiler and flags
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

#remove the compiled executable
clean:
	rm -f $(TARGET)
