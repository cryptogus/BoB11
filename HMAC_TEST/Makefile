#Makefile

CFLAGS=-lcrypto

all: hmac

hmac: hmac.o
	gcc -o hmac-test HMAC.c $(CFLAGS)

hmac.o: HMAC.c

clean:
	rm -f hmac-test
	rm -f *.o