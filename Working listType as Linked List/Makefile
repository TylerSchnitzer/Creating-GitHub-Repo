CFLAGS = -O
CC = g++

list: driver.o itemType.o pQueueType.o
	$(CC) $(CFLAGS) -o list driver.o itemType.o pQueueType.o

driver.o: driver.cpp
	$(CC) $(CFLAGS) -c driver.cpp

itemType.o: itemType.cpp
	$(CC) $(CFLAGS) -c itemType.cpp

pQueueType.o: pQueueType.cpp
	$(CC) $(CFLAGS) -c pQueueType.cpp

clean:
	rm -f core *.o
