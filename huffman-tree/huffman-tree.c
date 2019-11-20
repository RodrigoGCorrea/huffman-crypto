#include <stdlib.h>
#include <string.h>

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
        parent = create_node(hn1->prob + hn2->prob, '-', hn2, hn1);
    } else {
        parent = create_node(hn1->prob + hn2->prob, '-', hn1, hn2);
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

void create_code_table_aux(hfm_Node *hn, char **table, char *path) {
    if (!hn) return;
    if (hn->symbol != '-') {
        table[(hn->symbol - 'a')] = path;
    }
    char *path_left = (char*) malloc(sizeof(path) + sizeof(char));
    char *path_right = (char*) malloc(sizeof(path) + sizeof(char));
    strcpy(path_left, path);
    strcpy(path_right, path);
    strcat(path_left, "0");
    strcat(path_right, "1");
    create_code_table_aux(hn->left, table, path_left);
    create_code_table_aux(hn->right, table, path_right);

    if (hn->symbol == '-') {
        if (hn->left->symbol != '-')
            free(path_right);
        if (hn->right->symbol != '-')
            free(path_left);
    }
}

char** create_code_table(hfm_Node *hn, int table_size) {
    char **table = (char**) malloc(sizeof(char*) * table_size);
    create_code_table_aux(hn, table, "");
    return table;
}

void destroy_table(hfm_Tree *ht) {
    for (int i = 0; i < ht->table_size; i++){
        free(ht->table[i]);
    }
    free(ht->table);
}

// PUBLIC
hfm_Tree* hfm_Create() {
    hfm_Tree *ht = (hfm_Tree *) malloc(sizeof(hfm_Tree));

    ht->head = NULL;
    ht->pool = hfm_Create_Minheap(HFM_POOL_SIZE);
    ht->table = NULL;
    ht->table_size = 0;

    return ht;
}

void hfm_Insert_Pool(hfm_Tree* ht, float prob, char symbol) {
    if (hfm_Is_Full_Minheap(ht->pool))
        ht->pool = hfm_Increase_Size_Minheap(ht->pool, HFM_POOL_SIZE_INC);

    hfm_Node *hn = create_node(prob, symbol, NULL, NULL);
    hfm_Insert_Minheap(ht->pool, hn);
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

void hfm_Gen_Tree(hfm_Tree* ht, int table_size) {
    if (hfm_Is_Empty_Minheap(ht->pool)) return;
    ht->table_size = table_size;
    destroy_tree(ht->head);

    hfm_Node *hn1, *hn2, *head;

    while (ht->pool->tail > 0) {
        hn1 = hfm_Pop_Minheap(ht->pool);
        hn2 = hfm_Pop_Minheap(ht->pool);

        head = join_node(hn1, hn2);

        hfm_Insert_Minheap(ht->pool, head);
    }

    ht->head = hfm_Pop_Minheap(ht->pool);
    ht->table = create_code_table(ht->head, ht->table_size);
}



void hfm_Destroy(hfm_Tree *ht) {
    destroy_table(ht);
    destroy_tree(ht->head);
    hfm_Destroy_Minheap(ht->pool);
    free(ht);
}
