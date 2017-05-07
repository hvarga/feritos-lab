#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

int main() {
	char *alphabet;
	alphabet = malloc(sizeof(char) * ALPHABET_SIZE);

	int i;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		alphabet[i] = 97 + i;
	}
	printf("English alphabet has %d letters:\n%s\n",strlen(alphabet), alphabet);

	free(alphabet);
	return 0;
}
