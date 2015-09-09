cc = gcc
bin = factor
CFLAGS = -O2  -ansi -Wpedantic -Wall -Werror

.PHONY: all clean

all:	$(bin)

$(bin):	main.o factor.o
	$(cc) -o $(bin) main.o factor.o
main.o:
	$(cc) -c -o main.o $(CFLAGS) main.c
factor.o:
	$(cc) -c -o factor.o $(CFLAGS) factor.c
clean:
	rm -rf main.o factor.o $(bin) *~

