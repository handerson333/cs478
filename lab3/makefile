CC:=gcc
CFLAGS:= -w -g -pthread -lcrypto -lm

all:	huffman rabin mini_forensic_tool

huffman:
	$(CC) huffman.c $(CFLAGS) -o huffman
	
rabin:
	$(CC) rabin.c vandermonde.c $(CFLAGS) -o rabin

mini_forensic_tool:
	$(CC) mini_forensic_tool.c $(CFLAGS) -o mini_forensic_tool

clean:
	rm huffman rabin mini_forensic_tool
