#pragma once

int memgetminimumsize(void);

int memgetblocksize(void);

int meminit(void* block, int size);

void* memalloc(int size);

void memfree(void* point);

void memdone(void);

