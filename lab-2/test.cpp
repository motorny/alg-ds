#include "pch.h"

extern "C" {
   #include "memallocator.h"
}



TEST(meminit, NullPointerToMemory_ReturnERROR) {
    char* memory = NULL;

    EXPECT_EQ(meminit(memory, 1), ERROR);

}

TEST(meminit, Smallsize_ReturnERROR) {
    char* memory = (char*)malloc(memgetminimumsize() - 1);

    EXPECT_EQ(meminit(memory, memgetminimumsize() - 1), ERROR);

    free(memory);
}

TEST(meminit, SuccessCase_ReturnsSUCCESS) {
    char* memory = (char*)malloc(memgetminimumsize() + 1);

    EXPECT_EQ(meminit(memory, memgetminimumsize() + 1), SUCCESS);

    free(memory);
}

TEST(memalloc, AllocateNegativeSize_ReturnsNULL) {
    char* memory = (char*)malloc(memgetminimumsize() + 1);
    meminit(memory, memgetminimumsize() + 1);
    char* ptr = (char*)memalloc(-1);

    EXPECT_EQ(ptr, (char*)NULL);

    free(memory);
}

TEST(memalloc, NotEnoughMem_ReturnsNULL) {
    void* memory = malloc(memgetminimumsize() + 1);
    meminit(memory, memgetminimumsize() + 1);
    void* ptr = memalloc(2);

    EXPECT_TRUE(ptr == NULL);
    memfree(ptr);
    free(memory);
}

TEST(memalloc, AllocateValidMemory_ReturnPtr) {
    char* memory = (char*)malloc(memgetminimumsize() + 1);
    meminit(memory, memgetminimumsize() + 1);
    char* ptr = (char*)memalloc(1);


    EXPECT_NE(ptr, (char*)NULL);

    free(memory);
}