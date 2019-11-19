#include <stdio.h>

#include "huffman-tree/minheap.h"

void pp(hfm_Minheap *mh) {
    for (int i = 0; i <= mh->tail; i++) {
        printf("%i:[%i] - ", i, mh->data[i]);
    }
    printf(" t: %i\n", mh->tail);
}

int main() {
    hfm_Minheap *mh = hfm_Create_Minheap(10);

    hfm_Insert_Minheap(mh, 10);
    hfm_Insert_Minheap(mh, 8);
    hfm_Insert_Minheap(mh, 12);
    hfm_Insert_Minheap(mh, 1);
    hfm_Insert_Minheap(mh, 9);
    hfm_Insert_Minheap(mh, 99);

    pp(mh);

    hfm_Pop_Minheap(mh);

    pp(mh);

    hfm_Insert_Minheap(mh, 88);

    pp(mh);

    hfm_Insert_Minheap(mh, -1);

    pp(mh);

    hfm_Destroy_Minheap(mh);
    return 0;
}
