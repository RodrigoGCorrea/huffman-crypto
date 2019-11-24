#include <stdio.h>
#include <stdlib.h>

#include "encrypt.h"

// PRIVATE
//char* bt_encode_string_aux(bt_Node *bn, bt_T_Key key) {
//    if (bn == NULL)
//        return NULL;
//
//    int i = 0;
//    while (i < bn->nkey && key > bn->info[i].key)
//        i++;
//
//    if (i < bn->nkey && key == bn->info[i].key)
//        return bn;
//
//    if (bn->leaf)
//        return NULL;
//
//    return bt_search_node(bn->child[i], key);
//}

// PUBLIC
bt_Tree* bt_Gen_Tree_From_File(char *file, int t) {
    FILE *f = fopen(file, "r");
    if (!f) exit(1);

    bt_Tree *bt = bt_Create(t);

    char key[2], probs[10];
    float prob;

    while (!feof(f)){
        fscanf(f, "%s %s", key, probs);
        prob = strtof(probs, NULL);

        bt_T_Info to_insert = {key[0], prob};
        bt_Insert(bt, to_insert);
    }
    fclose(f);

    return bt;
}

char* bt_Encode_String(bt_Tree *bt, char *msg) {

}
