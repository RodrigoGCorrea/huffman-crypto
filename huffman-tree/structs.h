#ifndef HUFFMAN_CRYPTO_STRUCTS_H
#define HUFFMAN_CRYPTO_STRUCTS_H

typedef struct hfmt_tree hfm_Tree;
typedef struct hfm_node hfm_Node;

typedef struct hfm_minheap hfm_Minheap;
typedef hfm_Node hfm_T_Minheap;

struct hfm_node {
    float prob;
    char symbol;
    struct hfm_node *left, *right;
};

struct hfmt_tree {
    hfm_Minheap *pool;
    hfm_Node *head;
};

struct hfm_minheap {
    hfm_T_Minheap **data;
    int size;
    int tail;
};


#endif //HUFFMAN_CRYPTO_STRUCTS_H
