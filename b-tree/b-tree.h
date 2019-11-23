#ifndef HUFFMAN_CRYPTO_B_TREE_H
#define HUFFMAN_CRYPTO_B_TREE_H

#include <stdbool.h>

typedef struct bt_tree bt_Tree;
typedef struct bt_node bt_Node;
typedef struct bt_info bt_Info;

typedef bt_Info bt_T_Info;

struct bt_tree {
    int t;
    bt_Node *head;
};

struct bt_node {
    int nkey;
    bool leaf;

    bt_T_Info *info;

    struct bt_node **child;
};

struct bt_info {
    char key;
    float prob;
};


bt_Tree* bt_Create(int t);

void bt_Insert(bt_Tree *bt, bt_T_Info info);
void bt_Remove(bt_Tree *bt, bt_T_Info info);

bt_Node* bt_Search(bt_Tree *bt, bt_T_Info info);

void bt_Destroy(bt_Tree* bt);

#endif //HUFFMAN_CRYPTO_B_TREE_H
