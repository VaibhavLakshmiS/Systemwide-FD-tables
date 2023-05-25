#this is a makefile 

#compiler flags 
CC = gcc
CFLAGS = -Wall -Werror 

all: showFDtables

showFDtables: A2_final.o A2_linkedlist.o
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS)-c $<

.PHONY: clean

clean:
	rm *.o