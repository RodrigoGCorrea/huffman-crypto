#ifndef HUFFMAN_CRYPTO_HUFFMAN_TREE_H
#define HUFFMAN_CRYPTO_HUFFMAN_TREE_H

#include <stdbool.h>

#include "minheap.h"

#define HFM_POOL_SIZE 20
#define HFM_POOL_SIZE_INC 20

typedef struct hfm_node {
    int prob;
    char symbol;
    bool leaf;
    struct hfm_node *left, *right;
} hfm_Node;

typedef struct hfmt_tree {
    hfm_Minheap *pool;
    hfm_Node *head;
} hfm_Tree;


hfm_Tree* hfm_Create();

void hfm_Insert_Pool(hfm_Tree* ht, hfm_T_Minheap rune);
void hfm_Gen_Tree(hfm_Tree* ht);

void hfm_Destroy();

// TODO: LOW PRIORITY
hfm_Tree* hfm_Insert(hfm_Tree *ht, int prob, char symbol);
void hfm_Insert_Pool_From_Array(hfm_Tree* ht, hfm_T_Minheap *arr_rune);

#endif //HUFFMAN_CRYPTO_HUFFMAN_TREE_H
