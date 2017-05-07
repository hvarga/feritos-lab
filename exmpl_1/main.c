#include <stdio.h>
#include <string.h>

int prime_numbers(int last);

int main() {
	int prime_count = 0;
	int check_until = 100;

	prime_count = prime_numbers(check_until);
	printf("Number of prime numbers from 1 to %d: %d", check_until, prime_count);

	return 0;
}

int prime_numbers(int last) {
	int count = 0;
	int i = 1;

	for (i = 1; i<last; i++) {
		int j = 1;
		int no_divisions = 0;
		for (j = 0; j <= i; j++) {
			if (i % j == 0)
				no_divisions++;
		}
		if (no_divisions == 2)
			count++;
	}

	return count;
}
