#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils/cmd.h"
#include "huffman-tree/huffman-tree.h"
#include "b-tree/encrypt.h"

typedef struct options {
    bool b_tree;
    bool huffman;
} Options;

void display_menu_huffman(char *sel_tree) {
    printf("-> Menu: \n");
    printf("-> 1. Mudar tipo de arvore (atual: %s)\n", sel_tree);
    printf("-> 2. Encriptar mensagem\n");
    printf("-> 3. Decriptar mensagem\n");
    printf("-> 4. Imprimir arvore atual\n");
    printf("-> 0. Sair\n");
}

void display_menu_btree(char *sel_tree) {
    printf("-> Menu: \n");
    printf("-> 1. Mudar tipo de arvore (atual: %s)\n", sel_tree);
    printf("-> 2. Encriptar mensagem\n");
    printf("-> 3. Decriptar mensagem\n");
    printf("-> 4. Imprimir arvore atual\n");
    printf("-> 5. Imprimir vogais\n");
    printf("-> 6. Imprimir consoantes\n");
    printf("-> 7. Imprimir subordinados\n");
    printf("-> 0. Sair\n");
}

void display_interface(){
    char cmd_in;
    int cmd = 0;

    char sel_tree[10] = "Huffman";

    hfm_Tree *ht = hfm_Create();
    hfm_Insert_Pool_From_File(ht, "../probs_hfm.txt");
    hfm_Gen_Tree(ht);

    Options opt = {false, true};

    while (cmd != -1) {
        if (opt.huffman == true)
            display_menu_huffman(sel_tree);
        if (opt.b_tree == true)
            display_menu_btree(sel_tree);

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
                cmd_Encrypt_Huffman(ht);
            if (opt.b_tree == true)
                cmd_Encrypt_Btree();

        } else if (cmd == 3) {
            if (opt.huffman == true)
                cmd_Decrypt_Huffman(ht);
            if (opt.b_tree == true)
                cmd_Decrypt_Btree();

        } else if (cmd == 4) {
            if (opt.huffman == true)
                cmd_Print_Huffman(ht->head, 5);
            if (opt.b_tree == true) {
                int t = 0;
                printf("-> Digite a ordem da arvore:\n");
                scanf("%i", &t);

                bt_Tree *bt = bt_Gen_Tree_From_File("../probs_btree.txt", t);

                cmd_Print_Btree(bt->head, 5);

                bt_Destroy(bt);
            }
        } else if (opt.b_tree == true && cmd == 5) {

        } else if (opt.b_tree == true && cmd == 6) {

        } else if (opt.b_tree == true && cmd == 7) {

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
    display_interface();

    return 0;
}
