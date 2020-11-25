#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include"memallocator.h"

#define SUCCESS 1
#define FAILURE 0
#define MAGICKEY 2105
#define USED -1

	typedef struct block_head {
		int size;
		int magicKey;
		struct block_head* next;
	} block_head_t;

	typedef struct block_end {
		int size;
	} block_end_t;

	int memSize = 0;
	char* memory = NULL;
	block_head_t* firstBlock = NULL;

	int memgetminimumsize() {
		return sizeof(block_head_t) + sizeof(int);
	}

	int memgetblocksize() {
		return sizeof(block_head_t) + sizeof(int);
	}

	int meminit(void* pMemory, int size) {
		int min = memgetminimumsize();
		if (pMemory == NULL || size < min)
			return FAILURE;

		memory = (char*)pMemory;
		memSize = size;
		firstBlock = (block_head_t*)pMemory;
		firstBlock->magicKey = MAGICKEY;
		firstBlock->size = size - min;
		firstBlock->next = NULL;
		((block_end_t*)((char*)firstBlock + sizeof(block_head_t) + firstBlock->size))->size = firstBlock->size;
		return SUCCESS;
	}

	void memdone() {
		memSize = 0;
		memory = NULL;
		firstBlock = NULL;
	}

	void* memalloc(int size) {
		block_head_t** toFind = &firstBlock;
		block_head_t** curBlock = NULL;
		block_head_t* newBlock = NULL;
		int min = memgetminimumsize();
		int n = 0;

		if (memory == NULL || size < 0 || size + min > memSize) {
			return NULL;
		}

		//findind fit
		while (*toFind) {
			if ((*toFind)->size >= size) {
				curBlock = toFind;
				n++;
				if (n == 2)
					break;
			}
			toFind = &(*toFind)->next;
		}

		if (curBlock == NULL) {
			return NULL;
		}

		//changing list
		newBlock = *curBlock;
		if (newBlock->size <= size + min) {
			*curBlock = (*curBlock)->next;
			newBlock->magicKey = MAGICKEY;
			newBlock->next = NULL;
			((block_end_t*)((char*)newBlock + sizeof(block_head_t) + newBlock->size))->size = USED;
			return (void*)((char*)newBlock + sizeof(block_head_t));
		}

		//otherwise
		(*curBlock) = (block_head_t*)((char*)newBlock + min + size);
		(*curBlock)->size = newBlock->size - min - size;
		(*curBlock)->next = newBlock->next;
		((block_head_t*)((char*)newBlock + newBlock->size + sizeof(block_head_t)))->size = (*curBlock)->size;
		newBlock->magicKey = MAGICKEY;
		newBlock->size = size;
		newBlock->next = NULL;
		((block_end_t*)((char*)newBlock + sizeof(block_head_t) + newBlock->size))->size = USED;

		return (void*)((char*)newBlock + sizeof(block_head_t));
	}

	void memfree(void* p) {
		block_head_t* head;
		block_end_t* end;
		//heads and ends for uniting with other blocks
		block_head_t* pHead, * nHead, ** temp;
		block_end_t* pEnd, * nEnd;
		int min = memgetminimumsize();

		if (p == NULL || (char*)p < (char*)memory || (char*)p >= (char*)memory + memSize)
			return;

		head = (block_head_t*)((char*)p - sizeof(block_head_t));
		end = (block_end_t*)((char*)p + head->size);
		if (head->magicKey != MAGICKEY)
			return;

		//with left (prev)
		pEnd = (block_end_t*)((char*)p - min);
		pHead = (block_head_t*)((char*)p - min - pEnd->size - sizeof(block_head_t));
		if ((char*)pEnd < (char*)memory || pEnd->size == USED) {
			end->size = head->size;
			head->next = firstBlock;
			firstBlock = head;
		}
		else {
			pHead->size = head->size + pHead->size + min;
			end->size = pHead->size;
			head = pHead;
		}

		//with right (next)
		nHead = (block_head_t*)((char*)end + sizeof(block_end_t));
		nEnd = (block_end_t*)((char*)nHead + nHead->size + sizeof(block_head_t));
		if ((char*)nHead >= (char*)(memory + memSize) || nHead->magicKey != MAGICKEY)
			return;

		if (nEnd->size != USED) {
			head->size = nHead->size + head->size + min;
			nHead->magicKey = 0;
			nEnd->size = head->size;
			temp = &firstBlock;
			while (*temp != NULL && *temp != nHead) {
				temp = &(*temp)->next;
			}
			if (*temp == nHead) {
				*temp = (*temp)->next;
			}
		}

	}

#ifdef __cplusplus
}
#endif