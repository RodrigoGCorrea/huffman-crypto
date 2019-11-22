#ifndef HUFFMAN_CRYPTO_HUFFMAN_TREE_H
#define HUFFMAN_CRYPTO_HUFFMAN_TREE_H

#define HFM_POOL_SIZE 20
#define HFM_POOL_SIZE_INC 20

#include <stdio.h>

#include "structs.h"
#include "minheap.h"

hfm_Tree* hfm_Create();

void hfm_Insert_Pool(hfm_Tree *ht, float prob, char symbol);
void hfm_Insert_Pool_From_File(hfm_Tree *ht, char *file);
void hfm_Gen_Tree(hfm_Tree *ht);

char* hfm_Encode_String(hfm_Tree *ht, char *msg);
char* hfm_Decode_String(hfm_Tree *ht, char *msg);

char* hfm_Encode_Msg(hfm_Tree *ht, char* msg);
char* hfm_Decode_Msg(hfm_Tree *ht, char *msg);

void hfm_Destroy(hfm_Tree *ht);

#endif //HUFFMAN_CRYPTO_HUFFMAN_TREE_H
