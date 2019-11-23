#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "huffman-tree/huffman-tree.h"
#include "b-tree/b-tree.h"

#define MAX_SIZE_INPUT 500


typedef struct options {
    bool b_tree;
    bool huffman;
} Options;

void cmd_encrypt_huffman(hfm_Tree *ht) {
    char input[MAX_SIZE_INPUT];

    printf("-> Digite sua mensagem:\n");
    fgets(input, MAX_SIZE_INPUT, stdin);

    int count = 0;
    while (input[count] != '\0') {
        if (input[count] == '\n')
            input[count] = '\0';
        count++;
    }

    char *cleaned_input = (char *) malloc(sizeof(char) * count);
    strncpy(cleaned_input, input, count);

    char *answer = hfm_Encode_Msg(ht, cleaned_input);
    printf("-> Mensagem encriptada:\n");
    printf("%s\n", answer);

    free(cleaned_input);
    free(answer);
}

void cmd_decrypt_huffman(hfm_Tree *ht) {
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

void cmd_encrypt_btree() {

}

void cmd_decrypt_btree() {

}

void cmd_print_huffman(hfm_Node *root, int space) {
    if (root == NULL)
        return;

    space += 10;

    cmd_print_huffman(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("[%f, %c]\n", root->prob, root->symbol);

    cmd_print_huffman(root->left, space);
}

void cmd_print_btree(bt_Node *a, int level){
    if(a){
        int i,j;
        for(i=0; i<=a->nkey-1; i++){
            cmd_print_btree(a->child[i], level + 1);
            for(j=0; j<=level; j++) printf("   ");
            printf("%d\n", a->key[i]);
        }
        cmd_print_btree(a->child[i], level + 1);
    }
}

void display_menu(char *sel_tree) {
    printf("-> Menu: \n");
    printf("-> 1. Mudar tipo de arvore (atual: %s)\n", sel_tree);
    printf("-> 2. Encriptar mensagem\n");
    printf("-> 3. Decriptar mensagem\n");
    printf("-> 4. Imprimir arvore atual\n");
    printf("-> 0. Sair\n");
}

void display_interface(){
    char cmd_in;
    int cmd = 0;

    char sel_tree[10] = "Huffman";

    hfm_Tree *ht = hfm_Create();
    hfm_Insert_Pool_From_File(ht, "../probs.txt");
    hfm_Gen_Tree(ht);

    Options opt = {false, true};

    while (cmd != -1) {
        display_menu(sel_tree);
        cmd_in = getchar(); // Actual cmd
        getchar();          // Skips \n
        cmd = (int) cmd_in - '0';

        if (cmd == 1) {
            opt.b_tree = !opt.b_tree;
            opt.huffman = !opt.huffman;

            if (opt.b_tree == true)
                strcpy(sel_tree, "Arvore B");

            if (opt.huffman == true)
                strcpy(sel_tree, "Huffman");

        } else if (cmd == 2) {
            if (opt.huffman == true)
                cmd_encrypt_huffman(ht);
            if (opt.b_tree == true)
                cmd_encrypt_btree();

        } else if (cmd == 3) {
            if (opt.huffman == true)
                cmd_decrypt_huffman(ht);
            if (opt.b_tree == true)
                cmd_decrypt_btree();

        } else if (cmd == 4) {
            if (opt.huffman == true)
                cmd_print_huffman(ht->head, 5);
            if (opt.b_tree == true)
                cmd_print_btree(NULL, 5);

        } else if (cmd == 0) {
            hfm_Destroy(ht);
            cmd = -1;

        } else {
            printf("Comando invalido\n");
        }

        printf("\n\n");
    }
}

int main() {
//    hfm_Tree *ht = hfm_Create();
//    hfm_Insert_Pool_From_File(ht, "../probs.txt");
//    hfm_Gen_Tree(ht);
//
//    cmd_encrypt_huffman(ht);
//    cmd_decrypt_huffman(ht);
//
//    hfm_Destroy(ht);

    display_interface();

    return 0;
}
