#pragma once

#ifndef __HASH_H_INCLUDED
#define __HASH_H_INCLUDED

#ifdef __cpluslpus
extern "C" {
#endif /* __cpluslpus */

typedef struct hash_t hash_t;

hash_t *GetHash(unsigned capacity);

#define HASH_ADD_SUCCESS 1
#define HASH_ADD_NO_FREE_CELLS 0
#define HASH_ADD_ALREADY_EXIST -1
#define HASH_ADD_NULL_HASH -2

int HashAdd(hash_t *h, char key[]);

#define HASH_FIND_SUCCESS 1
#define HASH_FIND_FAIL 0
#define HASH_FIND_NULL_HASH -1

int HashFind(hash_t *h, char key[]);

#define HASH_REMOVE_SUCCESS 1
#define HASH_REMOVE_NO_ELEMENT 0
#define HASH_REMOVE_NULL_HASH -1

int HashRemove(hash_t *h, char key[]);

void DeleteHash(hash_t *h);

#ifdef __cpluslpus
}
#endif /* __cpluslpus */

#endif /* __HASH_H_INCLUDED */
