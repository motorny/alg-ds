#include "pch.h"
extern "C" {
#include"memallocator.h"
}
#define FALSE 0
#define TRUE 1

//meminit
TEST(meminit, NULL_returnFalse) {
  void* p = NULL;
  ASSERT_EQ(meminit(p, 10), FALSE);
}
TEST(meminit, incorrectSize_returnFalse) {
  void* p = malloc(100);
  ASSERT_EQ(meminit(p, -1), FALSE);
  free(p);
}
TEST(meminit, smallSize_returnFalse) {
  void* p = malloc(memgetminimumsize() - 1);
  ASSERT_EQ(meminit(p, memgetminimumsize() - 1), FALSE);
  free(p);
}
TEST(meminit, normalSize_returnTrue) {
  void* p = malloc(memgetminimumsize() + 1);
  ASSERT_EQ(meminit(p, memgetminimumsize() + 1), TRUE);
  free(p);
}
//memmalloc
TEST(memalloc, incorrectlSize_returnNULL) {
  void* p = malloc(memgetminimumsize() + 1);
  meminit(p, memgetminimumsize() + 1);
  ASSERT_TRUE(memalloc(-1) == NULL);
  memdone();
  free(p);
}
TEST(memalloc, smallSize_returnNULL) {
  void* p = malloc(memgetminimumsize() + 1);
  meminit(p, memgetminimumsize() + 1);
  ASSERT_TRUE(memalloc(memgetminimumsize()- 1) == NULL);
  memdone();
  free(p);
}
TEST(memalloc, notInitialized_returnNULL) {
  void* p = malloc(memgetminimumsize() + 1);
  ASSERT_TRUE(memalloc(memgetminimumsize() + 1) == NULL);
  free(p);
}
TEST(memalloc, notEnoughMemory_returnNULL) {
  void* p = malloc(memgetminimumsize() + sizeof(int));
  meminit(p,  memgetminimumsize() + sizeof(int));
  char* s = (char*)memalloc(memgetminimumsize());
  ASSERT_TRUE(s == NULL);
  memdone();
  free(p);
}
TEST(memalloc, normalWork_returnValidPointer) {
  void* p = malloc(2 * memgetminimumsize());
  meminit(p, 2 * memgetminimumsize());
  char* s = (char*)memalloc(memgetminimumsize());
  ASSERT_TRUE(s != NULL);
  memfree(s);
  memdone();
  free(p);
}
//memfree
TEST(memfree, freeNULL_notFall) {
  void* p = malloc(memgetminimumsize() + sizeof(int));
  meminit(p, memgetminimumsize() + sizeof(int));
  char* s = (char*)memalloc(memgetminimumsize());
  memfree(s);
  memdone();
  free(p);
}
TEST(memfree, freeNotOurMemory_notFall) {
  char* p = (char*)malloc(memgetminimumsize() + sizeof(int));
  meminit(p, memgetminimumsize() + sizeof(int));
  memfree(p + 100);
  memdone();
  free(p);
}
TEST(memfree, freeNotOurAllocatedMemory_notFall) {
  char* p = (char*)malloc(10 * memgetminimumsize());
  meminit(p, 10 * memgetminimumsize());
  char* s = (char*)memalloc(1);
  memfree(p + 5 * memgetminimumsize() + sizeof(char));
  memdone();
  free(p);
}
TEST(memfree, normalWork_notFall) {
  char* p = (char*)malloc(10 * memgetminimumsize());
  meminit(p, 10 * memgetminimumsize());
  char* s = (char*)memalloc(1);
  memfree(s);
  memdone();
  free(p);
}