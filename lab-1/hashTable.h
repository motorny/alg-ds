#pragma once

#define TABLE_SIZE 701

#define NUMBER_M_HASH_1 701
#define NUMBER_M_HASH_2 1024
#define NUMBER_C1_HASH2 0.5
#define NUMBER_C2_HASH2 0.5

typedef char* data_t;

typedef struct {
	data_t data;
	int status;
} hash_t;

hash_t* CreateTable(int size);
int Add(hash_t* t, const data_t key);
int Find(const hash_t* t, const data_t key);
int Del(hash_t* t, const data_t key);
void Destroy(hash_t* t);