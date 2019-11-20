#include <stdio.h>
#include <stdlib.h>

#include "huffman-tree/huffman-tree.h"

void print2DUtil(hfm_Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 5;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("[%i, %c]\n", root->prob, root->symbol);

    // Process left child
    print2DUtil(root->left, space);
}


int main() {
    hfm_Tree *ht = hfm_Create();

    hfm_Insert_Pool(ht, 19, 'a');
    hfm_Insert_Pool(ht, 1, 'b');
    hfm_Insert_Pool(ht, 2, 'c');
    hfm_Insert_Pool(ht, 8, 'd');
    hfm_Insert_Pool(ht, 99, 'e');
    hfm_Insert_Pool(ht, 7, 'f');

    hfm_Gen_Tree(ht);

    print2DUtil(ht->head, 1);

    hfm_Destroy(ht);

    return 0;
}
