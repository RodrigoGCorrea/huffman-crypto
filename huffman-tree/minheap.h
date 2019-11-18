#ifndef HUFFMAN_CRYPTO_MINHEAP_H
#define HUFFMAN_CRYPTO_MINHEAP_H

#include <limits.h>

#define HFM_T_MIN INT_MIN


typedef int hfm_T_Minheap;

typedef struct hfm_minheap {
    hfm_T_Minheap *data;
    int size;
    int tail;
} hfm_Minheap;

hfm_Minheap* hfm_Create_Minheap(int size);
void hfm_Insert_Minheap(hfm_Minheap *mh, hfm_T_Minheap data);
hfm_T_Minheap hfm_Peek_Minheap(hfm_Minheap *mh);
hfm_T_Minheap hfm_Pop_Minheap(hfm_Minheap *mh);

void hfm_Destroy_Minheap(hfm_Minheap *mh);

#endif //HUFFMAN_CRYPTO_MINHEAP_H
