#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 9

struct Stuff {
	int *int_numbers;
	double *double_numbers;
	char *char_letters;
};
void print_stuff(struct Stuff stuff);

int main () {
	int whole_numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	double decimal_numbers[] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
	char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

	struct Stuff stuff;
	stuff.int_numbers = whole_numbers;
	stuff.double_numbers = decimal_numbers;
	stuff.char_letters = letters;

	print_stuff(stuff);

	return 0;
}

void print_stuff(struct Stuff stuff)
{
	printf("Whole numbers:\n");
	int i;
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf("%d, ", stuff.int_numbers[i]);

	printf("\nDecimal numbers:\n");
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf("%f, ", stuff.double_numbers[i]);

	printf("\nLetters:\n");
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf("%c, ", stuff.char_letters[i]);

	printf("\n");
}
