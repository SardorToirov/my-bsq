CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT = my_bsq

all:run success
run:
	$(CC) $(CFLAGS) main.c -o $(OUT) 

success:
	echo "my_bsq installed successfully"

fclean:
	rm -f $(OUT) *.o
	