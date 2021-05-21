#define SUCCESS 1

#define FAIL -1

#define ALREADY_EXISTS 0

typedef enum {
	FREE,
	FULL,
	DELETED
} status_t;

typedef struct {
	char* str;
	status_t status;
} hash_elem_t;

typedef struct {
	int size;
	hash_elem_t* table;
} hash_table_t;

hash_table_t* HashInit(int hashTSize);

int HashAdd(hash_table_t* hash, char elem[]);

hash_elem_t* HashFind(hash_table_t* hash, char elem[]);

int HashDelete(hash_table_t* hash, char elem[]);

void Clear(hash_table_t* hash);