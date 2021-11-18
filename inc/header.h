#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"
#include <stdio.h>

typedef struct island_list {
    char *name_island;
    int index;
    struct island_list *next;
}   is_list;

typedef struct node_list {
    char *island1;
    char *island2;
    int distance;
    struct node_list *next;
}   n_list;

is_list *Create_island_list(char *name_island, int index);
void Add_elem_end_island_list(char *name_island, int index, is_list *head);
is_list *Remove_all_island_list(is_list *head);

n_list *Create_node_list(char *island1, char *island2, int distance);
void Add_elem_end_node_list(char *island1, char *island2, int distance, n_list *head);
n_list *Remove_all_node_list(n_list *head);

void print_error(int argc, char* argv[]);
void algorithm(char* argv[]);
void pathfinder(char **arr_islands1, char **arr_islands_dist, char **arr_num_dist, int n, int amount_bridges);
int *recurs(int index_is, int index_is3, int **start_arr, int **res, int *arr_way, int i);
int **duplicate_way(int index_is, int index_is3, int **start_arr, int *arr_way, int l, int **arr_ways, int n, int num_3d, int ***res2);

#endif

