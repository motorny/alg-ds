int main(void) {
	Btree* root = tree_create();;
	int value;
	bool_t check = TRUE;
	char buff = getchar();

	while (buff != EOF) {
		scanf("%d", &value);
		if (buff == 'a') {
			check = elem_insert(&root, value);
		}
		else if (buff == 'r') {
			check = elem_delete(&root, value);
		}
		else if (buff == 'f') {
			if (elem_find(&root, value)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
		}
		else {
			printf("Incorrect input");
			return 0;
		}
		buff = getchar();
		if (buff == '\r' || buff == '\n')
			buff = getchar();
	}


	tree_delete(&root);
	return 0;
}