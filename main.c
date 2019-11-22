#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "huffman-tree/huffman-tree.h"
#include "b-tree/b-tree.h"

void print2DUtil(hfm_Node *root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("[%f, %c]\n", root->prob, root->symbol);

    // Process left child
    print2DUtil(root->left, space);
}

void Imprime(bt_Node *a, int andar){
    if(a){
        int i,j;
        for(i=0; i<=a->nkey-1; i++){
            Imprime(a->child[i],andar+1);
            for(j=0; j<=andar; j++) printf("   ");
            printf("%d\n", a->key[i]);
        }
        Imprime(a->child[i],andar+1);
    }
}

typedef struct options {
    bool b_tree;
    bool huffman;
} Options;

void display_menu(char *sel_tree) {
    printf("Menu: \n");
    printf("1. Mudar tipo de arvore (atual: %s)\n", sel_tree);
    printf("2. Encriptar mensagem\n");
    printf("3. Decriptar mensagem\n");
}

void interfacezada(){
    int cmd = INT_MAX;
    char sel_tree[40] = "Huffman";
    char input[500];

    hfm_Tree *ht = hfm_Create();
    hfm_Insert_Pool_From_File(ht, "../probs.txt");
    hfm_Gen_Tree(ht);

    Options opt = {false, true};

    while (cmd != -1) {
        display_menu(sel_tree);
        scanf("%i", &cmd);
        getchar();

        if (cmd == 1) {
            opt.b_tree = !opt.b_tree;
            opt.huffman = !opt.huffman;

            if (opt.b_tree == true)
                strcpy(sel_tree, "Arvore B");

            if (opt.huffman == true)
                strcpy(sel_tree, "Huffman");

        } else if (cmd == 2) {

            printf("Digite sua mensagem:\n");
            fgets(input, sizeof(input), stdin);

            int count = 0;
            while (input[count] != '\0') count++;

            char *dale = (char*) malloc(sizeof(char) * (count - 1));
            strncpy(dale, input, (count - 1));
            printf("%s\n", dale);

            char* ans = hfm_Encode_Msg(ht, dale);
            printf("Mensagem encriptado: ");
            printf("%s\n", ans);

            free(input);
            free(dale);

        } else if (cmd == 3) {

        } else {
            printf("Comando invalido\n");
        }
        printf("\n\n");
    }
}

int main() {
//
//    char *encoded = hfm_Encode_String(ht, "espaco");
//    printf("%s\n", encoded);
//
//    char *msg = hfm_Decode_String(ht, encoded);
//    printf("%s\n", msg);
//
//    free(msg);
//    free(encoded);
//
//    hfm_Destroy(ht);
//
    interfacezada();

    return 0;
}
