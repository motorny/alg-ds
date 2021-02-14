#include "memallocator.h"
#include <stdlib.h>

typedef struct prenode_t {
	struct prenode_t* next;
	struct prenode_t* prev;
	char isFree;
	int size;
}prenode_t;

static prenode_t* freeList; //the actual list of free space
static void* memory; //the start
static int allocSize; //the amount (volume?) of given space

static void _deleteNode(prenode_t* node) {
	//cuts the given node from a list
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	else {
		freeList = node->next; //note: if node->next is also empty, all the memory is used up, list is empty
	}
}

static void _addNode(prenode_t* start, prenode_t* node) {
	//adds node "node" to the list beginning with "start"
	if (start != NULL) {
		while (start->next != NULL) {
			start = start->next;
		}
		start->next = node;
		node->next = NULL;
		node->prev = start;
	}
	else {
		//yeah it can happen, e.g. if all the memory is used up
		freeList = node;
		node->next = NULL;
		node->prev = NULL;
	}
}

int meminit(void* pMemory, int size) {
	freeList = (prenode_t*)pMemory;
	memory = pMemory;
	allocSize = size;
	int* pEnd;

	if (pMemory != NULL && size > memgetminimumsize()) {
		freeList->isFree = 1; //yeah, by default
		freeList->next = NULL;
		freeList->prev = NULL;
		freeList->size = allocSize - memgetblocksize(); //documented usage of blocksize

		pEnd = (int*)((char*)(freeList+1)+freeList->size); //going to the end of given memory and marking it
		*pEnd = freeList->size;
		return 1;
	}
	else {
		return 0;
	}

	
};

void* memalloc(int size) {
	prenode_t* iter = freeList;
	void* retval;
	int* pEnd;
	int tempMemSize;

	while (iter != NULL && iter->next != NULL && iter->size < size) {
		//going to drop right away 
		//if the list is empty somehow, 
		//else it's going to find the first valid element
		//if available
		iter = iter->next;
	}
	if (iter == NULL || iter->size < size) { 
		//search has failed, either the list is empty
		//or not enough memory in any given node
		retval = NULL;
	}
	else {
		if (iter->size <= size + memgetblocksize()) { 
			//exact match, no need to waste space on new block, 
			//can just take it from the list
			//doesn't make much difference if can't cut a block from it though
			retval = (char*)(iter)+sizeof(prenode_t);
			iter->isFree = 0;
			_deleteNode(iter);
		}
		else { 
			//got to cut leftovers there
			pEnd = (int*)((char*)(iter+1)+iter->size);
			iter->size -= size + memgetblocksize(); //going to leave the beggining in the list, seems more convinient
			tempMemSize = iter->size;
			*pEnd = size;
			iter = (prenode_t*)((char*)(pEnd)-size) - 1; //(char*)(pEnd)-size jumps right to the retval, descr is a bit before
			iter->isFree = 0;
			iter->size = size;
			pEnd = (int*)(iter)-1; //got to write down the size of the leftover block
			*pEnd = tempMemSize;
			retval = (char*)(iter)+sizeof(prenode_t);
		}
	}
	return retval;
};

void memfree(void* p) {
	prenode_t* iter;
	prenode_t* temp;
	int* pEnd;
	int* pEndLeft;

	iter = (prenode_t*)p - 1;
	iter->isFree = 1;

	//given that any block was added to the list with this function, any node should have only taken physical neighbors if any
	//if that is true, then if any of neighbours of this memory part are free, then we merge them with this
	//and so the following node's neighbours are taken if exist

	//check what's on the right
	temp = (prenode_t*)((char*)(iter + 1) + iter->size + sizeof(int));
	if ((char*)memory <= (char*)temp && (char*)temp <= (char*)memory + allocSize && temp->isFree == 1) { 
		//node on the right should be tailored to the center
		//also check the boundaries, should be useful
		iter->size += temp->size + memgetblocksize();
		_deleteNode(temp);
		pEnd = (int*)((char*)(temp + 1) + temp->size);
	}
	else {
		pEnd = (int*)(temp)-1; //regardless of boundaries, there on this place should be an int, we placed it here
		                       //before allocating the memory
	}

	//check what's on the left
	pEndLeft = (int*)iter - 1;
	if ((char*)memory <= (char*)pEndLeft && (char*)pEndLeft <= (char*)memory + allocSize) {
		temp = (prenode_t*)((char*)(pEndLeft)-*pEndLeft) - 1;
		if ((char*)memory <= (char*)temp && (char*)temp <= (char*)memory + allocSize && temp->isFree == 1) {
			//node on the center should be tailored to the left
			temp->size += iter->size + memgetblocksize(); //if right block was free, it's size would be counted
			*pEnd = temp->size;
		}
		else {
			//in "if" case the node was already in a list, only the content has changed
			//there we've got a new element, and so it should be added to the list
			_addNode(freeList, iter);
			*pEnd = iter->size;
		}
	}
	else {
		//in "if" case the node was already in a list, only the content has changed
		//there we've got a new element, and so it should be added to the list
		_addNode(freeList, iter);
		*pEnd = iter->size;
	}
};

int memgetminimumsize() {
	return sizeof(prenode_t) + sizeof(int);
};

int memgetblocksize() {
	return sizeof(prenode_t) + sizeof(int);
};

void memdone() {

};