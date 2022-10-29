CFLAGS = -O
CC = g++

list: driver.o itemType.o listType.o md5.o
	$(CC) $(CFLAGS) -o list driver.o itemType.o listType.o md5.o

driver.o: driver.cpp
	$(CC) $(CFLAGS) -c driver.cpp

itemType.o: itemType.cpp
	$(CC) $(CFLAGS) -c itemType.cpp

listType.o: listType.cpp
	$(CC) $(CFLAGS) -c listType.cpp
    
md5.o: md5.cpp
	$(CC) $(CFLAGS) -c md5.cpp

clean:
	rm -f core *.o