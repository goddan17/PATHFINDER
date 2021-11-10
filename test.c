#include <unistd.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <malloc/malloc.h>
//#include <malloc.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
typedef struct island_list {
    char *name_island;
    int index;
    struct island_list *next;
}   is_list;
////////////////////////////////////////////////////////////////////////////////
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
typedef struct node_list {
    char *island1;
    char *island2;
    int distance;
    struct node_list *next;
}   n_list;
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
////////////////////////////////////////////////////////////////////////////////
int *recurs(int index_is, int index_is3, int **start_arr, int **res, int *arr_way, int i) {
    arr_way[i] = index_is3;
    if (start_arr[index_is - 1][index_is3] == -1) {
        index_is3 = res[index_is - 1][index_is3];
        i++;
        recurs(index_is, index_is3, start_arr, res, arr_way, i);
    }
    return arr_way;
}

int **duplicate_way(int index_is, int index_is3, int **start_arr, int **res, int *arr_way, int l, int **arr_ways, int n, int num_3d) {
    for (int i = 0; i < num_3d; i++) {
        for (int j = 0; j < n; j++) {
            arr_way[j] = 0;
        }
        arr_way = recurs(index_is, index_is3, start_arr, res, arr_way, l);
        for (int j = 0; j < n; j++) {
            arr_ways[i][j] = arr_way[j];
        }
    }
    return arr_ways;
}

int main() {
    int n = 5;
    is_list *islands = Create_island_list("A", 1);
    is_list *head_islands = islands;
    Add_elem_end_island_list("B", 2, islands);
    Add_elem_end_island_list("C", 3, islands);
    Add_elem_end_island_list("D", 4, islands);
    Add_elem_end_island_list("E", 5, islands);
    
    /*while (islands != NULL) {
        printf("INDEX = %d ", islands->index);
        printf("NAME = %s\n", islands->name_island);
        islands = islands->next;
    }*/
    
    n_list *node_lists = Create_node_list("A", "B", 11);
    n_list *head_node = node_lists;
    Add_elem_end_node_list("A", "C", 10, node_lists);
    Add_elem_end_node_list("B", "D", 5, node_lists);
    Add_elem_end_node_list("C", "D", 6, node_lists);
    Add_elem_end_node_list("C", "E", 15, node_lists);
    Add_elem_end_node_list("D", "E", 4, node_lists);
    
    /*while (node_lists != NULL) {
        printf("%s - ", node_lists->island1);
        printf("%s, ", node_lists->island2);
        printf("%d\n", node_lists->distance);
        node_lists = node_lists->next;
    }*/
    int **arr = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++) {
        arr[i] = (int *)malloc(n*sizeof(int));
    }
    int **res = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++) {
        res[i] = (int *)malloc(n*sizeof(int));
    }
    int **res_duplicate = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++) {
        res_duplicate[i] = (int *)malloc(n*sizeof(int));
    }
    int **start_arr = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++) {
        start_arr[i] = (int *)malloc(n*sizeof(int));
    }
    int *arr_way = (int *)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        arr_way[i] = 0;
    }
    int *arr_way_2 = (int *)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        arr_way_2[i] = 0;
    }
    int **arr_dist_way = (int **)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr_dist_way[i] = (int *)malloc(2*sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            arr_dist_way[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
            res[i][j] = 0;
            res_duplicate[i][j] = 0;
            start_arr[i][j] = 0;
        }
    }
    char *buff1;
    char *buff2;
    int num = 0;
    int num_3d = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            num = -1;
            if (i == j) {
                continue;
            }
            while (islands != NULL) {
                if(i + 1 == islands->index) {
                    buff1 = islands->name_island;
                }
                islands = islands->next;
            }
            islands = head_islands;
            while (islands != NULL) {
                if(j + 1 == islands->index) {
                    buff2 = islands->name_island;
                }
                islands = islands->next;
            }
            islands = head_islands;
            while (node_lists != NULL) {
                if (strcmp(buff1, node_lists->island1) == 0 || strcmp(buff1, node_lists->island2) == 0) {
                    if (strcmp(buff2, node_lists->island1) == 0 || strcmp(buff2, node_lists->island2) == 0) {
                        num = node_lists->distance;
                    }
                }
                node_lists = node_lists->next;
            }
            node_lists = head_node;
            if (num > 0) {
                num_3d++;
            }
            arr[i][j] = num;
            start_arr[i][j] = num;
        }
    }
    int **ways = (int **)malloc(num_3d*sizeof(int *));
    for (int i = 0; i < num_3d; i++) {
        ways[i] = (int *)malloc(n*sizeof(int));
    }
    for (int i = 0; i < num_3d; i++) {
        for (int j = 0; j < n; j++) {
            ways[i][j] = 0;
        }
    }
    int ***res2 = (int ***)malloc(n*sizeof(int **));
    for (int i = 0; i < n; i++) {
        res2[i] = (int **)malloc(n*sizeof(int*));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res2[i][j] = (int *)malloc(num_3d*sizeof(int));
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < num_3d; l++) {
                res2[i][j][l] = 0;
            }
        }
    }
    int *arr_duplicate = (int *)malloc(num_3d*sizeof(int));
    for (int i = 0; i < num_3d; i++) {
        arr_duplicate[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] >= 10) {
                printf("%d ", arr[i][j]);
            }
            else {
                printf("0%d ", arr[i][j]);
            }
            
        }
        printf("%s\n", "|");
    }
    printf("%s\n", "========================================");
    int g = 0;
    int h = 0;
    int l = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                /*if (arr[i][j] > 0) {
                    continue;
                }*/
                if (i == j) {
                    continue;
                }
                if(i != j && arr[i][k] != -1 && arr[k][j] != -1) {
                    if (arr[i][j] == -1) {
                        h = arr[i][k] + arr[k][j];
                        if (g > h) {
                            g = arr[i][k] + arr[k][j];
                            /*if (arr[i][j] == g) {
                                res2[i][j][l] = k;
                                res2[j][i][l] = k;
                                l++;
                                continue;
                            }*/
                            arr[i][j] = g;
                            arr[j][i] = g;
                            res[i][j] = k;
                            res[j][i] = k;
                            continue;
                        }
                        else {
                            g = arr[i][k] + arr[k][j];
                            continue;
                        }
                    }
                    else {
                        if (arr[i][j] > arr[i][k] + arr[k][j]) {
                            arr[i][j] = arr[i][k] + arr[k][j];
                            arr[j][i] = arr[i][k] + arr[k][j];
                            res[i][j] = k;
                            res[j][i] = k;
                        }
                        else {
                            if (arr[i][k] + arr[k][j] == arr[i][j]) {
                                res2[i][j][l] = k;
                                res2[j][i][l] = k;
                                l++;
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] >= 10) {
                printf("%d ", arr[i][j]);
            }
            else {
                printf("%d ", arr[i][j]);
            }
            
        }
        printf("%s\n", "|");
    }
    printf("%s\n", "========================================");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] >= 10) {
                printf("%d ", res[i][j]);
            }
            else {
                printf("%d ", res[i][j]);
            }
            
        }
        printf("%s\n", "|");
    }
    printf("%s\n", "========================================");
    printf("%s\n", "|");
    for (int l = 0; l < num_3d; l++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (res2[i][j][l] == 0) {
                    res2[i][j][l] = res[i][j];
                }
            }
        }
    }
    for (int l = 0; l < num_3d; l++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", res2[i][j][l]);
            }
            printf("%s\n", "|");
        }
        printf("%s\n", "|");
    }
    char *buff_island;
    char *buff_island2;
    char *buff_island3;
    int index_is3 = 0;
    int indicator = 0;
    for (int index_is = 1; index_is <= n; index_is++) {
        for (int index_is2 = index_is + 1; index_is2 <= n; index_is2++) {
            indicator = 0;
            while (islands != NULL) {
                if (index_is == islands->index) {
                    buff_island = islands->name_island;
                    break;
                }
                islands = islands->next;
            }
            islands = head_islands;
            while (islands != NULL) {
                if (index_is2 == islands->index) {
                    buff_island2 = islands->name_island;
                    break;
                }
                islands = islands->next;
            }
            islands = head_islands;
            while (node_lists != NULL) {
                if (start_arr[index_is - 1][index_is2 - 1] != arr[index_is - 1][index_is2 - 1] && start_arr[index_is - 1][index_is2 - 1] > 0) {
                    indicator = 0;
                    break;
                }
                else {
                    if (strcmp(buff_island, node_lists->island1) == 0 && strcmp(buff_island2, node_lists->island2) == 0) {
                        indicator = 1;
                        printf("%s\n", "========================================");
                        printf("Path: %s -> %s\n", buff_island, buff_island2);
                        printf("Route: %s -> %s\n", buff_island, buff_island2);
                        printf("Distance: %d\n", arr[index_is - 1][index_is2 - 1]);
                        printf("%s\n", "========================================");
                        break;
                    }
                }
                
                node_lists = node_lists->next;
            }
            node_lists = head_node;
            if (indicator == 0) {
                index_is3 = res[index_is-1][index_is2-1];
                int l = 0;
                for (int i = 0; i < num_3d; i++) {
                    for (int j = 0; j < n; j++) {
                        ways[i][j] = 0;
                    }
                }
                for (int i = 0; i < n; i++) {
                    arr_way_2[i] = 0;
                }
                for (int i = 0; i < n; i++) {
                    arr_way[i] = 0;
                }
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < 2; j++) {
                        arr_dist_way[i][j] = 0;
                    }
                }
                for (int i = 0; i < num_3d; i++) {
                    arr_duplicate[i] = 0;
                }
                int i2 = 0;
                for (int i = 0; i < num_3d; i++) {
                    if (res2[index_is-1][index_is2-1][i] == 0) {
                        continue;
                    }
                    else {
                        arr_duplicate[i2] = res2[index_is-1][index_is2-1][i];
                        i2++;
                    }
                }
                int num_buff = 0;
                for (int i = 0; i < num_3d; i++) {
                    num_buff = arr_duplicate[i];
                    for (int j = 0; j < i; j++) {
                        if (num_buff == arr_duplicate[j]) {
                            arr_duplicate[j] = 0;
                        }
                    }
                }
                arr_way = recurs(index_is, index_is3, start_arr, res, arr_way, l);
                int c = 0;
                for (int i = 0; i < n/2; i++) {
                    c = arr_way[i];
                    arr_way[i] = arr_way[n - 1 - i];
                    arr_way[n - 1 - i] = c;
                }
                int bufff = 0;
                for (int i = 0; i < n; i++) {
                    bufff = arr_way[i];
                    arr_way_2[i] = bufff;
                }
                for (int i = 0; i < n; i++) {
                    arr_way[i] = 0;
                }
                bufff = 0;
                int inum = 0;
                for (int i = 0; i < n; i++) {
                    if (arr_way_2[i] == 0) {
                        continue;
                    }
                    bufff = arr_way_2[i];
                    arr_way[inum] = bufff;
                    inum++;
                }
                printf("%s\n", "========================================");
                for (int i = 0; i < n; i++) {
                    printf("%d ", arr_way[i]);
                }
                printf("%s\n", "|");
                for (int i = 0; i < num_3d; i++) {
                    printf("%d ", arr_duplicate[i]);
                }
                printf("%s\n", "|");
                printf("Path: %s -> %s\n", buff_island, buff_island2);
                printf("Route: %s ->", buff_island);
                int count = 0;
                for (int i = 0; i < n; i++) {
                    if (arr_way[i] == 0) {
                        continue;
                    }
                    while (islands != NULL) {
                        if (arr_way[i] + 1 == islands->index) {
                            buff_island3 = islands->name_island;
                        }
                        islands = islands->next;
                    }
                    islands = head_islands;
                    printf(" %s ->", buff_island3); 
                    count++;
                }
                printf(" %s\n", buff_island2);
                int step = 0;
                int t = 0;
                for (int i = 0; i < count + 1; i++) {
                    for (int j = 0; j < 2; j++) {
                        if (t > 0 && j == 0) {
                            arr_dist_way[i][j] = t;
                            continue;
                        }
                        if (i == 0 && j == 0) {
                            arr_dist_way[i][j] = index_is;
                            continue;
                        }
                        if (i + 1 == count + 1 && j + 1 == 2) {
                            arr_dist_way[i][j] = index_is2;
                            continue;
                        }
                        arr_dist_way[i][j] = arr_way[i] + 1;
                        if (j == 1) {
                            t = arr_way[i] + 1;
                        }
                    }
                    if (arr_dist_way[i][0] != 0 || arr_dist_way[i][1] != 0) {
                        step++;
                    }
                }
                
                printf("Distance%s", ":");
                printf("%s\n", "|");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < 2; j++) {
                        /*int s = arr_dist_way[i][j];
                        int d = arr_dist_way[i][j+1];
                        printf(" %d +", arr[s][d]);*/
                        printf("%d ", arr_dist_way[i][j]);
                    }
                    printf("%s\n", "|");
                }
                //printf(" %d +", arr[arr_dist_way[0][0] - 1][arr_dist_way[0][1] - 1]);
                bufff = 0;
                int bufff2 = 0;
                int print_num_arr_dist_way = 0;
                for (int i = 0; i <= count; i++) {
                    for (int j = 0; j < 2; j++) {
                        if (j == 0) {
                            bufff = arr_dist_way[i][j] - 1;
                        }
                        else {
                            bufff2 = arr_dist_way[i][j] - 1;
                        }
                    }
                    print_num_arr_dist_way = arr[bufff][bufff2];
                    if (i == count) {
                        printf(" %d ", print_num_arr_dist_way);
                        break;
                    }
                    printf(" %d +", print_num_arr_dist_way);
                }
                
                printf("= %d", arr[index_is - 1][index_is2 - 1]);
                printf("\n%s\n", "========================================");
                int i3 = 0;
                int k_ind = 0;
                for (int i = 0; i < num_3d; i++) {
                    if (arr_duplicate[i] == 0) {
                        if (k_ind > 0) {
                            break;
                        }
                        continue;
                    }
                    if (arr_duplicate[i] > 0) {
                        k_ind++;
                        arr_duplicate[i3] = arr_duplicate[i];
                        i3++;
                        arr_duplicate[i] = 0;
                    }
                }
                for (int i = 0; i < num_3d; i++) {
                    if (res[index_is - 1][index_is2 - 1] >= arr_duplicate[i]) {
                        arr_duplicate[i] = 0;
                    }
                }
                printf("%s\n", "|");
                for (int i = 0; i < num_3d; i++) {
                    printf("%d ", arr_duplicate[i]);
                }
                printf("%s\n", "|");
                for (int i = 0; i < num_3d; i++) {
                    for (int j = 0; j < n; j++) {
                        printf("%d ", ways[i][j]);
                    }
                    printf("%s\n", "|");
                }
                printf("%s\n", "|");
                if (arr_duplicate[0] != 0 ) {
                    for (int i = 0; i < num_3d; i++) {
                        if (arr_duplicate[i] == 0) {
                            break;
                        }
                        /*if (arr_duplicate[i] <= res[index_is - 1][index_is2 - 1]) {
                            continue;
                        }*/
                        for (int i2 = 0; i2 < n; i2++) {
                            arr_way_2[i2] = 0;
                        }
                        for (int j = 0; j < n; j++) {
                            arr_way[j] = 0;
                        }
                        l = 0;
                        int num_buff1 = arr_duplicate[i];
                        int index_duplicate = 1;
                        for (int k = 0; k < n; k++) {
                            for (int kk = 0; kk < n; kk++) {
                                res_duplicate[k][kk] = 0;
                            }
                        }
                        for (int j = 0; j < num_3d; j++) {
                            if (num_buff1 == res2[index_is - 1][index_is2 - 1][j]) {
                                for (int k = 0; k < n; k++) {
                                    for (int kk = 0; kk < n; kk++) {
                                        res_duplicate[k][kk] = res2[k][kk][j];
                                    }
                                }
                                break;
                            }
                            index_duplicate++;
                        }
                        index_is3 = res_duplicate[index_is-1][index_is2-1];
                        arr_way = recurs(index_is, index_is3, start_arr, res_duplicate, arr_way, l);
                        l = 0;
                        ways = duplicate_way(index_is, index_is3, start_arr, res_duplicate, arr_way, l, ways, n, num_3d);
                        int c = 0;
                        for (int v = 0; v < n/2; v++) {
                            c = arr_way[v];
                            arr_way[v] = arr_way[n - 1 - v];
                            arr_way[n - 1 - v] = c;
                        }
                        int bufff = 0;
                        for (int v = 0; v < n; v++) {
                            bufff = arr_way[v];
                            arr_way_2[v] = bufff;
                        }
                        for (int v = 0; v < n; v++) {
                            arr_way[v] = 0;
                        }
                        bufff = 0;
                        int inum = 0;
                        for (int v = 0; v < n; v++) {
                            if (arr_way_2[v] == 0) {
                                continue;
                            }
                            bufff = arr_way_2[v];
                            arr_way[inum] = bufff;
                            inum++;
                        }
                        for (int j = 0; j < n; j++) {
                            printf("%d |", arr_way[j]);
                        }
                        printf("%s\n", "|");
                        
                        printf("%s\n", "|");
                        for (int mm = 0; mm < n; mm++) {
                            for (int nn = 0; nn < n; nn++) {
                                printf("%d ", res_duplicate[mm][nn]);
                            }
                            printf("%s\n", "|");
                        }
                        printf("\nres2 index = %d\n", index_duplicate);
                    }
                    printf("\n%s\n", "===");
                }
            }
            else {
                continue;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        free(arr[i]);
        free(res[i]);
        free(start_arr[i]);
        free(arr_dist_way[i]);
    }
    free(arr);
    free(res);
    free(start_arr);
    free(arr_dist_way);
    free(arr_way);
    return 0;
}
