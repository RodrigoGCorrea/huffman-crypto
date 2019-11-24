#include <stdlib.h>

#include "b-tree.h"

// PRIVATE
bt_Node* bt_create_node(int t) {
    bt_Node* bn = (bt_Node *) malloc(sizeof(bt_Node));
    bn->nkey = 0;
    bn->leaf = true;

    bn->info = (bt_T_Info *) malloc(sizeof(bt_T_Info) * ((t * 2) - 1));

    bn->child = (bt_Node **) malloc(sizeof(bt_Node*) * t * 2);

    for (int i= 0; i < (t * 2); i++)
        bn->child[i] = NULL;

    return bn;
}

void bt_destroy_node(bt_Node *bn) {
    if (bn != NULL) {
        if (bn->child != NULL) {
            for (int i = 0; i <= bn->nkey; i++)
                bt_destroy_node(bn->child[i]);
        }

        free(bn->info);
        free(bn->child);
        free(bn);
    }
}

bt_Node* bt_search_node(bt_Node *bn, bt_T_Key key) {
    if (bn == NULL)
        return NULL;

    int i = 0;
    while (i < bn->nkey && key > bn->info[i].key)
        i++;

    if (i < bn->nkey && key == bn->info[i].key)
        return bn;

    if (bn->leaf == true)
        return NULL;

    return bt_search_node(bn->child[i], key);
}

bt_Node* bt_split_node(bt_Node *parent, int i, bt_Node *c_complete, int t) {
    bt_Node *c_new = bt_create_node(t);

    c_new->nkey = t - 1;
    c_new->leaf = c_complete->leaf;

    for (int j = 0; j < t-1; j++)
        c_new->info[j] = c_complete->info[j + t];

    if (c_complete->leaf == false){
        for(int j = 0; j < t; j++){
            c_new->child[j] = c_complete->child[j + t];
            c_complete->child[j + t] = NULL;
        }
    }

    c_complete->nkey = t - 1;

    for(int j = parent->nkey; j >= i; j--)
        parent->child[j + 1] = parent->child[j];
    parent->child[i] = c_new;

    for(int j = parent->nkey; j >= i; j--)
        parent->info[j] = parent->info[j - 1];
    parent->info[i - 1] = c_complete->info[t - 1];

    parent->nkey++;

    return parent;
}

bt_Node* bt_insert_node_incomplete(bt_Node *bn, bt_T_Info info, int t) {
    int i = bn->nkey - 1;

    if (bn->leaf == true) {
        while ((i >= 0) && (info.key < bn->info[i].key)) {
            bn->info[i+1] = bn->info[i];
            i--;
        }

        bn->info[i+1] = info;
        bn->nkey++;

        return bn;
    }

    while ((i >= 0) && (info.key < bn->info[i].key))
        i--;

    i++;
    if (bn->child[i]->nkey == ((2 * t) - 1)) {
        bn = bt_split_node(bn, (i + 1), bn->child[i], t);
        if (info.key > bn->info[i].key) i++;
    }

    bn->child[i] = bt_insert_node_incomplete(bn->child[i], info, t);

    return bn;
}

bt_Node* bt_insert_node(bt_Node *bn, bt_T_Info info, int t) {
    if (bt_search_node(bn, info.key))
        return bn;

    if (bn == NULL) {
        bn = bt_create_node(t);
        bn->info[0] = info;
        bn->nkey = 1;

        return bn;
    }

    if (bn->nkey == (2*t)-1) {
        bt_Node *bn2 = bt_create_node(t);
        bn2->nkey = 0;
        bn2->leaf = false;
        bn2->child[0] = bn;

        bn2 = bt_split_node(bn2, 1, bn, t);
        bn2 = bt_insert_node_incomplete(bn2, info, t);

        return bn2;
    }

    bn = bt_insert_node_incomplete(bn, info, t);

    return bn;
}

bt_Node* bt_remove_node_aux(bt_Node *bn, bt_T_Key key, int t) {
    if (bn == NULL)
        return NULL;

    int i;
    for(i = 0; i < bn->nkey && bn->info[i].key < key; i++);

    //CASES: 1, 2A, 2B e 2C
    if (i < bn->nkey && key == bn->info[i].key){

        // CASE 1
        if (bn->leaf == true){
            for (int j = i; j < bn->nkey-1; j++)
                bn->info[j] = bn->info[j+1];

            bn->nkey--;

            return bn;
        }

        // CASE 2A
        if (bn->leaf == false && bn->child[i]->nkey >= t) {
            bt_Node *aux = bn->child[i];  //Encontrar o predecessor k' de k na árvore com raiz em aux

            while (aux->leaf == false)
                aux = aux->child[aux->nkey];

            //Eliminar recursivamente K e substitua K por K' em x
            bt_T_Info temp = aux->info[aux->nkey-1];
            bn->child[i] = bt_remove_node_aux(bn->child[i], temp.key, t);
            bn->info[i] = temp;

            return bn;
        }

        // CASE 2B
        if (bn->leaf == false && bn->child[i+1]->nkey >= t) {
            bt_Node *aux = bn->child[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em aux

            while (aux->leaf == false)
                aux = aux->child[0];

            //Eliminar recursivamente K e substitua K por K' em x
            bt_T_Info temp = aux->info[0];
            aux = bt_remove_node_aux(bn->child[i + 1], temp.key, t);
            bn->info[i] = temp;

            return bn;
        }

        // CASE 2C
        if (bn->leaf == false && bn->child[i+1]->nkey == t-1 && bn->child[i]->nkey == t-1) {
            bt_Node *aux1 = bn->child[i];
            bt_Node *aux2 = bn->child[i+1];

            aux1->info[aux1->nkey] = bn->info[i];  //colocar info ao final de child[i]

            int j;
            for (j=0; j<t-1; j++)                  //juntar info[i+1] com info[i]
                aux1->info[t+j] = aux2->info[j];

            for (j=0; j<=t; j++)                   //juntar child[i+1] com child[i]
                aux1->child[t+j] = aux2->child[j];

            aux1->nkey = 2*t-1;

            for (j=i; j < bn->nkey-1; j++)   //bt_remove_node_aux info de bn
                bn->info[j] = bn->info[j+1];

            for (j=i+1; j <= bn->nkey; j++)  //bt_remove_node_aux ponteiro para child[i+1]
                bn->child[j] = bn->child[j+1];

            bn->child[j] = NULL;
            bn->nkey--;
            bn->child[i] = bt_remove_node_aux(bn->child[i], key, t);

            return bn;
        }
    }

    bt_Node *y = bn->child[i], *z = NULL;

    // CASES 3A, 3B
    if (y->nkey == t-1) {

        // CASE 3A
        if ((i < bn->nkey) && (bn->child[i+1]->nkey >= t)) {
            z = bn->child[i+1];
            y->info[t-1] = bn->info[i];   //dar a y a info i da bn
            y->nkey++;

            bn->info[i] = z->info[0];     //dar a bn uma info de z

            int j;
            for (j=0; j < z->nkey-1; j++)  //ajustar chaves de z
                z->info[j] = z->info[j+1];

            //z->info[j] = 0; Rosseti
            y->child[y->nkey] = z->child[0]; //enviar ponteiro menor de z para o novo elemento em y
            for (j=0; j < z->nkey; j++)       //ajustar filhos de z
                z->child[j] = z->child[j+1];

            z->nkey--;
            bn->child[i] = bt_remove_node_aux(bn->child[i], key, t);

            return bn;
        }

        // CASE 3A
        if ((i > 0) && (!z) && (bn->child[i-1]->nkey >= t)) {
            z = bn->child[i-1];

            int j;
            for (j = y->nkey; j>0; j--)               //encaixar lugar da nova info
                y->info[j] = y->info[j-1];

            for (j = y->nkey+1; j>0; j--)             //encaixar lugar dos filhos da nova info
                y->child[j] = y->child[j-1];

            y->info[0] = bn->info[i-1];              //dar a y a info i da bn
            y->nkey++;

            bn->info[i-1] = z->info[z->nkey-1];   //dar a bn uma info de z

            y->child[0] = z->child[z->nkey];         //enviar ponteiro de z para o novo elemento em y
            z->nkey--;

            bn->child[i] = bt_remove_node_aux(y, key, t);

            return bn;
        }

        // CASE 3B
        if (!z) {
            if (i < bn->nkey && bn->child[i+1]->nkey == t-1){
                z = bn->child[i+1];
                y->info[t-1] = bn->info[i];     //pegar info [i] e coloca ao final de child[i]
                y->nkey++;

                int j;
                for(j=0; j < t-1; j++){
                    y->info[t+j] = z->info[j];     //passar child[i+1] para child[i]
                    y->nkey++;
                }

                if(!y->leaf){
                    for(j=0; j<t; j++){
                        y->child[t+j] = z->child[j];
                    }
                }

                for(j=i; j < bn->nkey-1; j++){ //limpar referências de i
                    bn->info[j] = bn->info[j+1];
                    bn->child[j+1] = bn->child[j+2];
                }

                bn->nkey--;
                bn = bt_remove_node_aux(bn, key, t);

                return bn;
            }

            if ((i > 0) && (bn->child[i-1]->nkey == t-1)){
                z = bn->child[i-1];

                if(i == bn->nkey)
                    z->info[t-1] = bn->info[i-1]; //pegar info[i] e poe ao final de child[i-1]
                else
                    z->info[t-1] = bn->info[i];   //pegar info [i] e poe ao final de child[i-1]

                z->nkey++;
                int j;
                for(j=0; j < t-1; j++){
                    z->info[t+j] = y->info[j];     //passar child[i+1] para child[i]
                    z->nkey++;
                }

                if(!z->leaf){
                    for(j=0; j<t; j++){
                        z->child[t+j] = y->child[j];
                    }
                }

                bn->nkey--;
                bn->child[i-1] = z;
                bn = bt_remove_node_aux(bn, key, t);

                return bn;
            }
        }
    }

    bn->child[i] = bt_remove_node_aux(bn->child[i], key, t);

    return bn;
}

bt_Node* bt_remove_node(bt_Node *bn, bt_T_Key key, int t) {
    if (bn == NULL || bt_search_node(bn, key) == NULL)
        return bn;

    return bt_remove_node_aux(bn, key, t);
}

// PUBLIC
bt_Tree* bt_Create(int t) {
    bt_Tree *bt = (bt_Tree *) malloc(sizeof(bt_Tree));
    bt->head = NULL;
    bt->t = t;

    return bt;
}

void bt_Insert(bt_Tree *bt, bt_T_Info info) {
    bt->head = bt_insert_node(bt->head, info, bt->t);
}

void bt_Remove(bt_Tree *bt, bt_T_Key key) {
    bt->head = bt_remove_node(bt->head, key, bt->t);
}

bt_Node* bt_Search(bt_Tree *bt, bt_T_Key key) {
    return bt_search_node(bt->head, key);
}

void bt_Destroy(bt_Tree* bt) {
    bt_destroy_node(bt->head);
    free(bt);
}

