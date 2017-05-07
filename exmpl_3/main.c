#include <stdio.h>
#include <stdlib.h>

int prime_numbers(int last);

int *numbers = NULL;

int main() {
	int prime_count = 0;
	int check_until = 100;
	numbers = malloc(sizeof(int));

	prime_count = prime_numbers(check_until);
	printf("Number of prime numbers from 1 to %d: %d\n", check_until, prime_count);

	int i;
	for (i = 0; i < prime_count; i++) {
		printf("%d) %d\n", i + 1, numbers[i]);
	}

	free(numbers);
	return 0;
}

int prime_numbers(int last) {
	int count = 0;
	int i = 1;

	for (i = 1; i<last; i++) {
		int j = 1;
		int no_divisions = 0;
		for (j = 1; j <= i; j++) {
			if (i % j == 0)
				no_divisions++;
		}
		if (no_divisions == 2) {
			if (count > 0)
				numbers = realloc(numbers, sizeof(int) * count);
			numbers[count] = i;
			count++;
		}
	}

	return count;
}

