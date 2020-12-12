#include "Header.h"

void Clear_list(list** List) {
	list* block = NULL;
	char* word = NULL;
	if (*List == NULL) {
		return ;
	}
	while ((*List) != NULL) {
		block = *List;
		word = block->word;
		*List = (*List)->next;
		free(word);
		free(block);
	}

	
	return;
}