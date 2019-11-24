#include <stdio.h>
#include <stdlib.h>

#include "encrypt.h"

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
