#include "./huffman.h"

int main(void) {
	int i;
	char *data = "data to be compressed by our huffman algorithm";
  char buf[1024];

	init(data);
	compress(data, buf);
	printf("Compressed: %s\n", buf);
	printf("Decompressed: ");
	decompress(buf, byte[1]);

	return 0;
}
