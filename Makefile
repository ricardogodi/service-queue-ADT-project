# Compiler and compiler flags
CC = gcc
CFLAGS = -g -Wall

# Build targets
all: service_queue

# Link the program
service_queue: driver.o sq.o llist.o
	$(CC) $(CFLAGS) -o service_queue driver.o sq.o llist.o

# Compile the driver source file
driver.o: driver.c sq.h list.h
	$(CC) $(CFLAGS) -c driver.c

# Compile the service queue source file
sq.o: sq.c sq.h list.h
	$(CC) $(CFLAGS) -c sq.c

# Compile the linked list source file
llist.o: llist.c list.h
	$(CC) $(CFLAGS) -c llist.c

# Clean build files
clean:
	rm -f *.o service_queue

# Run the program
run: service_queue
	./service_queue