#include <stdio.h>
#include <stdlib.h>

int count_prime_numbers(int last);
void get_prime_numbers(int last);

int *numbers = NULL;

int main()
{
	int prime_count = 0;
	int check_until = 100;

	prime_count = count_prime_numbers(check_until);
	printf("Number of prime numbers from 1 to %d: %d\n", check_until, prime_count);
	numbers = malloc(prime_count);
	int i = 0;
	for (i = 0; i < prime_count; i++)
		numbers[i] = 0;
	get_prime_numbers(check_until);

	for (i = 0; i < prime_count; i++) {
		printf("%d) %d\n", i + 1, numbers[i]);
	}

	return 0;
}

int count_prime_numbers(int last)
{
	int count = 0;
	int i = 1;

	for (i = 1; i < last; i++) {
		int j = 1;
		int no_divisions = 0;
		for (j = 1; j <= i; j++) {
			if (no_divisions > 2) {
				break;
			}
			if (i % j == 0)
				no_divisions++;
		}
		if (no_divisions == 2) {
			count++;
		}
	}

	return count;
}

void get_prime_numbers(int last) {
	int count = 0;
	int i = 1;

	for (i = 1; i < last; i++) {
		int j = 1;
		int no_divisions = 0;
		for (j = 1; j <= i; j++) {
			if (no_divisions > 2)
				break;
			if (i % j == 0)
				no_divisions++;
		}
		if (no_divisions == 2) {
			numbers[count] = i;
			count++;
		}
	}
}
