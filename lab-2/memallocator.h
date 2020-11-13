#pragma once
#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

	// Init memory system with memory block pMemory.
	int meminit(void* pMemory, int size);

	// You can implement memory leak checks here
	void memdone();

	// Allocate memory block of size 'size'.
	// Returns pointer to memory block is success, 0 otherwise
	void* memalloc(int size);

	// Free memory previously allocated by memalloc
	void memfree(void* p);

	// Return minimum size in bytes of the memory pool to allocate 0-bytes block
	int memgetminimumsize();


	// Returns size in bytes of additional information per allocation
	int memgetblocksize();


	

#ifdef __cplusplus
}
#endif

#endif