# dragino lora testing
# Single lora testing app

CC=g++
#CC=gcc

#CFLAGS=-c -Wall
#CFLAGS=-ggdb -c -Wall
CFLAGS=-c -g -Wall

LIBS=-lwiringPi

all: dragino_lora_app

dragino_lora_app: main.o
	$(CC) main.o  $(LIBS) -o dragino_lora_app

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o dragino_lora_app	
