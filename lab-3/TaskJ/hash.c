#include <stdlib.h>
#include <string.h>

#include "hash.h"

#ifdef __cpluslpus
extern "C" {
#endif /* __cpluslpus */

typedef struct hash_t {
  unsigned capacity;
  char **table;
  char deleted;
} hash_t;

hash_t * GetHash(unsigned capacity) {
  hash_t *hash = (hash_t *)malloc(sizeof(hash_t));
  if (hash == NULL)
    return NULL;
  hash->table = (char **)calloc(capacity, sizeof(char *));
  if (hash->table == NULL) {
    free(hash);
    return NULL;
  }
  hash->capacity = capacity;
  return hash;
}

#define CHECK_EMPTY(HASH, NUM) ((HASH)->table[(NUM)] == NULL)
#define CHECK_DELETED(HASH, NUM) ((HASH)->table[(NUM)] == &(HASH)->deleted)
#define CHECK_FREE(HASH, NUM) (CHECK_EMPTY(HASH, NUM) || CHECK_DELETED(HASH, NUM))

#define HASH_TERM_FOR_ITER(ITER) (2 * (ITER) + 1)
#define HASH_MAX(HASH) ((HASH)->capacity)

static unsigned _hashFunc(hash_t *h, char *key) {
  int sum = 0;
  while (*key != 0) {
    sum += *key;
    key++;
  }
  return sum % HASH_MAX(h);
}

int HashAdd(hash_t *h, char key[]) {
  int pos0, pos, i = 0, pos1 = -1;

  if (h == NULL)
    return HASH_ADD_NULL_HASH;
  pos0 = pos = _hashFunc(h, key);
  do {
    if (CHECK_EMPTY(h, pos)) {
      if (pos1 == -1)
        pos1 = pos;
      break;
    }
    else {
      if (CHECK_DELETED(h, pos)) {
        if (pos1 == -1)
          pos1 = pos;
      }
      else if (strcmp(h->table[pos], key) == 0)
        return HASH_ADD_ALREADY_EXIST;
    }
    pos = (pos + HASH_TERM_FOR_ITER(i)) % h->capacity;
    i++;
  } while (pos != pos0);
  if (pos1 != -1) {
    h->table[pos1] = (char *)malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(h->table[pos1], key);
    return HASH_ADD_SUCCESS;
  }
  return HASH_ADD_NO_FREE_CELLS;
}

int HashFind(hash_t *h, char key[]) {
  int pos0, pos, i = 0;

  if (h == NULL)
    return HASH_FIND_NULL_HASH;
  pos0 = pos = _hashFunc(h, key);
  do {
    if (CHECK_EMPTY(h, pos))
      return HASH_FIND_FAIL;
    else if (!CHECK_DELETED(h, pos) && strcmp(h->table[pos], key) == 0)
      return HASH_FIND_SUCCESS;
    pos = (pos + HASH_TERM_FOR_ITER(i)) % h->capacity;
    i++;
  } while (pos != pos0);
  return HASH_FIND_FAIL;
}

int HashRemove(hash_t *h, char key[]) {
  int pos0, pos, i = 0;

  if (h == NULL)
    return HASH_FIND_NULL_HASH;
  pos0 = pos = _hashFunc(h, key);
  do {
    if (CHECK_EMPTY(h, pos))
      return HASH_REMOVE_NO_ELEMENT;
    else if (!CHECK_DELETED(h, pos) && strcmp(h->table[pos], key) == 0) {
      int pos1 = (pos + HASH_TERM_FOR_ITER(i)) % h->capacity;
      free(h->table[pos]);
      h->table[pos] = &h->deleted;
      if (CHECK_EMPTY(h, pos1))
        while (h->table[pos] == &h->deleted) {
          h->table[pos] = NULL;
          i--;
          pos = (pos - HASH_TERM_FOR_ITER(i)) % h->capacity;
          if (pos == pos0)
            break;
        }
      return HASH_REMOVE_SUCCESS;
    }
    pos = (pos + HASH_TERM_FOR_ITER(i)) % h->capacity;
    i++;
  } while (pos != pos0);
  return HASH_REMOVE_NO_ELEMENT;
}

void DeleteHash(hash_t *h) {
  unsigned i;
  if (h == NULL)
    return;
  for (i = 0; i < h->capacity; i++)
    if (!CHECK_FREE(h, i))
      free(h->table[i]);
  free(h);
}

#ifdef __cpluslpus
}
#endif /* __cpluslpus */
