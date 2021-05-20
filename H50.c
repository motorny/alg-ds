#include <stdio.h>
#include "aatree.h"

void do_nothing(void* val) {
}

void print(const aanode* n, void* arg) {
    printf("key %d\n", n->key);
}

int main(void) {
    aatree* t = new_aatree(do_nothing);
    for (int i = 0; i < 10; ++i) {
        aa_insert(t, i, NULL);
    }
    aa_foreach(t, print, NULL);
    delete_aatree(t);
    return 0;
}