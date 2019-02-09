CC = gcc
CFLAGS = -g
TARGET = fork
OBJS = main.o stack.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
	
clean:
	/bin/rm -f *.o $(TARGET)	
