#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encrypt.h"
#include "list.h"

// PRIVATE
char* bt_encode_string_aux(bt_Node *bn, bt_T_Key key, char *path, bt_List **pt_trash) {
    if (bn == NULL)
        return NULL;

    int i = 0;
    while (i < bn->nkey && key > bn->info[i].key)
        i++;

    char *number = (char *) malloc(sizeof(char) + 1);
    sprintf(number, "%i", i);

    char *new_path = (char *) malloc(strlen(path) + 2);
    strcpy(new_path, path);
    strcat(new_path, number);
    free(number);

    *pt_trash = bt_Append_List(*pt_trash, new_path);

    if (i < bn->nkey && key == bn->info[i].key)
        return new_path;

    if (bn->leaf)
        return NULL;

    return bt_encode_string_aux(bn->child[i], key, new_path, pt_trash);
}

// PUBLIC
bt_Tree* bt_Gen_Tree_From_File(char *file, int t) {
    FILE *f = fopen(file, "r");
    if (!f) exit(1);

    bt_Tree *bt = bt_Create(t);

    char key[2], probs[10];
    float prob;

    while (!feof(f)) {
        fscanf(f, "%s %s", key, probs);
        prob = strtof(probs, NULL);

        bt_T_Info to_insert = {key[0], prob};
        bt_Insert(bt, to_insert);
    }
    fclose(f);

    return bt;
}

char* bt_Encode_String(bt_Tree *bt, char *msg) {
    if (!msg) return NULL;
    if (!bt) return NULL;

    bt_List *pointers_trash = bt_Create_List();

    int size = 0;
    for (int i = 0; i < strlen(msg); i++) {
        pointers_trash = NULL;

        char *aux = bt_encode_string_aux(bt->head, msg[i], "", &pointers_trash);

        size += strlen(aux);

        bt_Destroy_List(pointers_trash);
    }

    char *encoded = (char*) malloc(sizeof(char) * size + strlen(msg) + 1);
    strcpy(encoded, "");
    for (int i = 0; i < strlen(msg); i++) {
        pointers_trash = NULL;
        char *aux = bt_encode_string_aux(bt->head, msg[i], "", &pointers_trash);

        char *level = (char*) malloc(sizeof(char) + 1);

        sprintf(level, "%i", (int) strlen(aux) - 1);
        strcat(encoded, level);
        strcat(encoded, aux);

        free(level);

        bt_Destroy_List(pointers_trash);
    }

    return encoded;
}

char* bt_Decode_String(bt_Tree *bt, char*msg) {
    int j = 0, size = 0;
    while (j < strlen(msg)) {
        j += msg[j] - '0' + 2;
        size++;
    }

    char *decoded = (char*) malloc(sizeof(char) * size + 1);
    strcpy(decoded, "");
    j = 0;
    while (j < strlen(msg)) {
        bt_Node *aux = bt->head;
        char *decoded_char = (char*) malloc(sizeof(char) + 1);
        int i;
        for (i = j + 1; i < j + msg[j] - '0' + 1; i++) {
            aux = aux->child[msg[i] - '0'];
        }
        decoded_char[0] = aux->info[msg[i] - '0'].key;
        decoded_char[1] = '\0';
        strcat(decoded, decoded_char);
        j += msg[j] - '0' + 2;
        free(decoded_char);
    }

    return decoded;
}
