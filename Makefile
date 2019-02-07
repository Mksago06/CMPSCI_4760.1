CC = gcc
CFLAGS = -g
TARGET = fork
OBJS = main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	/bin/rm -f *.o $(TARGET)	
