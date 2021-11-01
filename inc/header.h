#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"
#include <stdio.h>
typedef struct island_list {
    char *island1;
    char *island2;
    int distance;
}           is_list;

typedef struct node_list {
    int index;
    struct island_list element;
    struct node_list *next;
}            n_list;

n_list *create_node(int index, char *isl1, char *isl2, int dist);
n_list *add_elem_start(int index, char *isl1, char *isl2, int dist, n_list *Head);
n_list *remove_list(n_list *Head);
n_list *print_list(n_list *tmp);
void add_ellem_end(int index, char *isl1, char *isl2, int dist, n_list *Head);

void print_error(int argc, char* argv[]);
void algorithm(char* argv[]);

#endif

