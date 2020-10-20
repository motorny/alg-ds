#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

int meminit(void *pMemory, int size);

void memdone();

void* memalloc(int size);

void memfree(void *p);

int memgetminimumsize();

int memgetblocksize();

int CheakMemoryLeaks();

#ifdef __cplusplus
}
#endif
#endif
