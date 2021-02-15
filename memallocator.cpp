#include "memallocator.h"

typedef enum bool_t {
	FALSE,
	TRUE
}bool_t;

typedef struct blockBegin_t {
	int size;
	struct blockBegin_t* next;
	bool_t isEmpty;
} blockBegin_t;

typedef struct blockEnd_t {
	int size;
}blockEnd_t;

//memory block:
//||isEmpty||size||nextBlock||userData||size||

void* leftBorder = 0;
void* rightBorder = 0;

blockBegin_t* memListHead = 0;
blockBegin_t* memListLast = 0;



int meminit(void* pMemory, int size) {
	if (pMemory == 0 || size <= memgetminimumsize())
		return FALSE;

	leftBorder = pMemory;
	rightBorder = (void*)((char*)pMemory + size);

	memListHead = memListLast = (blockBegin_t*)pMemory;
	memListHead->isEmpty = TRUE;
	memListHead->next = memListLast;
	memListHead->size = size;
	
	blockEnd_t* listHeadEnd = (blockEnd_t*)((char*)memListHead + memgetminimumsize() - sizeof(blockEnd_t));
	listHeadEnd->size = size;

	return TRUE;
}

void memdone() {
	return;
}

void* memalloc(int size) {
	//check if size correct && listHead exists
	if (size <= 0 || memListHead == 0)
		return 0;

	int requiredSize = size + memgetminimumsize();

	blockBegin_t* temp = memListHead;
	blockBegin_t* tempPrev = memListLast;
	bool_t isFound = FALSE; //flag showing if we found fit memory block
	while (temp != memListLast) {
		if (temp->size >= requiredSize) {
			isFound = TRUE;
			break;
		}
		temp = temp->next;
		tempPrev = tempPrev->next;
	}
	//if isFound == FALSE and (while) is ended then temp == memListLast
	//need to check it is suitable 
	if (isFound == FALSE) {
		if (temp->size >= requiredSize) {
			isFound = TRUE;
		}
	}
	//now we checked all list

	//if no suitable block then return 0
	if (isFound == FALSE)
		return 0;
	
	int leftSpace = temp->size - requiredSize;
	if (leftSpace > memgetminimumsize()) {
		//there is a space for new memory block
		//need to find place for new memory block
		blockBegin_t* newBlock = (blockBegin_t*)((char*)temp + requiredSize);
		blockEnd_t* newBlockEnd = (blockEnd_t*)((char*)temp + temp->size - sizeof(blockEnd_t));

		blockEnd_t* tempBlockEnd = (blockEnd_t*)((char*)temp + requiredSize - sizeof(blockEnd_t));

		newBlock->isEmpty = TRUE;
		if (memListHead != memListLast) {
			newBlock->next = temp->next;
		}
		else {
			newBlock->next = newBlock;
		}
		newBlock->size = leftSpace;
		newBlockEnd->size = leftSpace;
		tempPrev->next = newBlock;
		if (memListHead != memListLast) {
			memListHead = newBlock;
			memListLast = tempPrev;
		}
		else {
			memListHead = memListLast = newBlock;
		}

		temp->isEmpty = FALSE;
		temp->next = 0;
		temp->size = requiredSize;
		tempBlockEnd->size = requiredSize;
	}
	else {
		//there is no space for new memory block so we'll give what we have
		temp->isEmpty = FALSE;
		//temp->size doesn't change 

		//need to pop temp from list
		//but if temp==tempPrev (that means that there's only 1 elem in list) 
		//need to nullify memListHead && memListLast
		if (memListHead == memListLast) {
			memListHead->next = 0;
			memListHead = memListLast = 0;
		}
		else {
			//we change list head because of next-fit alg
			memListHead = temp->next;
			tempPrev->next = temp->next;
			temp->next = 0;
		}
	}
	return (void*)((char*)temp + sizeof(blockBegin_t));
}

void memfree(void* p) {
	if (p == 0)
		return;
	blockBegin_t* center = (blockBegin_t*)((char*)p - sizeof(blockBegin_t));
	blockBegin_t* right = (blockBegin_t*)((char*)center + center->size);
	blockEnd_t* rightEnd = (blockEnd_t*)((char*)right + right->size - sizeof(blockEnd_t));


	blockEnd_t* leftEnd = (blockEnd_t*)((char*)p - memgetminimumsize());
	blockBegin_t* left = (blockBegin_t*)((char*)center - leftEnd->size);

	enum {
		NO_UNION,
		RIGHT_UNION,
		LEFT_UNION,
		RL_UNION
	} flag;

	flag = NO_UNION;

	if ((char*)rightEnd + sizeof(blockEnd_t) <= rightBorder && (char*)center + center->size < rightBorder) {
		if (right->isEmpty == TRUE)
			flag = RIGHT_UNION;
	}

	if (leftBorder <= left && leftBorder<center) {
		if (left->isEmpty == TRUE)
			flag = LEFT_UNION;
	}

	if ((leftBorder <= left && (char*)rightEnd + sizeof(blockEnd_t) <= rightBorder) &&
		((char*)center + center->size < rightBorder && leftBorder < center)) {
		if (left->isEmpty == TRUE && right->isEmpty == TRUE)
			flag = RL_UNION;
	}

	switch (flag)
	{
	case NO_UNION:
	{
		center->isEmpty = TRUE;
		if (memListHead == 0 || memListLast == 0) {
			memListHead = center;
			memListLast = center;
			center->next = center;
		}
		else {
			memListLast->next = center;
			center->next = memListHead;
			memListLast = center;
		}
		break;
	}
	case RIGHT_UNION:
	{
		center->isEmpty = TRUE;
		center->size = center->size + right->size;
		rightEnd->size = center->size;
		//check if head==last
		if (memListHead == memListLast) {
			center->next = center;
			memListHead = memListLast = center;
		}
		else {
			//if head!=last then might be there's only head and last in list
			if (memListHead->next = memListLast) {
				if (right == memListLast) {
					center->next = memListHead;
					memListLast = center;
					memListHead->next = memListLast;
				}
				else {
					center->next = memListLast;
					memListHead = center;
					memListLast->next = memListHead;
				}
			}
			else {
				//there're >=3 elements
				if (right == memListHead) {
					center->next = right->next;
					memListHead = center;
					memListLast->next = center;
				}
				if (right == memListLast) {
					center->next = memListHead;
					blockBegin_t* prevLast = memListHead;
					while (prevLast->next != memListLast) {
						prevLast = prevLast->next;
					}
					prevLast->next = center;
					memListLast = center;
				}
				if (right != memListHead && right != memListLast) {
					center->next = right->next;
					blockBegin_t* prevRight = right;
					while (prevRight->next != right) {
						prevRight = prevRight->next;
					}
					prevRight->next = center;
				}
			}
		}
		break;
	}
	case LEFT_UNION:
	{
		left->isEmpty = TRUE;
		left->size = left->size + center->size;
		//don't forget to change the end of descriptor
		blockEnd_t* centerEnd = (blockEnd_t*)((char*)center+center->size-sizeof(blockEnd_t));
		centerEnd->size = left->size;
		break;
	}
	case RL_UNION:
	{
		//Right Union
		center->isEmpty = TRUE;
		center->size = center->size + right->size;
		rightEnd->size = center->size;
		//check if head==last
		if (memListHead == memListLast) {
			center->next = center;
			memListHead = memListLast = center;
		}
		else {
			//if head!=last then may be there's only head and last in list
			if (memListHead->next = memListLast) {
				if (right == memListLast) {
					center->next = memListHead;
					memListLast = center;
					memListHead->next = memListLast;
				}
				else {
					center->next = memListLast;
					memListHead = center;
					memListLast->next = memListHead;
				}
			}
			else {
				//there're >=3 elements
				if (right == memListHead) {
					center->next = right->next;
					memListHead = center;
					memListLast->next = center;
				}
				if (right == memListLast) {
					center->next = memListHead;
					blockBegin_t* prevLast = memListHead;
					while (prevLast->next != memListLast) {
						prevLast = prevLast->next;
					}
					prevLast->next = center;
					memListLast = center;
				}
				if (right != memListHead && right != memListLast) {
					center->next = right->next;
					blockBegin_t* prevRight = right;
					while (prevRight->next != right) {
						prevRight = prevRight->next;
					}
					prevRight->next = center;
				}
			}
		}

		//Left Union

		//need to check if now list consists of only 2 elements
		if (memListHead->next == memListLast) {
			memListHead = memListLast = left;
			left->next = left;
			left->size = left->size + center->size;
			//don't forget to change the end of descriptor
			rightEnd->size = left->size;
		}
		else {
			blockBegin_t* prevCenter = memListHead;
			while (prevCenter->next != center) {
				prevCenter = prevCenter->next;
			}
			prevCenter->next = center->next;
			if (memListLast == center)
				memListLast = prevCenter;
			if (memListHead == center)
				memListHead = center->next;

			blockBegin_t* prevLeft = memListHead;
			while (prevLeft->next != left) {
				prevLeft = prevLeft->next;
			}
			prevLeft->next = left->next;
			if (memListLast == left)
				memListLast = prevLeft;
			if (memListHead == left)
				memListHead = left->next;

			left->size = left->size + center->size;
			blockEnd_t* centerEnd = rightEnd;
			centerEnd->size = left->size;

			left->next = memListHead;
			memListLast->next = left;
			memListLast = left;
		}
		break;
	}

	}
}

int memgetminimumsize() {
	return sizeof(blockBegin_t)+sizeof(blockEnd_t);
}

int memgetblocksize() {
	return sizeof(blockBegin_t) + sizeof(blockEnd_t);
}