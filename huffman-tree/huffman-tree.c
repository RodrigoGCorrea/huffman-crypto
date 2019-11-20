#include <stdlib.h>

#include "huffman-tree.h"

// PRIVATE
hfm_Node* create_node(
        float prob,
        char symbol,
        hfm_Node *left,
        hfm_Node *right
) {
    hfm_Node *hn = (hfm_Node*) malloc(sizeof(hfm_Node));
    hn->prob = prob;
    hn->symbol = symbol;
    hn->left = left;
    hn->right = right;

    return hn;
}

hfm_Node* join_node(hfm_Node *hn1, hfm_Node *hn2) {
    hfm_Node *parent = NULL;

    if (hn1->prob < hn2->prob) {
        parent = create_node(hn1->prob + hn2->prob, '0', hn2, hn1);
    } else {
        parent = create_node(hn1->prob + hn2->prob, '0', hn1, hn2);
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

void hfm_Insert_Pool(hfm_Tree* ht, float prob, char symbol) {
    if (hfm_Is_Full_Minheap(ht->pool))
        ht->pool = hfm_Increase_Size_Minheap(ht->pool, HFM_POOL_SIZE_INC);

    hfm_Node *hn = create_node(prob, symbol, NULL, NULL);
    hfm_Insert_Minheap(ht->pool, hn);
}

void hfm_Gen_Tree(hfm_Tree* ht) {
    if (hfm_Is_Empty_Minheap(ht->pool)) return;
    destroy_tree(ht->head);

    hfm_Node *hn1, *hn2, *head;

    while (ht->pool->tail > 0) {
        hn1 = hfm_Pop_Minheap(ht->pool);
        hn2 = hfm_Pop_Minheap(ht->pool);

        head = join_node(hn1, hn2);

        hfm_Insert_Minheap(ht->pool, head);
    }

    ht->head = hfm_Pop_Minheap(ht->pool);
}

void hfm_Insert_Pool_From_File(hfm_Tree* ht, char *file){
    FILE *f = fopen(file, "r");
    if (!f) exit(1);
    char symbol[2], probs[10];
    float prob;
    while (!feof(f)){
        fscanf(f, "%s %s", symbol, probs);
        prob = strtof(probs, NULL);
        hfm_Insert_Pool(ht, prob, symbol[0]);
    }
    fclose(f);
}

void hfm_Destroy(hfm_Tree *ht) {
    destroy_tree(ht->head);
    hfm_Destroy_Minheap(ht->pool);
    free(ht);
}
