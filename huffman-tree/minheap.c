#include <stdlib.h>
#include <stdbool.h>

#include "minheap.h"

// PRIVATE
int get_parent(int i) {
    return (i-1)/2;
}

int get_left(int i) {
    return (2*i)+1;
}

int get_right(int i) {
    return (2*i)+2;
}

bool has_parent(int i) {
    if (get_parent(i) < 0) return false;
    else return true;
}

bool has_left(int i, int tail) {
    if (get_left(i) > tail) return false;
    else return true;
}

bool has_right(int i, int tail) {
    if (get_right(i) > tail) return false;
    else return true;
}

void heapify_up(hfm_Minheap *mh) {
    int i = mh->tail;

    while (has_parent(i) && mh->data[i].prob < mh->data[get_parent(i)].prob) {
        hfm_T_Minheap aux = mh->data[i];
        mh->data[i] = mh->data[get_parent(i)];
        mh->data[get_parent(i)] = aux;
        i = get_parent(i);
    }
}

void heapify_down(hfm_Minheap *mh) {
    int i = 0;
    int smaller;

    while (has_left(i, mh->tail)) {
        smaller = get_left(i);
        if (has_right(i, mh->tail) && mh->data[get_right(i)].prob < mh->data[get_left(i)].prob)
            smaller = get_right(i);

        if (mh->data[i].prob < mh->data[smaller].prob) return;
        else {
            hfm_T_Minheap aux = mh->data[i];
            mh->data[i] = mh->data[smaller];
            mh->data[smaller] = aux;
        }

        i = smaller;
    }
}

// PUBLIC
hfm_Minheap* hfm_Create_Minheap(int size) {
    hfm_Minheap *mh = (hfm_Minheap *) malloc(sizeof(hfm_Minheap));
    hfm_T_Minheap *data = (hfm_T_Minheap *) malloc(sizeof(hfm_T_Minheap) * size);
    mh->data = data;
    mh->size = size;
    mh->tail = -1;

    return mh;
}

void hfm_Insert_Minheap(hfm_Minheap *mh, hfm_T_Minheap data) {
    if (mh->tail == mh->size - 1) return;

    mh->tail += 1;
    mh->data[mh->tail] = data;

    heapify_up(mh);
}

hfm_T_Minheap hfm_Peek_Minheap(hfm_Minheap *mh) {
    if (mh->tail < 0) return HFM_T_ERROR;

    return mh->data[0];
}

hfm_T_Minheap hfm_Pop_Minheap(hfm_Minheap *mh) {
    if (mh->tail < 0) return HFM_T_ERROR;

    hfm_T_Minheap aux = mh->data[0];

    mh->data[0] = mh->data[mh->tail];
    mh->tail -= 1;

    heapify_down(mh);

    return aux;
}

hfm_Minheap* hfm_Increase_Size_Minheap(hfm_Minheap *mh, int to_inc) {
    hfm_Minheap *new = hfm_Create_Minheap(mh->size+to_inc);
    new->tail = mh->tail;

    for (int i = 0; i <= mh->tail; i++)
        new->data[i] = mh->data[i];

    hfm_Destroy_Minheap(mh);

    return new;
}

void hfm_Destroy_Minheap(hfm_Minheap *mh) {
    free(mh->data);
    free(mh);
}
