#include "../inc/header.h"

////////////////////////////////////////////////////////////////////////////////$
is_list *Create_island_list(char *name_island, int index) {
    is_list *tmp = (is_list*)malloc(sizeof(is_list));
    tmp->name_island = name_island;
    tmp->index = index;
    tmp->next = NULL;
    return(tmp);
}

void Add_elem_end_island_list(char *name_island, int index, is_list *head) {
    is_list *tmp = (is_list*)malloc(sizeof(is_list));
    tmp->name_island = name_island;
    tmp->index = index;
    tmp->next = NULL;
    is_list *p = head;
    
    while (p->next != NULL)
        p = p->next;
    p->next = tmp;
}

is_list *Remove_all_island_list(is_list *head) {
    while (head != NULL) {
        is_list *p = head;
        head = head->next;
        free(p);
    }
    return NULL;
}
////////////////////////////////////////////////////////////////////////////////
n_list *Create_node_list(char *island1, char *island2, int distance) {
    n_list *tmp = (n_list*)malloc(sizeof(n_list));
    tmp->island1 = island1;
    tmp->island2 = island2;
    tmp->distance = distance;
    tmp->next = NULL;
    return(tmp);
}

void Add_elem_end_node_list(char *island1, char *island2, int distance, n_list *head) {
    n_list *tmp = (n_list*)malloc(sizeof(n_list));
    tmp->island1 = island1;
    tmp->island2 = island2;
    tmp->distance = distance;
    tmp->next = NULL;
    n_list *p = head;
    while (p->next != NULL)
        p = p->next;
    p->next = tmp;
}

n_list *Remove_all_node_list(n_list *head) {
    while (head != NULL) {
        n_list *p = head;
        head = head->next;
        free(p);
    }
    return NULL;
}

