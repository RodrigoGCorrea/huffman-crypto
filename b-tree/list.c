#include <stdlib.h>

#include "list.h"

// PUBLIC
bt_List* bt_Create_List() {
    return NULL;
}

bt_List* bt_Append_List(bt_List *btl, char *info) {
    bt_List *aux = (bt_List *) malloc(sizeof(bt_List));
    aux->info = info;
    aux->next = NULL;

    if (btl == NULL) {
        return aux;
    }

    bt_List *p = btl;
    while (btl->next != NULL)
         p = p->next;

    p->next = aux;

    return btl;
}

void bt_Destroy_List(bt_List *btl) {
    if (btl == NULL) return;

    bt_List *aux = btl;
    while (btl->next != NULL) {
        btl = btl->next;
        free(aux->info);
        free(aux);
        aux = btl->next;
    }
}
