#ifndef HUFFMAN_CRYPTO_MINHEAP_H
#define HUFFMAN_CRYPTO_MINHEAP_H

#include <limits.h>
#include <stdbool.h>

#include "../common/common.h"

typedef cmn_Rune hfm_T_Minheap;

typedef struct hfm_minheap {
    hfm_T_Minheap *data;
    int size;
    int tail;
} hfm_Minheap;

hfm_Minheap* hfm_Create_Minheap(int size);

void hfm_Insert_Minheap(hfm_Minheap *mh, hfm_T_Minheap data);
hfm_T_Minheap hfm_Peek_Minheap(hfm_Minheap *mh);
hfm_T_Minheap hfm_Pop_Minheap(hfm_Minheap *mh);

hfm_Minheap* hfm_Clone_Minheap(hfm_Minheap *mh);
hfm_Minheap* hfm_Increase_Size_Minheap(hfm_Minheap *mh, int to_inc);
bool hfm_Is_Full_Minheap(hfm_Minheap *mh);

void hfm_Destroy_Minheap(hfm_Minheap *mh);

#endif //HUFFMAN_CRYPTO_MINHEAP_H
