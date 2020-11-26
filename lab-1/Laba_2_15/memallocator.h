#pragma once
#include "pch.h"

	int meminit(void* pMem, int size);
	void memdone();
	void* memalloc(int size);
	void memfree(void* p);
	int memgetminimumsize();
	int memgetblocksize();
