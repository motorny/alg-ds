#include <stdlib.h>
#include <cstddef>
#include <stdbool.h>
#include <bits/stdc++.h>
#ifdef __cplusplus
extern "C" {
#endif

void *managed_memory_start;
void *last_valid_address;


struct Node {
    bool is_available;
//    unsigned long long *next;
    struct Node *prev;
//    char *data;
    int segment_size;
};
struct Node * get_next_element(struct Node* element){
    char * cur_ptr=(char*)element;
    return (struct Node*) (cur_ptr + element->segment_size + sizeof(struct Node));
}
int memgetminimumsize() {

    return (sizeof (struct Node));
}
int memgetblocksize() {
    return (sizeof(struct Node));
}
char*  L;
char * R;
bool is_good_ptr(struct Node* p) {
    return p == nullptr || (L <= (char*)p && (char*)p + sizeof(struct Node) <= R);
}


int meminit(void *pMemory, int size) {
    L = (char*) pMemory;
    R = L + size;
    managed_memory_start = pMemory;
    last_valid_address = (void *) ((char *) pMemory + size);
    if ( !pMemory|| size < memgetminimumsize() )
        return 0;

    struct Node *element = (struct Node *) pMemory;
    element->segment_size = size - sizeof(struct Node);
    element->prev = nullptr;
    element->is_available = true;
    return 1;
}

void memdone() {
//    assert((char*)managed_memory_start == L);
//    assert((char*)last_valid_address == R);
//    struct Node * p = (struct Node*) managed_memory_start;
//    assert(p->is_available);
//    assert((void*)get_next_element(p) == last_valid_address);

//    assert(&managed_memory_start-&last_valid_address);
}

int get_n_element() {
    int answer = 0;
    struct Node * p = (struct Node*) managed_memory_start;
    for (; (void*)p != last_valid_address;) {
        p = get_next_element(p);
        answer++;
    }
    return answer;
}

void print_availability() {
    struct Node * p = (struct Node*) managed_memory_start;
    for (; (void*)p != last_valid_address;) {
        std::cout << p->is_available << " ";
        p = get_next_element(p);
    }
    std::cout<< std::endl;
}

using std::cout;
using std::endl;
void *memalloc(int size) {
    char *cur_ptr = (char *) managed_memory_start;
    for (; cur_ptr != last_valid_address;) {

        struct Node *element = (struct Node *) cur_ptr;

        if (element->is_available && element->segment_size >= size) {

            int new_element_size = element->segment_size - size - (int) sizeof(struct Node);

            if (new_element_size <= 0) {
                element->is_available = false;
            } else {
                struct Node *new_element = (struct Node *) (cur_ptr + size + sizeof(struct Node));

                struct Node *next_element =get_next_element(element);
                if (next_element != last_valid_address) {

                    next_element->prev = new_element;
                }
                new_element->segment_size = new_element_size;
                new_element->is_available = true;
                new_element->prev = element;
                assert(is_good_ptr(new_element->prev));
                element->is_available = false;
                element->segment_size = size;
            }
            char* ret_ptr = cur_ptr + sizeof(struct Node);
            assert(L <= ret_ptr && ret_ptr + size <= R);
            return cur_ptr + sizeof(struct Node);
        } else {

            cur_ptr = (char* ) get_next_element(element);
        }

    }

    return nullptr;

}
void memfree(void *p) {
    struct Node *element = (Node *) ((char*)p - sizeof(struct Node));
    assert(is_good_ptr(element));
    assert(L <= (char*)element && (char*)element + sizeof(struct Node) <= R);
    struct Node *next_element =  get_next_element(element);
    assert(!element->is_available);
    element->is_available = true;
    if (next_element != last_valid_address && next_element->is_available) {
        struct Node *second = get_next_element(next_element);
        if (second != last_valid_address) {
            assert(is_good_ptr(second));
            second->prev = element;
            assert(is_good_ptr(second->prev));
        }
        element->segment_size+=next_element->segment_size+sizeof (struct Node);
    }
    next_element =  get_next_element(element);
//    assert(is_good_ptr(element->prev));
    struct Node *prev_element = (struct Node *) element->prev;
    if (prev_element!= nullptr && prev_element->is_available ) {//?&& prev_element!= managed_memory_start
        if (next_element != last_valid_address) {
            next_element->prev = prev_element;
//            assert(is_good_ptr(next_element->prev));
        }
        prev_element->segment_size += element->segment_size + sizeof(struct Node);

    }


}

#ifdef __cplusplus
}
#endif
