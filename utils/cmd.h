#ifndef HUFFMAN_CRYPTO_CMD_H
#define HUFFMAN_CRYPTO_CMD_H

#include "../b-tree/b-tree.h"
#include "../b-tree/encrypt.h"
#include "../huffman-tree/huffman-tree.h"

#define MAX_SIZE_INPUT 500

void cmd_Encrypt_Huffman(hfm_Tree *ht);
void cmd_Decrypt_Huffman(hfm_Tree *ht);
void cmd_Encrypt_Btree();
void cmd_Decrypt_Btree();
void cmd_Print_Huffman(hfm_Node *root, int space);
void cmd_Print_Btree(bt_Node *bn, int level);

#endif //HUFFMAN_CRYPTO_CMD_H
