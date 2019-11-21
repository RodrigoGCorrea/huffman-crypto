#include <stdio.h>
#include <stdlib.h>

#include "b-tree.h"

// PRIVATE
bt_Node* create_node(int height){
    bt_Node* bn = (bt_Node*) malloc(sizeof(bt_Node));
    bn->nkey = 0;
    bn->key = (int *) malloc(sizeof(int*) * ((height*2)-1));
    bn->leaf = true;
    bn->child = (bt_Node **) malloc(sizeof(bt_Node*) * height * 2);

    for (int i= 0; i < (height * 2); i++)
        bn->child[i] = NULL;

    return bn;
}

void destroy_tree(bt_Node *bn){
    if (bn != NULL) {
        if (bn->child != NULL) {
            for (int i = 0; i <= bn->nkey; i++)
                destroy_tree(bn->child[i]);
        }

        free(bn->key);
        free(bn->child);
        free(bn);
    }
}

bt_Node* search_node(bt_Node* bn, int key){
    bt_Node *found = NULL;

    if (bn == NULL)
        return found;

    int i = 0;
    while (i < bn->nkey && key > bn->key[i])
        i++;

    if (i < bn->nkey && key == bn->key[i])
        return bn;

    if (bn->leaf)
        return found;

    return search_node(bn->child[i], key);
}

bt_Node* division_aux(bt_Node *bn1, int i, bt_Node* bn2, int height){
    bt_Node *aux = create_node(height);

    aux->nkey = height - 1;
    aux->leaf = bn2->leaf;

    for (int j = 0; j < height-1; j++)
        aux->key[j] = bn2->key[j+height];

    if (bn2->leaf == false){
        for(int j = 0; j < height; j++){
            aux->child[j] = bn2->child[j+height];
            bn2->child[j+height] = NULL;
        }
    }

    bn2->nkey = height-1;
    for(int j = bn1->nkey; j >= i; j--)
        bn1->child[j+1] = bn1->child[j];

    bn1->child[i] = aux;
    for(int j = bn1->nkey; j >= i; j--)
        bn1->key[j] = bn1->key[j-1];

    bn1->key[i-1] = bn2->key[height-1];
    bn1->nkey++;

    return bn1;
}

bt_Node *insert_node_incomplete(bt_Node *bn, int key, int height){
    int i = bn->nkey - 1;

    if (bn->leaf == true) {
        while ((i>=0) && (key < bn->key[i])) {
            bn->key[i+1] = bn->key[i];
            i--;
        }

        bn->key[i+1] = key;
        bn->nkey++;

        return bn;
    }

    while ((i>=0) && (key<bn->key[i]))
        i--;

    i++;
    if (bn->child[i]->nkey == ((2*height)-1)) {
        bn = division_aux(bn, (i+1), bn->child[i], height);
        if(key>bn->key[i]) i++;
    }

    bn->child[i] = insert_node_incomplete(bn->child[i], key, height);

    return bn;
}

bt_Node *insert_node(bt_Node *bn, int key, int height){
    if (search_node(bn, key))
        return bn;

    if (bn == NULL) {
        bn = create_node(height);
        bn->key[0] = key;
        bn->nkey = 1;

        return bn;
    }

    if (bn->nkey == (2*height)-1) {
        bt_Node *bn2 = create_node(height);
        bn2->nkey = 0;
        bn2->leaf = 0;
        bn2->child[0] = bn;

        bn2 = division_aux(bn2, 1, bn, height);
        bn2 = insert_node_incomplete(bn2, key, height);

        return bn2;
    }

    bn = insert_node_incomplete(bn, key, height);

    return bn;
}

bt_Node* remove_node_aux(bt_Node *bn, int key, int height){
    if (bn == NULL)
        return NULL;

    printf("Removendo %d...\n", key);

    int i;
    for(i = 0; i < bn->nkey && bn->key[i] < key; i++);

    //CASES: 1, 2A, 2B e 2C
    if (i < bn->nkey && key == bn->key[i]){

        // CASE 1
        if (bn->leaf == true){
            printf("\nCASO 1\n");

            for (int j = i; j < bn->nkey-1; j++)
                bn->key[j] = bn->key[j+1];

            bn->nkey--;

            return bn;
        }

        // CASE 2A
        if (bn->leaf == false && bn->child[i]->nkey >= height) {
            printf("\nCASO 2A\n");

            bt_Node *aux = bn->child[i];  //Encontrar o predecessor k' de k na árvore com raiz em aux

            while (aux->leaf == false)
                aux = aux->child[aux->nkey];

            //Eliminar recursivamente K e substitua K por K' em x
            int temp = aux->key[aux->nkey-1];
            bn->child[i] = remove_node_aux(bn->child[i], temp, height);
            bn->key[i] = temp;

            return bn;
        }

        // CASE 2B
        if (bn->leaf == false && bn->child[i+1]->nkey >= height) {
            printf("\nCASO 2B\n");

            bt_Node *aux = bn->child[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em aux

            while (aux->leaf == false)
                aux = aux->child[0];

            //Eliminar recursivamente K e substitua K por K' em x
            int temp = aux->key[0];
            aux = remove_node_aux(bn->child[i + 1], temp, height);
            bn->key[i] = temp;

            return bn;
        }

        // CASE 2C
        if (bn->leaf == false && bn->child[i+1]->nkey == height-1 && bn->child[i]->nkey == height-1) {
            printf("\nCASO 2C\n");

            bt_Node *aux1 = bn->child[i];
            bt_Node *aux2 = bn->child[i+1];

            aux1->key[aux1->nkey] = key;          //colocar key ao final de child[i]

            int j;
            for (j=0; j<height-1; j++)                //juntar key[i+1] com key[i]
                aux1->key[height+j] = aux2->key[j];

            for (j=0; j<=height; j++)                 //juntar child[i+1] com child[i]
                aux1->child[height+j] = aux2->child[j];

            aux1->nkey = 2*height-1;

            for (j=i; j < bn->nkey-1; j++)   //remove_node_aux key de bn
                bn->key[j] = bn->key[j+1];

            for (j=i+1; j <= bn->nkey; j++)  //remove_node_aux ponteiro para child[i+1]
                bn->child[j] = bn->child[j+1];

            bn->child[j] = NULL;
            bn->nkey--;
            bn->child[i] = remove_node_aux(bn->child[i], key, height);

            return bn;
        }
    }

    bt_Node *y = bn->child[i], *z = NULL;

    // CASES 3A, 3B
    if (y->nkey == height-1) {

        // CASE 3A
        if ((i < bn->nkey) && (bn->child[i+1]->nkey >= height)) {
            printf("\nCASO 3A: i menor que nkey\n");

            z = bn->child[i+1];
            y->key[height-1] = bn->key[i];   //dar a y a key i da bn
            y->nkey++;

            bn->key[i] = z->key[0];     //dar a bn uma key de z

            int j;
            for (j=0; j < z->nkey-1; j++)  //ajustar chaves de z
                z->key[j] = z->key[j+1];

            //z->key[j] = 0; Rosseti
            y->child[y->nkey] = z->child[0]; //enviar ponteiro menor de z para o novo elemento em y
            for (j=0; j < z->nkey; j++)       //ajustar filhos de z
                z->child[j] = z->child[j+1];

            z->nkey--;
            bn->child[i] = remove_node_aux(bn->child[i], key, height);

            return bn;
        }

        // CASE 3A
        if ((i > 0) && (!z) && (bn->child[i-1]->nkey >= height)) {
            printf("\nCASO 3A: i igual a nkey\n");

            z = bn->child[i-1];

            int j;
            for (j = y->nkey; j>0; j--)               //encaixar lugar da nova key
                y->key[j] = y->key[j-1];

            for (j = y->nkey+1; j>0; j--)             //encaixar lugar dos filhos da nova key
                y->child[j] = y->child[j-1];

            y->key[0] = bn->key[i-1];              //dar a y a key i da bn
            y->nkey++;

            bn->key[i-1] = z->key[z->nkey-1];   //dar a bn uma key de z

            y->child[0] = z->child[z->nkey];         //enviar ponteiro de z para o novo elemento em y
            z->nkey--;

            bn->child[i] = remove_node_aux(y, key, height);

            return bn;
        }

        // CASE 3B
        if (!z) {

            if (i < bn->nkey && bn->child[i+1]->nkey == height-1){
                printf("\nCASO 3B: i menor que nkey\n");

                z = bn->child[i+1];
                y->key[height-1] = bn->key[i];     //pegar key [i] e coloca ao final de child[i]
                y->nkey++;

                int j;
                for(j=0; j < height-1; j++){
                    y->key[height+j] = z->key[j];     //passar child[i+1] para child[i]
                    y->nkey++;
                }

                if(!y->leaf){
                    for(j=0; j<height; j++){
                        y->child[height+j] = z->child[j];
                    }
                }

                for(j=i; j < bn->nkey-1; j++){ //limpar referências de i
                    bn->key[j] = bn->key[j+1];
                    bn->child[j+1] = bn->child[j+2];
                }

                bn->nkey--;
                bn = remove_node_aux(bn, key, height);

                return bn;
            }

            if ((i > 0) && (bn->child[i-1]->nkey == height-1)){
                printf("\nCASO 3B: i igual a nkey\n");

                z = bn->child[i-1];

                if(i == bn->nkey)
                    z->key[height-1] = bn->key[i-1]; //pegar key[i] e poe ao final de child[i-1]
                else
                    z->key[height-1] = bn->key[i];   //pegar key [i] e poe ao final de child[i-1]

                z->nkey++;
                int j;
                for(j=0; j < height-1; j++){
                    z->key[height+j] = y->key[j];     //passar child[i+1] para child[i]
                    z->nkey++;
                }

                if(!z->leaf){
                    for(j=0; j<height; j++){
                        z->child[height+j] = y->child[j];
                    }
                }

                bn->nkey--;
                bn->child[i-1] = z;
                bn = remove_node_aux(bn, key, height);

                return bn;
            }
        }
    }

    bn->child[i] = remove_node_aux(bn->child[i], key, height);

    return bn;
}

bt_Node* remove_node(bt_Node* bn, int key, int height){
    if (bn == NULL || search_node(bn, key) == NULL)
        return bn;

    return remove_node_aux(bn, key, height);
}

// PUBLIC
bt_Tree* bt_Create(int height) {
    bt_Tree *bt = (bt_Tree *) malloc(sizeof(bt_Tree));
    bt->head = NULL;
    bt->height = height;

    return bt;
}

void bt_Insert(bt_Tree *bt, int key) {
    bt->head = insert_node(bt->head, key, bt->height);
}

void bt_Remove(bt_Tree *bt, int key) {
    bt->head = remove_node(bt->head, key, bt->height);
}

bt_Node* bt_Search(bt_Tree *bt, int key) {
    return search_node(bt->head, key);
}

void bt_Destroy(bt_Tree* bt) {
    destroy_tree(bt->head);
    free(bt);
}

