#include <stdio.h>

#include "huffman-tree/huffman-tree.h"

void imprime_aux(hfm_Node* a, int andar){
    if(a){
        int j;
        imprime_aux(a->left, andar + 1);
        for(j = 0; j <= andar; j++) printf("   ");
        printf("[%i, %c]\n", a->prob, a->symbol);
        imprime_aux(a->right, andar + 1);
    }
}

void imprime_ab(hfm_Node* a){
    imprime_aux(a, 1);
}

int main() {
    hfm_

    return 0;
}
