#ifndef HUFFMAN_CRYPTO_LIST_H
#define HUFFMAN_CRYPTO_LIST_H

typedef struct bt_list bt_List;

struct bt_list {
    char *info;
    struct bt_list *next;
};

bt_List* bt_Create_List();
bt_List* bt_Append_List(bt_List *btl, char *info);

void bt_Destroy_List(bt_List *btl);


#endif //HUFFMAN_CRYPTO_LIST_H
