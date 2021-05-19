#include"Header.h"
#pragma warning (disable:4996)

void Words_on_the_screen(list* head) {
	if (head == NULL) {
		printf("List is empty\n");
		return;
	}
	while (head != NULL) {
		printf("%s %i \n", head->word, head->number);
		head = head->next;
	}
	return;
}

void Error_repeat_number(void) {
		printf("Repeat number!!!!!!!\n");
}

void Search_number(list* head) {
	int a;
	

	if (head == NULL) {
		printf("List is empty");
		return;
	}

	printf("\nInput number: ");
	if (scanf("%i", &a) != 0) {
		while (head != NULL) {
			if (head->number == a) {
				printf("Yes, I have. It is : %s", head->word);
				return;
			}
			head = head->next;
		}

		printf("No, I haven't this number");
	}


	return;
}