#define OUT_OF_MEM -1
#define SUCCESS 0
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
int PutOnTheRightPlace(char* word, DoubleLinkedList* list);
DoubleLinkedList* CreateDoubleLinkedList(int RESULT);
void DeleteDoubleLinkedList(DoubleLinkedList** list);
int PushFront(DoubleLinkedList* list, char* data);
int PushBack(DoubleLinkedList* list, char* value);
int Compare(char* word, char* wordFromList);
int PutBeforeElement(DoubleLinkedList* eist, Node* element, char* value);
void PrintDoubleLinkedListMoreThanN(DoubleLinkedList* list, int N);
void PrintDoubleLinkedListTheN(DoubleLinkedList* list, int N);
