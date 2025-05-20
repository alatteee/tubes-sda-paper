# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Daftar file source
SRC = main.c src/parser.c ADTSLL/linkedlist.c ADTstack/stack.c
OBJ = $(SRC:.c=.o)

# Nama executable (Windows)
EXEC = app.exe

# Rule utama
all: $(EXEC)

# Compile dan link
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compile file .c ke .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Bersihkan file object dan exe
clean:
	del /Q $(OBJ) $(EXEC) 2>nul

# Jalankan program (Windows)
run: all
	app.exe



