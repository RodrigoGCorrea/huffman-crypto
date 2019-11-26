#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cmd.h"

void cmd_Encrypt_Huffman(hfm_Tree *ht) {
    char input[MAX_SIZE_INPUT];

    printf("-> Digite sua mensagem:\n");
    fgets(input, MAX_SIZE_INPUT, stdin);

    // Clean input
    int count = 0;
    while (input[count] != '\0') {
        if (input[count] == '\n')
            input[count] = '\0';
        count++;
    }

    char *cleaned_input = (char *) malloc(sizeof(char) * count);
    strncpy(cleaned_input, input, count);

    // To lower case
    for (int i = 0; i < strlen(cleaned_input); i++)
        cleaned_input[i] = tolower(cleaned_input[i]);

    // Encode input
    char *answer = hfm_Encode_Msg(ht, cleaned_input);
    printf("-> Mensagem encriptada:\n");
    printf("%s\n", answer);

    free(cleaned_input);
    free(answer);
}

void cmd_Decrypt_Huffman(hfm_Tree *ht) {
    char input[MAX_SIZE_INPUT];

    printf("-> Digite sua mensagem encriptada:\n");
    fgets(input, MAX_SIZE_INPUT, stdin);

    int count = 0;
    while (input[count] != '\0') {
        if (input[count] == '\n')
            input[count] = '\0';
        count++;
    }

    char *cleaned_input = (char *) malloc(sizeof(char) * count);
    strncpy(cleaned_input, input, count);

    char *answer = hfm_Decode_Msg(ht, cleaned_input);
    printf("-> Mensagem decriptada:\n");
    printf("%s\n", answer);

    free(cleaned_input);
    free(answer);
}

void cmd_Encrypt_Btree() {
    char input[MAX_SIZE_INPUT];

    int t = 0;
    printf("-> Digite a ordem da arvore:\n");
    scanf("%i", &t);
    getchar();

    bt_Tree *bt = bt_Gen_Tree_From_File("../probs_btree.txt", t);

    printf("-> Digite sua mensagem:\n");
    fgets(input, MAX_SIZE_INPUT, stdin);

    // Clean input
    int count = 0;
    while (input[count] != '\0') {
        if (input[count] == '\n')
            input[count] = '\0';
        count++;
    }

    char *cleaned_input = (char *) malloc(sizeof(char) * count);
    strncpy(cleaned_input, input, count);

    // To lower case
    for (int i = 0; i < strlen(cleaned_input); i++)
        cleaned_input[i] = tolower(cleaned_input[i]);

    // Encode input
    char *answer = bt_Encode_Msg(bt, cleaned_input);
    printf("-> Mensagem encriptada:\n");
    printf("%s\n", answer);

    bt_Destroy(bt);
    free(cleaned_input);
    free(answer);
}

void cmd_Decrypt_Btree() {
    char input[MAX_SIZE_INPUT];

    int t = 0;
    printf("-> Digite a ordem da arvore:\n");
    scanf("%i", &t);
    getchar();

    bt_Tree *bt = bt_Gen_Tree_From_File("../probs_btree.txt", t);

    printf("-> Digite sua mensagem encriptada:\n");
    fgets(input, MAX_SIZE_INPUT, stdin);

    int count = 0;
    while (input[count] != '\0') {
        if (input[count] == '\n')
            input[count] = '\0';
        count++;
    }

    char *cleaned_input = (char *) malloc(sizeof(char) * count);
    strncpy(cleaned_input, input, count);

    char *answer = bt_Decode_Msg(bt, cleaned_input);
    printf("-> Mensagem decriptada:\n");
    printf("%s\n", answer);

    bt_Destroy(bt);
    free(cleaned_input);
    free(answer);

}

void cmd_Print_Huffman(hfm_Node *root, int space) {
    if (root == NULL)
        return;

    space += 10;

    cmd_Print_Huffman(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("[%f, %c]\n", root->prob, root->symbol);

    cmd_Print_Huffman(root->left, space);
}

void cmd_Print_Btree(bt_Node *bn, int level) {
    if(bn != NULL) {
        int i;

        for (i = 0; i <= bn->nkey - 1; i++) {
            cmd_Print_Btree(bn->child[i], level + 1);

            for (int j = 0; j <= level; j++)
                printf("   ");

            printf("[%c, %.2f]\n", bn->info[i].key, bn->info[i].prob);
        }

        cmd_Print_Btree(bn->child[i], level + 1);
    }
}