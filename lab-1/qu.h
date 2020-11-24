typedef struct node_t {

	int data;
	struct node_t* next;

} node_t;

typedef struct {

	int size;
	int first, last;
	int* data;

} quArray_t;

typedef struct {

	int size;
	node_t* first;
	node_t* last;

} quList_t;

int IsQuArrayEmpty(quArray_t quAr);
int PushQuArray(int data, quArray_t* quAr);
int PopQuArray(quArray_t* quAr);
int PushQuList(int data, quList_t* quLi);
int PopQuList(quList_t* quLi);
int* InitArray(int size);
quList_t InitQuList(int size, int* data);