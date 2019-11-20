#ifndef HUFFMAN_CRYPTO_MINHEAP_H
#define HUFFMAN_CRYPTO_MINHEAP_H

#define HFM_T_ERROR NULL

#include <limits.h>
#include <stdbool.h>

#include "structs.h"

hfm_Minheap* hfm_Create_Minheap(int size);

void hfm_Insert_Minheap(hfm_Minheap *mh, hfm_T_Minheap *data);
hfm_T_Minheap* hfm_Peek_Minheap(hfm_Minheap *mh);
hfm_T_Minheap* hfm_Pop_Minheap(hfm_Minheap *mh);

hfm_Minheap* hfm_Increase_Size_Minheap(hfm_Minheap *mh, int to_inc);
bool hfm_Is_Full_Minheap(hfm_Minheap *mh);
bool hfm_Is_Empty_Minheap(hfm_Minheap *mh);

void hfm_Destroy_Minheap(hfm_Minheap *mh);

#endif //HUFFMAN_CRYPTO_MINHEAP_H
