#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LENGTH 9

struct Stuff {
	int *int_numbers;
	double *double_numbers;
	char *char_letters;
};
void print_stuff(struct Stuff *stuff);
void init_stuff(struct Stuff *stuff);
void free_stuff(struct Stuff *stuff);

int main () {
	int whole_numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	double decimal_numbers[] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
	char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

	struct Stuff *stuff = malloc(sizeof(struct Stuff));
	init_stuff(stuff);

	stuff->int_numbers = malloc(sizeof(int) * ARRAY_LENGTH);
	memcpy(stuff->int_numbers, whole_numbers, ARRAY_LENGTH);
	stuff->double_numbers = malloc(sizeof(double) * ARRAY_LENGTH);
	memcpy(stuff->double_numbers, decimal_numbers, ARRAY_LENGTH);
	stuff->char_letters = malloc(sizeof(char) * ARRAY_LENGTH);
	memcpy(stuff->char_letters, letters, ARRAY_LENGTH);

	print_stuff(stuff);
	free_stuff(stuff);

	return 0;
}


void print_stuff(struct Stuff *stuff)
{
	printf("Whole numbers:\n");
	int i;
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf("%d, ", stuff->int_numbers[i]);

	printf("\nDecimal numbers:\n");
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf("%f, ", stuff->double_numbers[i]);

	printf("\nLetters:\n");
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf("%c, ", stuff->char_letters[i]);

	printf("\n");
}

void init_stuff(struct Stuff *stuff) {
	stuff->int_numbers = NULL;
	stuff->double_numbers = NULL;
	stuff->char_letters = NULL;
}

void free_stuff(struct Stuff *stuff) {
	free(stuff->int_numbers);
	free(stuff->double_numbers);
	free(stuff->char_letters);
	free(stuff);
}
