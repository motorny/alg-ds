#include "../memallocator.h"
#include "funcs_for_test.h"
#include "gtest/gtest.h"

// macro to evaluate shift
#define SHIFT(NUM_OF_INT, NUM_OF_PTR, EXTRA) \
  (sizeof(int) * (NUM_OF_INT) + sizeof(void*) * (NUM_OF_PTR) + (EXTRA))

// macro to evaluate minimum structure size
#define MIN_SIZE ((2 * sizeof(int) + sizeof(void*)) * 2)
// macro to evaluate structure size for 1 byte allocation
#define SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE ((2 * sizeof(int) + sizeof(void*)) * 2 + 1)
// macro to evaluate structure size for 2 allocations with 1 byte
#define SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES ((2 * sizeof(int) + sizeof(void*)) * 3 + 2)

TEST(memalloc_AllocationWithoutIni_returnNULL) {
  ASSERT_EQ(memalloc(1), (void*)NULL);
}

TEST(meminit_InitWithNULLNot0Size_return0) {
  ASSERT_EQ(meminit(NULL, 1), 0);
}

TEST(meminit_InitWithNULL0Size_return0) {
  ASSERT_EQ(meminit(NULL, 0), 0);
}

TEST(meminit_InitWithIncorrectSize_return0) {
  char buf[MIN_SIZE - 1];
  ASSERT_EQ(meminit(buf, MIN_SIZE - 1), 0);
}

TEST(meminit_CorrectInit_return1) {
  char buf[MIN_SIZE];
  ASSERT_EQ(meminit(buf, MIN_SIZE), 1);
}

TEST(memalloc_AllocateIncorrectSize_returnNULL) {
  char memBlock[SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE];
  InitNoCheck(memBlock, SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE);
  char *allocated = (char*)memalloc(0);

  ASSERT_EQ(allocated, (char*)NULL);
  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), (char*)(memBlock + SHIFT(2, 1, 0)));
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), 1);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(3, 1, 0))), (char*)memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 1))), 1);
}

TEST(memalloc_AllocateBlockWithoutSplit_returnValidPtr) {
  char memBlock[SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE];
  InitNoCheck(memBlock, SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE);
  char *allocated = (char*)memalloc(1);

  ASSERT_EQ(allocated, memBlock + SHIFT(3, 2, 0));
  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block - allocated
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), -1);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 1))), -1);
}

TEST(memalloc_AllocateBlockWithSplit_returnValidPtr) {
  char memBlock[SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES];
  InitNoCheck(memBlock, SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES);
  char *allocated = (char*)memalloc(1);

  ASSERT_EQ(allocated, memBlock + SHIFT(3, 2, 0));
  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), memBlock + SHIFT(4, 2, 1));
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block - allocated
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), -1);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 1))), -1);
  // third block
  ASSERT_EQ(*((int*)(memBlock + SHIFT(4, 2, 1))), 1);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(5, 2, 1))), memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(5, 3, 2))), 1);
}

TEST(memalloc_TryToAllocateBlockWithTooBigSize_returnNULL) {
  char memBlock[SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE];
  InitNoCheck(memBlock, SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE);
  char *allocated = (char*)memalloc(1 + 1);

  ASSERT_EQ(allocated, (char*)NULL);
  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), memBlock + SHIFT(2, 1, 0));
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), 1);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(3, 1, 0))), memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 1))), 1);
}

TEST(memfree_FreeBlockWithoutUnite_returnNone) {
  char memBlock[SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE];
  InitNoCheck(memBlock, SIZE_FOR_TWO_INFO_BLOCKS_AND_ONE_BYTE);
  // fill second block ro make it allocate
  *((char**)(memBlock + SHIFT(1, 0, 0))) = memBlock;
  *((int*)(memBlock + SHIFT(2, 1, 0))) = -1;
  *((int*)(memBlock + SHIFT(3, 2, 1))) = -1;
  // set memory manager info
  SetListStart(memBlock);
  SetListEnd(memBlock);
  SetBeforeLastAlloc(memBlock);

  memfree(memBlock + SHIFT(3, 2, 0));

  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), memBlock + SHIFT(2, 1, 0));
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), 1);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(3, 1, 0))), memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 1))), 1);
}

TEST(memfree_FreeBlockWithUniteWithForward_returnNone) {
  char memBlock[SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES];
  InitNoCheck(memBlock, SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES);
  // fill first block
  *((char**)(memBlock + SHIFT(1, 0, 0))) = memBlock + SHIFT(4, 2, 1);
  // fill second block to make it allocated
  *((int*)(memBlock + SHIFT(2, 1, 0))) = -1;
  *((int*)(memBlock + SHIFT(3, 2, 1))) = -1;
  // fill third block
  *((int*)(memBlock + SHIFT(4, 2, 1))) = 1;
  *((char**)(memBlock + SHIFT(5, 2, 1))) = memBlock;
  *((int*)(memBlock + SHIFT(5, 3, 2))) = 1;
  // set memory manager info
  SetListStart(memBlock);
  SetListEnd(memBlock + SHIFT(4, 2, 1));
  SetBeforeLastAlloc(memBlock);

  memfree(memBlock + SHIFT(3, 2, 0));

  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), memBlock + SHIFT(2, 1, 0));
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), 10 + sizeof(void*));
  ASSERT_EQ(*((char**)(memBlock + SHIFT(3, 1, 0))), memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 14))), 10 + sizeof(void*));
}

TEST(memfree_FreeBlockWithUniteWithBackward_returnNone) {
  char memBlock[SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES];
  InitNoCheck(memBlock, SIZE_FOR_THREE_INFO_BLOCKS_AND_TWO_BYTES);
  // fill first block
  *((char**)(memBlock + SHIFT(1, 0, 0))) = memBlock + SHIFT(2, 1, 0);
  // fill second block
  *((int*)(memBlock + SHIFT(2, 1, 0))) = 1;
  *((char**)(memBlock + SHIFT(3, 1, 0))) = memBlock;
  *((int*)(memBlock + SHIFT(3, 2, 1))) = 1;
  // fill third block to make it allocated
  *((int*)(memBlock + SHIFT(4, 2, 1))) = -1;
  *((int*)(memBlock + SHIFT(5, 3, 2))) = -1;
  // set memory manager info
  SetListStart(memBlock);
  SetListEnd(memBlock + 12);
  SetBeforeLastAlloc(memBlock);

  memfree(memBlock + 33);

  // first block
  ASSERT_EQ(*((int*)(memBlock)), 0);
  ASSERT_EQ(*((char**)(memBlock + SHIFT(1, 0, 0))), memBlock + SHIFT(2, 1, 0));
  ASSERT_EQ(*((int*)(memBlock + SHIFT(1, 1, 0))), 0);
  // second block
  ASSERT_EQ(*((int*)(memBlock + SHIFT(2, 1, 0))), 10 + sizeof(void*));
  ASSERT_EQ(*((char**)(memBlock + SHIFT(3, 1, 0))), memBlock);
  ASSERT_EQ(*((int*)(memBlock + SHIFT(3, 2, 14))), 10 + sizeof(void*));
}
