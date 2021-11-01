#include "../inc/header.h"

n_list *create_node(int index, char *isl1, char *isl2, int dist) {
    n_list *tmp = (n_list*)malloc(sizeof(n_list));
    tmp->index = index;
    tmp->element.island1 = isl1;
    tmp->element.island2 = isl2;
    tmp->element.distance = dist;
    tmp->next = NULL;
    return(tmp);
}

void add_ellem_end(int index, char *isl1, char *isl2, int dist, n_list *Head) {
    n_list *tmp = (n_list*)malloc(sizeof(n_list));
    tmp->index = index;
    tmp->element.island1 = isl1;
    tmp->element.island2 = isl2;
    tmp->element.distance = dist;
    tmp->next = NULL;
    n_list *p = Head;
    while (p -> next != NULL)
        p = p -> next;
    p -> next = tmp;
}

n_list *add_elem_start(int index, char *isl1, char *isl2, int dist, n_list *Head) {
    n_list *tmp = (n_list*)malloc(sizeof(n_list));
    tmp->index = index;
    tmp->element.island1 = isl1;
    tmp->element.island2 = isl2;
    tmp->element.distance = dist;
    tmp->next = Head;
    return(tmp);
}

n_list *remove_list(n_list *Head) {
    while (Head != NULL) {
        n_list *p = Head;
        Head = Head -> next;
        free(p);
    }
    return NULL;
}

n_list *print_list(n_list *tmp) {
    while (tmp != NULL) {
        printf("%d\n", tmp->index);
        printf("%s -", tmp->element.island1);
        printf("%s, ", tmp->element.island2);
        printf("%d\n", tmp->element.distance);
        tmp = tmp -> next;
    }
    return(tmp);
}

