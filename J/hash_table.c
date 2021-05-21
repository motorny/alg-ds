#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include "hash_table.h"

ht_t* createHash(ht_t* table, int capacity) {
    table = (ht_t*) malloc(sizeof(ht_t));
    if (table) {
        table->size = 0;
        table->capacity = capacity;
        table->entries = (ht_entry_t*) calloc(capacity, sizeof(ht_entry_t));
        if (!table->entries) {
            free(table);
            return NULL;
        }
    }
    return table;
}

void freeHash(ht_t* table) {
    if (!table)
        return;
    for (int i = 0; i < table->capacity; i++)
        free((void*) table->entries[i].key);
    free(table->entries);
    free(table);
}

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

static uint_fast16_t hash(const char* s) {
    uint_fast16_t h = FIRSTH;
    uint8_t size = 0;
    for (const char* ptr = s; *ptr; ptr++, size++) {
        if (size > 20)
            return h;
        h = (h * A) ^ (*ptr * B);
    }
    return h;
}

ht_entry_t* findHash(const ht_t* table, const char* str) {
    if (!table)
        return NULL;

    uint_fast16_t index = hash(str) % table->capacity, _try = 0;

    while (table->entries[index].status != FREE) {
        if (table->entries[index].status == BUSY && strcmp(table->entries[index].key, str) == 0)
            return &table->entries[index];
        _try++;
        index = (index + _try * _try) % table->capacity;
    }
    return NULL;
}


ht_entry_t* __insertHash(ht_entry_t* entries, const char* str, const int capacity, int* size) {
    uint_fast16_t index = hash(str) % capacity, _try = 0;

    while (entries[index].status == BUSY) {
        if (strcmp(entries[index].key, str) == 0)
            return entries;
        _try++, index = (index + _try * _try) % capacity;
    }

    entries[index].key = strdup(str);
    entries[index].status = BUSY;
    if (size != NULL)
        (*size)++;

    return entries;
}

resize_status_t resizeHash(ht_t* table, double multiplier) {
    int new_capacity = table->capacity > 0 ? (int) (table->capacity * multiplier) : 4;
    ht_entry_t* new_entries = (ht_entry_t*) calloc(new_capacity, sizeof *(table->entries));
    if (!new_entries || new_capacity <= 0)
        return FAIL;

    ht_entry_t entry;
    for (int i = 0; i < table->capacity; i++) {
        entry = table->entries[i];
        if (entry.status == BUSY) {
            __insertHash(new_entries, entry.key, new_capacity, NULL);
            free(entry.key);
        }
    }
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return SUCCESS;
}

ht_t* insertHash(ht_t* table, const char* str) {
    if (!table)
        return NULL;
    if (table->capacity * OCCUPANCY <= (table->size + 1) && resizeHash(table, EXPAND) == FAIL)
        return table;
    __insertHash(table->entries, str, table->capacity, &table->size);
    return table;
}

ht_t* deleteHash(ht_t* table, const char* str) {
    if (!table)
        return NULL;

    if (table->capacity * (1 - OCCUPANCY) > table->size && resizeHash(table, SHRINK) == FAIL)
        return table;

    uint_fast16_t index = hash(str) % table->capacity, _try = 0;

    while (table->entries[index].status != FREE) {
        if (table->entries[index].status == BUSY && strcmp(table->entries[index].key, str) == 0) {
            free(table->entries[index].key);
            table->entries[index].key = NULL;
            table->entries[index].status = DELETED;
            table->size--;
            return table;
        }
        _try++;
        index = (index + _try * _try) % table->capacity;
    }
    return table;
}