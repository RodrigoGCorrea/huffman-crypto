#include <stdlib.h>

#include "huffman-tree.h"

// PRIVATE
hfm_Node* create_node(
        hfm_T_Minheap rune,
        hfm_Node *left,
        hfm_Node *right
) {
    hfm_Node *hn = (hfm_Node*) malloc(sizeof(hfm_Node));
    hn->prob = rune.prob;
    hn->symbol = rune.symbol;
    hn->leaf = true;
    hn->left = NULL;
    hn->right = NULL;

    return hn;
}

hfm_Node* join_rune(hfm_T_Minheap r1, hfm_T_Minheap r2) {
    hfm_T_Minheap rune = {r1.prob + r2.prob, '0'};
    hfm_Node *parent = NULL, *hn1, *hn2;
    hn1 = create_node(r1, NULL, NULL);
    hn2 = create_node(r2, NULL, NULL);

    if (hn1->prob < hn2->prob) {
        parent = create_node(rune, hn1, hn2);
    } else {
        parent = create_node(rune, hn2, hn1);
    }

    return parent;
}

void destroy_tree(hfm_Node *hn) {
    if (hn != NULL) {
        destroy_tree(hn->left);
        destroy_tree(hn->right);
        free(hn);
    }
}

// PUBLIC
hfm_Tree* hfm_Create() {
    hfm_Tree *ht = (hfm_Tree *) malloc(sizeof(hfm_Tree));

    ht->head = NULL;
    ht->pool = hfm_Create_Minheap(HFM_POOL_SIZE);

    return ht;
}

void hfm_Insert_Pool(hfm_Tree* ht, hfm_T_Minheap rune) {
    if (hfm_Is_Full_Minheap(ht->pool))
        ht->pool = hfm_Increase_Size_Minheap(ht->pool, HFM_POOL_SIZE_INC);

    hfm_Insert_Minheap(ht->pool, rune);
}

void hfm_Gen_Tree(hfm_Tree* ht) {
    destroy_tree(ht->head);
    ht->head = NULL;
    hfm_Minheap *bck_pool = hfm_Clone_Minheap(ht->pool);

    hfm_T_Minheap r1, r2;
    r1 = hfm_Pop_Minheap(ht->pool);
    r2 = hfm_Pop_Minheap(ht->pool);

    hfm_Node *parent = join_rune(r1, r2);

    while (hfm_Is_Empty_Minheap(ht->pool) == false) {

    }
}

/*hfm_Tree* hfm_Insert(hfm_Tree *hfmt, int prob, char symbol) {
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
*/