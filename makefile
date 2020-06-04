CC = gcc
# OPENCV = `pkg-config opencv4 --cflags --libs`
# LIBS = $(OPENCV)

all: server client

server: main.o server.o server_ext.o
	$(CC) main.o server.o server_ext.o -o server -lpthread

main.o: main.c
	$(CC) -c main.c

server.o: server.c server.h
	$(CC) -c server.c

server_ext.o: server_ext.c server_ext.h
	$(CC) -c server_ext.c

client: client.c
	$(CC) -o client client.c -lpthread -lpulse-simple -lpulse

clean:
	rm *.o server client