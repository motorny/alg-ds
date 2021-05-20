#ifndef __ht_t__
#define __ht_t__

typedef struct htCell_t htCell_t;
struct htCell_t 
{
	char str[100];
	char status;            
};

enum returns 
{
	LABJ_TRUE = 1,
	LABJ_FALSE = 0
};

int FuncForInit(htCell_t** ht, int htSize);
int FuncForInsert(htCell_t* ht, int htSize, char* str);
int FuncForFind(htCell_t* ht, int htSize, char* str);
int FuncForDelete(htCell_t* ht, int htSize, char* str);
int FuncForClear(htCell_t** ht, int htSize);

#endif // __ht_t__