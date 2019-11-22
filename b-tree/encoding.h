#ifndef HUFFMAN_CRYPTO_ENCODING_H
#define HUFFMAN_CRYPTO_ENCODING_H

#include "b-tree.h"

bt_Tree* bt_Gen_Key(char *msg);
char* bt_Encode_Msg(bt_Tree *key, char *msg);
char* bt_Decode_Msg(bt_Tree *key, char *msg);

#endif //HUFFMAN_CRYPTO_ENCODING_H
