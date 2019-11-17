#ifndef HUFFMAN_CRYPTO_HUFFMAN_TREE_H
#define HUFFMAN_CRYPTO_HUFFMAN_TREE_H

#include <stdbool.h>

typedef struct hfmt {
    int prob;
    char symbol;
    bool leaf;
    int r_a, l_a;
    struct hfmt *right, *left;
} hfm_Tree;

hfm_Tree* hfm_Create();
hfm_Tree* hfm_Insert(hfm_Tree *hfmt, int prob, char symbol);
void hfm_Remove();

#endif //HUFFMAN_CRYPTO_HUFFMAN_TREE_H
