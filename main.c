#include <stdio.h>
#include <stdlib.h>

#include "huffman-tree/huffman-tree.h"

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


int main() {
    hfm_Tree *ht = hfm_Create();
    hfm_Insert_Pool_From_File(ht, "../probs.txt");
    hfm_Gen_Tree(ht);

    char *encoded = hfm_Encode_String(ht, "espaco");
    printf("%s\n", encoded);

    char *msg = hfm_Decode_String(ht, encoded);
    printf("%s\n", msg);

    free(msg);
    free(encoded);

    hfm_Destroy(ht);
    return 0;
}
