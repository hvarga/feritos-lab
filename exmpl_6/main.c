#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
};

struct Person *get_input(int);
int print_people(struct Person *, int);
void cleanup(struct Person *, int);

int main()
{
	struct Person *people = NULL;
	char do_again = 'n';
	int no_people;
	do {
		printf("Enter a number of people you wish to add:\n");
		scanf("%d", &no_people);

		if (no_people < 1) {
			printf("That wasn't a valid number.\n");
		} else {
			people = get_input(no_people);

			char print_out = 'y';
			printf("You want to see what you did? (y/n)\n");
			scanf(" %c", &print_out);
			if (print_out == 'y')
				print_people(people, no_people);
		}

		printf("You want to try again? (y/n)\n");
		scanf(" %c", &do_again);

		cleanup(people, no_people);
	} while (do_again == 'y');

	return 0;
}

struct Person *get_input(int no_people)
{
	struct Person *people = NULL;
	people = malloc(sizeof(struct Person) * no_people);

	int i;
	for (i = 0; i < no_people; i++) {
		char name[256];
		int age = 0;
		printf("Enter %d. person name:\n", i + 1);
		scanf("%s", name);
		printf("Enter %d. person age:\n", i + 1);
		scanf("%d", &age);

		people[i].name = malloc(strlen(name) + 1);
		people[i].name = name;
		people[i].age = age;
	}

	return people;
}

int print_people(struct Person *people, int no_people)
{
	if (people != NULL && no_people > 0) {
		int i;
		for (i = 0; i < no_people; i++) {
			printf("%d. person:\n", i + 1);
			printf("Name: %s; Age: %d\n", people[i].name, people[i].age);
		}
		return 0;
	} else
		return 1;
}

void cleanup(struct Person *people, int no_people)
{
	int i;
	for (i = 0; i < no_people; i++) {
		free(people[i].name);
	}
}
