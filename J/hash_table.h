#pragma once

#define OCCUPANCY 0.75
#define INIT_SIZE 4

typedef enum status {
    FREE,
    DELETED,
    BUSY
} status_t;

typedef enum expand_status {
    SUCCESS,
    FAIL
} expand_status_t;

typedef struct ht_entry {
    char* key;
    status_t status;
} ht_entry_t;

typedef struct ht {
    int size;
    int capacity;
    ht_entry_t* entries;
} ht_t;

typedef unsigned int uint;

ht_t* createHash(ht_t* table, int capacity);

void freeHash(ht_t* table);

ht_entry_t* findHash(const ht_t* table, const char* str);

ht_t* insertHash(ht_t* table, const char* str);

ht_t* deleteHash(ht_t* table, const char* str);