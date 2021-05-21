#include <malloc.h>
#include <string.h>
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

uint hash(const char* key) {
    unsigned int sum = 0;

    for (const char* ptr = key; *ptr; ptr++)
        sum += (*ptr - 'a');
    return sum;
}

ht_entry_t* findHash(const ht_t* table, const char* str) {
    if (!table)
        return NULL;

    uint index = hash(str) % table->capacity, _try = 0;

    while (table->entries[index].status != FREE) {
        if (table->entries[index].status == BUSY && strcmp(table->entries[index].key, str) == 0)
            return &table->entries[index];
        _try++;
        index = (index + _try * _try) % table->capacity;
    }
    return NULL;
}


ht_entry_t* __insertHash(ht_entry_t* entries, const char* str, const int capacity, int* size) {
    uint index = hash(str) % capacity, _try = 0;

    while (entries[index].status == BUSY && strcmp(entries[index].key, str) != 0)
        _try++, index = (index + _try * _try) % capacity;

    if (entries[index].status != BUSY) {
        entries[index].key = strdup(str);
        entries[index].status = BUSY;
        if (size != NULL)
            (*size)++;
    }
    return entries;
}

expand_status_t expandHash(ht_t* table) {
    int new_capacity = table->capacity * 2;
    ht_entry_t* new_entries = (ht_entry_t*) calloc(new_capacity, sizeof(ht_entry_t));
    if (!new_entries)
        return FAIL;
    ht_entry_t en_try;
    for (int i = 0; i < table->capacity; i++) {
        en_try = table->entries[i];
        if (en_try.status == BUSY) {
            __insertHash(new_entries, en_try.key, table->capacity, NULL);
            free(en_try.key);
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
    if (table->capacity * OCCUPANCY <= (table->size + 1) && expandHash(table) == FAIL)
        return table;
    __insertHash(table->entries, str, table->capacity, &table->size);
    return table;
}

ht_t* deleteHash(ht_t* table, const char* str) {
    if (!table)
        return NULL;

    uint index = hash(str) % table->capacity, _try = 0;

    while (table->entries[index].status != FREE) {
        if (table->entries[index].status == BUSY && strcmp(table->entries[index].key, str) == 0) {
            free(table->entries[index].key);
            table->entries[index].key = NULL;
            table->entries[index].status = DELETED;
            table->size--;
            return table;
        }
        _try++, index = (index + _try * _try) % table->capacity;
    }
    return table;
}