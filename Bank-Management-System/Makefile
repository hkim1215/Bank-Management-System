CC = gcc
CFLAGS = -Wall -Werror -pthread  # Use pthread for multi-threading and warnings

all: bank_management

bank_management: main.o customer.o transaction.o loan.o admin.o file_manager.o security.o
	$(CC) $(CFLAGS) -o bank_management main.o customer.o transaction.o loan.o admin.o file_manager.o security.o

main.o: main.c customer.h transaction.h loan.h admin.h file_manager.h security.h
	$(CC) $(CFLAGS) -c main.c

customer.o: customer.c customer.h file_manager.h security.h
	$(CC) $(CFLAGS) -c customer.c

transaction.o: transaction.c transaction.h file_manager.h security.h
	$(CC) $(CFLAGS) -c transaction.c

loan.o: loan.c loan.h
	$(CC) $(CFLAGS) -c loan.c

admin.o: admin.c admin.h
	$(CC) $(CFLAGS) -c admin.c

file_manager.o: file_manager.c file_manager.h
	$(CC) $(CFLAGS) -c file_manager.c

security.o: security.c security.h
	$(CC) $(CFLAGS) -c security.c

clean:
	rm -f *.o bank_management

