#ifndef __ht_t__
#define __ht_t__

typedef struct htCell_t htCell_t;
struct htCell_t {
  char str[100];
  char status;            // 0 not inited, 2 - free, 1 - not free
};

enum returns {
  LABJ_TRUE = 1,
  LABJ_FALSE = 0
};

int HtInit(htCell_t** ht, int htSize);

int HtInsert(htCell_t* ht, int htSize, char* str);
int HtFind(htCell_t* ht, int htSize, char* str);
int HtDelete(htCell_t* ht, int htSize, char* str);

int HtClear(htCell_t** ht, int htSize);

#endif // __ht_t__