CC:=gcc
CFLAGS:= -w -g -fpack-struct=16 -pthread -lcrypto -lm

all:	merkle hors pqsig

merkle:
	$(CC) MerkleHash.c $(CFLAGS) -o merkle
	
hors:
	$(CC) HORS.c $(CFLAGS) -o hors

pqsig:
	$(CC) PQSig.c $(CFLAGS) -o pqsig

clean:
	rm hors merkle pqsig
