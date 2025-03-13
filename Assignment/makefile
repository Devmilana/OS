CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic 
LINK = -pthread
OBJ = main.o printResults.o validators.o reader.o 
EXEC = mssv

$(EXEC): clean $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c buffer.h validators.h reader.h
	$(CC) -c main.c $(CFLAGS) $(LINK)

printResults.o: printResults.c printResults.h buffer.h
	$(CC) -c printResults.c $(CFLAGS) $(LINK)

validators.o: validators.c validators.h buffer.h
	$(CC) -c validators.c $(CFLAGS) $(LINK)

reader.o: reader.c reader.h buffer.h
	$(CC) -c reader.c $(CFLAGS) $(LINK)

clean:
	rm -f $(OBJ) $(EXEC)
