#pragma once
typedef struct hash_t hash_t;
hash_t* GetHash(unsigned capacity);
#define HASH_ADD_SUCCESS 1
#define HASH_ADD_NO_FREE_CELLS 0
#define HASH_ADD_ALREADY_EXIST -1
#define HASH_ADD_NULL_HASH -2
int Add(hash_t* h, char key[]);
#define HASH_FIND_SUCCESS 1
#define HASH_FIND_FAIL 0
#define HASH_FIND_NULL_HASH -1
int Find(hash_t* h, char key[]);
#define HASH_REMOVE_SUCCESS 1
#define HASH_REMOVE_NO_ELEMENT 0
#define HASH_REMOVE_NULL_HASH -1
int Remove(hash_t* h, char key[]);
void Delete(hash_t* h);


