CC=gcc
CFLAGS=-c -Wall
LDFLAGS= -lm

all: Md_Key_Logger

Md_Key_Logger: main.o get_event_keyboard.o change_task.o clock.o
	$(CC) main.o get_event_keyboard.o change_task.o clock.o -o Md-Key-Logger $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

get_event_keyboard.o: get_event_keyboard.c
	$(CC) $(CFLAGS) get_event_keyboard.c

change_task.o: change_task.c
	$(CC) $(CFLAGS) change_task.c

clock.o: clock.c
	$(CC) $(CFLAGS) clock.c

clean :
	rm -f *.o

