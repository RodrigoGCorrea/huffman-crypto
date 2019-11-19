#include <stdlib.h>

#include "huffman-tree.h"

// PRIVATE
hfm_Tree* create_node(
        int prob,
        char symbol,
        hfm_Tree *left,
        hfm_Tree *right
) {
    hfm_Tree *hf = (hfm_Tree*) malloc(sizeof(hfm_Tree));
    hf->prob = prob;
    hf->symbol = symbol;
    hf->leaf = true;
    hf->l_a = -1;
    hf->r_a = -1;
    hf->right = right;
    hf->left = left;

    return hf;
}

// PUBLIC
hfm_Tree* hfm_Create() {
    return NULL;
}

hfm_Tree* hfm_Insert(hfm_Tree *hfmt, int prob, char symbol) {
    if (hfmt == NULL) {
        hfm_Tree *aux = create_node(prob, symbol, NULL, NULL);
        return aux;
    }

    int final_prob = prob + hfmt->prob;
    if (hfmt->leaf) {
        if (prob < hfmt->prob) {
            hfm_Tree *child = create_node(prob, symbol, NULL, NULL);

            hfm_Tree *parent = create_node(final_prob, '0', hfmt, child);
            parent->leaf = false;

            return parent;
        }

        if (prob >= hfmt->prob) {
            hfm_Tree *child = create_node(prob, symbol, NULL, NULL);

            hfm_Tree *parent = create_node(final_prob, '0', child, hfmt);
            parent->leaf = false;

            return parent;
        }
    }

    if (prob < hfmt->prob) {
        hfmt->prob = final_prob;
        hfmt->right = hfm_Insert(hfmt->right, prob, symbol);
    } else {
        hfmt->prob = final_prob;
        hfmt->left = hfm_Insert(hfmt->left, prob, symbol);
    }

    return hfmt;
}
