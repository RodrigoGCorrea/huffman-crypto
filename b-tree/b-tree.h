#ifndef HUFFMAN_CRYPTO_B_TREE_H
#define HUFFMAN_CRYPTO_B_TREE_H

#include <stdbool.h>

typedef struct bt_tree bt_Tree;
typedef struct bt_node bt_Node;

struct bt_tree{
    int t;
    bt_Node *head;
};

struct bt_node{
    int nkey, *key;
    bool leaf;

    struct bt_node **child;
};


bt_Tree* bt_Create(int t);

void bt_Insert(bt_Tree *bt, int key);
void bt_Remove(bt_Tree *bt, int key);

bt_Node* bt_Search(bt_Tree *bt, int key);

void bt_Destroy(bt_Tree* bt);

#endif //HUFFMAN_CRYPTO_B_TREE_H
