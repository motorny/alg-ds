#include "gtest/gtest.h"
#include "../hash.h"

typedef struct hash_t {
  unsigned capacity;
  char **table;
  char deleted;
} hash_t;

static char *SetDoubleString(char *str, char num) {
  str[0] = num;
  str[1] = 0;
  return str;
}

static char * GetDoubleString(char num) {
  char *str = (char *)malloc(sizeof(char) * 2);
  str[0] = num;
  str[1] = 0;
  return str;
}

TEST(HashAdd_NullHash_returnMinus2) {
  char str[2];
  EXPECT_EQ(HashAdd(NULL, SetDoubleString(str, 0)), -2);
}

TEST(HashAdd_NoCollision_return1) {
  char str[2];
  hash_t *hash = GetHash(1);
  EXPECT_EQ(HashAdd(hash, SetDoubleString(str, 0)), 1);
  EXPECT_EQ(hash->capacity, 1);
  EXPECT_EQ(*hash->table[0], 0);
  free(hash->table[0]);
  free(hash);
}

TEST(HashAdd_Collision_return1) {
  char str[2];
  hash_t *hash = GetHash(2);
  hash->table[0] = GetDoubleString(0);
  EXPECT_EQ(HashAdd(hash, SetDoubleString(str, 0 + hash->capacity * 1)), 1);
  EXPECT_EQ(hash->capacity, 2);
  EXPECT_EQ(*hash->table[0], 0);
  EXPECT_EQ(*hash->table[1], 2);
  free(hash->table[0]);
  free(hash->table[1]);
  free(hash);
}

TEST(HashAdd_CollisionWithDeleted_return1) {
  char str[2];
  hash_t *hash = GetHash(5);
  hash->table[0] = GetDoubleString(0);
  hash->table[1] = &hash->deleted;
  hash->table[4] = GetDoubleString(hash->capacity * 2);
  EXPECT_EQ(HashAdd(hash, SetDoubleString(str, hash->capacity * 1)), 1);
  EXPECT_EQ(hash->capacity, 5);
  EXPECT_EQ(*hash->table[0], 0);
  EXPECT_EQ(*hash->table[1], hash->capacity * 1);
  EXPECT_EQ(hash->table[2], (char *)NULL);
  EXPECT_EQ(hash->table[3], (char *)NULL);
  EXPECT_EQ(*hash->table[4], hash->capacity * 2);
  free(hash->table[0]);
  free(hash->table[1]);
  free(hash->table[4]);
  free(hash);
}

TEST(HashAdd_AlreadyExist_returnMinus1) {
  char str[2];
  hash_t *hash = GetHash(1);
  hash->table[0] = GetDoubleString(0);
  EXPECT_EQ(HashAdd(hash, SetDoubleString(str, 0)), -1);
  EXPECT_EQ(hash->capacity, 1);
  EXPECT_EQ(*hash->table[0], 0);
  free(hash->table[0]);
  free(hash);
}

TEST(HashAdd_NoCells_return0) {
  char str[2];
  hash_t *hash = GetHash(1);
  hash->table[0] = GetDoubleString(0);
  EXPECT_EQ(HashAdd(hash, SetDoubleString(str, 1)), 0);
  EXPECT_EQ(hash->capacity, 1);
  EXPECT_EQ(*hash->table[0], 0);
  free(hash->table[0]);
  free(hash);
}

TEST(HashFind_NullHash_returnMinus1) {
  char str[2];
  EXPECT_EQ(HashFind(NULL, 0), -1);
}

TEST(HashFind_SuccessNoCollision_return1) {
  char str[2];
  hash_t *hash = GetHash(1);
  hash->table[0] = GetDoubleString(0);
  EXPECT_EQ(HashFind(hash, SetDoubleString(str, 0)), 1);
  EXPECT_EQ(hash->capacity, 1);
  EXPECT_EQ(*hash->table[0], 0);
  free(hash->table[0]);
  free(hash);
}

TEST(HashFind_SuccessCollision_return1) {
  char str[2];
  hash_t *hash = GetHash(2);
  hash->table[0] = GetDoubleString(0);
  hash->table[1] = GetDoubleString(hash->capacity * 1);
  EXPECT_EQ(HashFind(hash, SetDoubleString(str, hash->capacity * 1)), 1);
  EXPECT_EQ(hash->capacity, 2);
  EXPECT_EQ(*hash->table[0], 0);
  EXPECT_EQ(*hash->table[1], hash->capacity * 1);
  free(hash->table[0]);
  free(hash->table[1]);
  free(hash);
}

TEST(HashFind_SuccessCollisionWithDeleted_return1) {
  char str[2];
  hash_t *hash = GetHash(5);
  hash->table[0] = GetDoubleString(0);
  hash->table[1] = &hash->deleted;
  hash->table[4] = GetDoubleString(hash->capacity * 1);
  EXPECT_EQ(HashFind(hash, SetDoubleString(str, hash->capacity * 1)), 1);
  EXPECT_EQ(hash->capacity, 5);
  EXPECT_EQ(*hash->table[0], 0);
  EXPECT_EQ(hash->table[1], &hash->deleted);
  EXPECT_EQ(hash->table[2], (char *)NULL);
  EXPECT_EQ(hash->table[3], (char *)NULL);
  EXPECT_EQ(*hash->table[4], hash->capacity * 1);
  free(hash->table[0]);
  free(hash->table[4]);
  free(hash);
}

TEST(HashFind_Unsuccess_return0) {
  char str[2];
  hash_t *hash = GetHash(1);
  EXPECT_EQ(HashFind(hash, SetDoubleString(str, 0)), 0);
  EXPECT_EQ(hash->capacity, 1);
  EXPECT_EQ(hash->table[0], (char *)NULL);
  free(hash);
}

TEST(HashFind_UnsuccessWithDeleted_return0) {
  char str[2];
  hash_t *hash = GetHash(2);
  hash->table[0] = &hash->deleted;
  hash->table[1] = GetDoubleString(1);
  EXPECT_EQ(HashFind(hash, SetDoubleString(str, 0)), 0);
  EXPECT_EQ(hash->capacity, 2);
  EXPECT_EQ(hash->table[0], &hash->deleted);
  EXPECT_EQ(*hash->table[1], 1);
  free(hash->table[1]);
  free(hash);
}

TEST(HashRemove_NullHash_returnMinus1) {
  char str[2];
  EXPECT_EQ(HashRemove(NULL, SetDoubleString(str, 0)), -1);
}

TEST(HashRemove_NoKey_return0) {
  char str[2];
  hash_t *hash = GetHash(1);
  EXPECT_EQ(HashRemove(hash, SetDoubleString(str, 0)), 0);
  EXPECT_EQ(hash->capacity, 1);
  EXPECT_EQ(hash->table[0], (char *)NULL);
  free(hash);
}

TEST(HashRemove_NoKeyCollsion_return0) {
  char str[2];
  hash_t *hash = GetHash(2);
  hash->table[0] = &hash->deleted;
  hash->table[1] = GetDoubleString(hash->capacity * 1);
  EXPECT_EQ(HashRemove(hash, SetDoubleString(str, 0)), 0);
  EXPECT_EQ(hash->capacity, 2);
  EXPECT_EQ(*hash->table[1], hash->capacity * 1);
  free(hash->table[1]);
  free(hash);
}

TEST(HashRemove_CellToNull_return1) {
  char str[2];
  hash_t *hash = GetHash(2);
  hash->table[0] = GetDoubleString(0);
  EXPECT_EQ(HashRemove(hash, SetDoubleString(str, 0)), 1);
  EXPECT_EQ(hash->capacity, 2);
  EXPECT_EQ(hash->table[0], (char *)NULL);
  free(hash);
}

TEST(HashRemove_CellToDeleted_return1) {
  char str[2];
  hash_t *hash = GetHash(2);
  hash->table[0] = GetDoubleString(0);
  hash->table[1] = GetDoubleString(hash->capacity * 1);
  EXPECT_EQ(HashRemove(hash, SetDoubleString(str, 0)), 1);
  EXPECT_EQ(hash->capacity, 2);
  EXPECT_EQ(hash->table[0], &hash->deleted);
  EXPECT_EQ(*hash->table[1], hash->capacity * 1);
  free(hash->table[1]);
  free(hash);
}

TEST(DeleteHash_NullHash_correctMemoryFree) {
  DeleteHash(NULL);
}

TEST(DeleteHash_EmptyHash_correctMemoryFree) {
  hash_t *hash = GetHash(1);
  DeleteHash(hash);
}

TEST(DeleteHash_HashWithData_correctMemoryFree) {
  hash_t *hash = GetHash(1);
  hash->table[0] = GetDoubleString(0);
  DeleteHash(hash);
}

TEST(DeleteHash_HashWithDeleted_correctMemoryFree) {
  hash_t *hash = GetHash(1);
  hash->table[0] = &hash->deleted;
  DeleteHash(hash);
}
