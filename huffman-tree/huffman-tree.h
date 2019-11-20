#ifndef HUFFMAN_CRYPTO_HUFFMAN_TREE_H
#define HUFFMAN_CRYPTO_HUFFMAN_TREE_H

#define HFM_POOL_SIZE 20
#define HFM_POOL_SIZE_INC 20

#include <stdbool.h>

#include "structs.h"

hfm_Tree* hfm_Create();

void hfm_Insert_Pool(hfm_Tree* ht, hfm_T_Minheap rune);
void hfm_Gen_Tree(hfm_Tree* ht);

void hfm_Destroy();

// TODO: LOW PRIORITY
void hfm_Insert_Pool_From_Array(hfm_Tree* ht, hfm_T_Minheap *arr_rune);

#endif //HUFFMAN_CRYPTO_HUFFMAN_TREE_H
