#ifndef HUFFMAN_CRYPTO_ENCRYPT_H
#define HUFFMAN_CRYPTO_ENCRYPT_H

#include "b-tree.h"

bt_Tree* bt_Gen_Tree_From_File(char *file, int t);
char* bt_Encode_String(bt_Tree *bt, char *msg);
char* bt_Decode_String(bt_Tree *bt, char *msg);
char* bt_Encode_Msg(bt_Tree *bt, char *msg);
char* bt_Decode_Msg(bt_Tree *bt, char *msg);

#endif //HUFFMAN_CRYPTO_ENCRYPT_H
