typedef struct Node {
	char* value;
	struct Node* next;
	struct Node* prev;
} Node;
typedef struct DoubleLinkedList {
	int size;
	Node* head;
	Node* tail;
}DoubleLinkedList;
void PutOnTheRightPlace(char* word, DoubleLinkedList* List);
void Push(DoubleLinkedList* List, char* value);
DoubleLinkedList* CreateDoubleLinkedList();
void DeleteDoubleLinkedList(DoubleLinkedList** List);
void PushFront(DoubleLinkedList* list, char* data);
void PushBack(DoubleLinkedList* list, char* value);
int Compare(char* Word, char* WordFromList);
void PutBeforeElement(DoubleLinkedList* List, Node* Element, char* value);
void PrintMoreThanN(int N, char* value);
void PrintTheN(int N, char* value);
void PrintDoubleLinkedList(DoubleLinkedList* List, void (*fun)(int N, char* value), int N);
