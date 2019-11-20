#include <stdio.h>

#include "huffman-tree/minheap.h"

void pp(hfm_Minheap *mh) {
    for (int i = 0; i <= mh->tail; i++) {
        printf("%i:[%i, %c] - ", i, mh->data[i].prob, mh->data[i].symbol);
    }
    printf(" t: %i\n", mh->tail);
}

int main() {
    hfm_Minheap *mh = hfm_Create_Minheap(2);
    hfm_T_Minheap in = {100, 'a'};

    hfm_Insert_Minheap(mh, in);

    in.prob = 8;
    hfm_Insert_Minheap(mh, in);

    in.prob = 12;
    hfm_Insert_Minheap(mh, in);

    in.prob = 1;
    hfm_Insert_Minheap(mh, in);

    in.prob = 9;
    hfm_Insert_Minheap(mh, in);

    in.prob = 99;
    hfm_Insert_Minheap(mh, in);

    pp(mh);

    hfm_Pop_Minheap(mh);

    pp(mh);

    in.prob = 88;
    hfm_Insert_Minheap(mh, in);

    pp(mh);

    in.prob = -1;
    hfm_Insert_Minheap(mh, in);

    pp(mh);

    in.prob = -10;
    hfm_Insert_Minheap(mh, in);

    pp(mh);

    printf("Full? %i\n", hfm_Is_Full_Minheap(mh));

    in.prob = -10;
    hfm_Insert_Minheap(mh, in);

    pp(mh);

    printf("Full? %i\n", hfm_Is_Full_Minheap(mh));

    hfm_Pop_Minheap(mh);
    hfm_Pop_Minheap(mh);


    printf("Empty? %i\n", hfm_Is_Empty_Minheap(mh));


    hfm_Destroy_Minheap(mh);
    return 0;
}
