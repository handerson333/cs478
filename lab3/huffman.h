#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct node_t {
	struct node_t *left, *right;
	int frequency;
	char c;
} *node;

struct node_t pool[256] = {{0}};
node bytes[255];
node *byte = bytes - 1;
int n_nodes = 0;
int end = 1;
char *code[128] = {0};
char *buf[1024];

node new_node(int frequency, char c, node a, node b);
void insert(node n);
node delete();
void init_tree(node n, char *s, int len);
void init(const char *s);
void compress(const char *s, char *out);
void decompress(const char *s, node t);

node new_node(int frequency, char c, node a, node b) {
	node n = pool + n_nodes++;
	if (frequency) n->c = c, n->frequency = frequency;
	else {
		n->left = a, n->right = b;
		n->frequency = a->frequency + b->frequency;
	}
	return n;
}

void insert(node n) {
	int j, i = end++;
	while ((j = i / 2)) {
		if (byte[j]->frequency <= n->frequency) break;
		byte[i] = byte[j], i = j;
	}
	byte[i] = n;
}

node delete() {
	int i, l;
	node n = byte[i = 1];

	if (end < 2) {
    return 0;
  }
	end--;
	while ((l = i * 2) < end) {
		if (l + 1 < end && byte[l + 1]->frequency < byte[l]->frequency) {
      l++;
    }
		byte[i] = byte[l], i = l;
	}
	byte[i] = byte[end];
	return n;
}

void init_tree(node n, char *s, int len) {
	static char *out = buf;
	if (n->c) {
		s[len] = 0;
		strcpy(out, s);
		code[n->c] = out;
		out += len + 1;
		return;
	}

	s[len] = '0'; init_tree(n->left,  s, len + 1);
	s[len] = '1'; init_tree(n->right, s, len + 1);
}

void init(const char *s) {
	int i, frequency[128] = {0};
	char c[16];

	while (*s){
     frequency[(int)*s++]++;
  }

	for (i = 0; i < 128; i++)
		if (frequency[i]) insert(new_node(frequency[i], i, 0, 0));

	while (end > 2)
		insert(new_node(0, 0, delete(), delete()));

	init_tree(byte[1], c, 0);
}

void compress(const char *s, char *out) {
	while (*s) {
    printf("%c  %d\n", *s, *s);
		strcpy(out, code[*s]);
		out += strlen(code[*s]);
    *s++;
	}
}

void decompress(const char *s, node t) {
	node n = t;
	while (*s) {
		if (*s++ == '0'){
       n = n->left;
		} else n = n->right;

		if (n->c) {
       putchar(n->c), n = t;
    }
	}

	putchar('\n');
	if (t != n) {
   printf("invalid\n");
  }
}
