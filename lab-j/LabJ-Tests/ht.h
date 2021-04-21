#ifndef __ht_t__
#define __ht_t__

typedef struct htCell_t htCell_t;
struct htCell_t {
  char* str;
  char isFree;
};

enum returnedType_t {
  ht_false = -1,
  ht_true = 1
};

int HtInit(htCell_t** ht, int htSize);

int HtInsert(htCell_t* ht, int htSize, char* str);
int HtFind(htCell_t* ht, int htSize, char* str);
int HtDelete(htCell_t* ht, int htSize, char* str);

int HtClear(htCell_t** ht, int htSize);

#endif // __ht_t__