#include <stdio.h>

#include "huffman-tree/huffman-tree.h"

int main() {
    hfm_Tree *t = hfm_Create();

    t = hfm_Insert(t, 1, 'f');
    t = hfm_Insert(t, 2, 'e');
    t = hfm_Insert(t, 3, 'd');
    t = hfm_Insert(t, 4, 'c');
    t = hfm_Insert(t, 5, 'b');
    t = hfm_Insert(t, 6, 'a');

    return 0;
}
