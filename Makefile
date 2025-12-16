TARGET = main
OBJ = commands.c env.c executor.c global.c history.c rawmode.c shell.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all:
	$(CC) -o $(TARGET) $(OBJ)
clean:
	rm -f *-o
fclean: clean
	rm -f $(TARGET)
re: fclean all