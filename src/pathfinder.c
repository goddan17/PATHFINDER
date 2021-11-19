#include "../inc/header.h"

int *recurs(int index_is, int index_is3, int **start_arr, int **res, int *arr_way, int i) {
    arr_way[i] = index_is3;
    if (start_arr[index_is - 1][index_is3] == -1) {
        index_is3 = res[index_is - 1][index_is3];
        i++;
        recurs(index_is, index_is3, start_arr, res, arr_way, i);
    }
    return arr_way;
}

int **duplicate_way(int index_is, int index_is3, int **start_arr, int *arr_way, int l, int **arr_ways, int n, int num_3d, int ***res2) {
    int **res = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++) {
        res[i] = (int *)malloc(n*sizeof(int));
    }
    for (int i = 0; i < num_3d; i++) {
        for (int m = 0; m < n; m++) {
            for (int b = 0; b < n; b++) {
                res[m][b] = 0;
            }
        }
        for (int m = 0; m < n; m++) {
            for (int b = 0; b < n; b++) {
                res[m][b] = res2[m][b][i];
            }
        }
        for (int j = 0; j < n; j++) {
            arr_way[j] = 0;
        }
        arr_way = recurs(index_is, index_is3, start_arr, res, arr_way, l);
        for (int j = 0; j < n; j++) {
            arr_ways[i][j] = arr_way[j];
        }
    }
    for (int i = 0; i < n; i++) {
        free(res[i]);
    }
    free(res);
    return arr_ways;
}

void pathfinder(char **arr_islands1, char **arr_islands_dist, char **arr_num_dist, int n, int amount_bridges) {
    is_list *islands = Create_island_list(arr_islands1[0], 1);
    is_list *head_islands = islands;
    for (int i = 1; i < n; i++) {
        Add_elem_end_island_list(arr_islands1[i], i + 1, islands);
    }

    n_list *node_lists = Create_node_list(arr_islands_dist[0], arr_islands_dist[1], mx_atoi(arr_num_dist[0]));
    n_list *head_node = node_lists;
    int uu = 1;
    for (int i = 2; i < amount_bridges; i++) {
        if ((i + 1) % 2 == 0) {
            Add_elem_end_node_list(arr_islands_dist[i - 1], arr_islands_dist[i], mx_atoi(arr_num_dist[uu]), node_lists);
            uu++;
        }
    }
    
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
    int *arr_way_3 = (int *)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        arr_way_3[i] = 0;
    }
    int *arr4 = (int *)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        arr4[i] = 0;
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
                if (mx_strcmp(buff1, node_lists->island1) == 0 || mx_strcmp(buff1, node_lists->island2) == 0) {
                    if (mx_strcmp(buff2, node_lists->island1) == 0 || mx_strcmp(buff2, node_lists->island2) == 0) {
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
    int g = 0;
    int l = 0;
    int h = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                if(i != j && arr[i][k] != -1 && arr[k][j] != -1) {
                    if (arr[i][j] == -1) {
                        g = arr[i][k] + arr[k][j];
                        arr[i][j] = g;
                        arr[j][i] = g;
                        res[i][j] = k;
                        res[j][i] = k;
                        continue;
                    }
                    else {
                        g = arr[i][j];
                        h = arr[i][k] + arr[k][j];
                        if (g > h) {
                            arr[i][j] = h;
                            arr[j][i] = h;
                            res[i][j] = k;
                            res[j][i] = k;
                        }
                        else {
                            if (g == h) {
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
    for (int l = 0; l < num_3d; l++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    res2[i][j][l] = 0;
                }
            }
        }
    }
    int ggg = 0;
    int hhh = 0;
    int xxx = 0;
    int yyy = 0;
    for (int l = 0; l < num_3d; l++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                xxx = res2[i][j][l];
                yyy = arr[i][j];
                ggg = arr[i][xxx];
                hhh = arr[xxx][j];
                if (ggg + hhh != yyy) {
                    res2[i][j][l] = 0;
                } 
            }
        }
    }
    for (int l = 0; l < num_3d; l++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (res2[i][j][l] == 0) {
                    res2[i][j][l] = res[i][j];
                }
            }
        }
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
                    if (mx_strcmp(buff_island, node_lists->island1) == 0 && mx_strcmp(buff_island2, node_lists->island2) == 0) {
                        indicator = 1;
                        mx_printstr("========================================\n");
                        mx_printstr("Path: ");
                        mx_printstr(buff_island);
                        mx_printstr(" -> ");
                        mx_printstr(buff_island2);
                        mx_printstr("\nRoute: ");
                        mx_printstr(buff_island);
                        mx_printstr(" -> ");
                        mx_printstr(buff_island2);
                        mx_printstr("\nDistance: ");
                        mx_printint(arr[index_is - 1][index_is2 - 1]);
                        mx_printstr("\n========================================\n");
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
                mx_printstr("========================================\n");
                mx_printstr("Path: ");
                mx_printstr(buff_island);
                mx_printstr(" -> ");
                mx_printstr(buff_island2);
                mx_printstr("\nRoute: ");
                mx_printstr(buff_island);
                mx_printstr(" -> ");
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
                    mx_printstr(buff_island3);
                    mx_printstr(" ->");
                    count++;
                }
                mx_printstr(buff_island2);
                mx_printstr("\n");
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
                mx_printstr("Distance:");
                int zz = 0;
                for (int i = 0; i < n; i++) {
                    if (arr_way[i] > 0) {
                        zz++;
                    }
                }
                if (zz == 0) {
                    mx_printstr(" ");
                    mx_printint(arr[index_is - 1][index_is2 - 1]);
                }
                else {
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
                            mx_printstr(" ");
                            mx_printint(print_num_arr_dist_way);
                            break;
                        }
                        mx_printstr(" ");
                        mx_printint(print_num_arr_dist_way);
                        mx_printstr(" +");
                    }
                    mx_printstr(" = ");
                    mx_printint(arr[index_is - 1][index_is2 - 1]);
                }
                mx_printstr("\n");
                mx_printstr("========================================");
                mx_printstr("\n");
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
                    if (res[index_is - 1][index_is2 - 1] > arr_duplicate[i]) {
                        arr_duplicate[i] = 0;
                    }
                }
                bool arr_dup = false;
                for (int i = 0; i < num_3d; i++) {
                    if (arr_dup == true) {
                        break;
                    }
                    if (arr_duplicate[i] > 0) {
                        arr_dup = true;
                    } 
                }
                if (arr_dup) {
                    if (step == 2) {
                        for (int i = 0; i < num_3d; i++) {
                            if (arr_way[0] == arr_duplicate[i]) {
                                arr_duplicate[i] = 0;
                            }
                        }
                        for (int i = 0; i < num_3d; i++) {
                            if (arr_duplicate[i] == 0) {
                                continue;
                            }
                            arr_way[0] = arr_duplicate[i];
                            mx_printstr("========================================\n");
                            mx_printstr("Path: ");
                            mx_printstr(buff_island);
                            mx_printstr(" -> ");
                            mx_printstr(buff_island2);
                            mx_printstr("\nRoute: ");
                            mx_printstr(buff_island);
                            mx_printstr(" -> ");
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
                                mx_printstr(buff_island3);
                                mx_printstr(" ->");
                                count++;
                            }
                            mx_printstr(buff_island2);
                            mx_printstr("\n");
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
                            mx_printstr("Distance:");
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
                                    mx_printstr(" ");
                                    mx_printint(print_num_arr_dist_way);
                                    break;
                                }
                                mx_printstr(" ");
                                mx_printint(print_num_arr_dist_way);
                                mx_printstr(" +");
                            }
                            mx_printstr(" = ");
                            mx_printint(arr[index_is - 1][index_is2 - 1]);
                            mx_printstr("\n");
                            mx_printstr("========================================");
                            mx_printstr("\n");
                        }
                    }
                    else {
                        for (int i2 = 0; i2 < n; i2++) {
                            arr_way_2[i2] = 0;
                        }
                        for (int i2 = 0; i2 < n; i2++) {
                            arr_way_3[i2] = 0;
                        }
                        ways = duplicate_way(index_is, index_is3, start_arr, arr_way_3, l, ways, n, num_3d, res2);
                        for (int i = 0; i < num_3d; i++) {
                            int c = 0;
                            for (int j = 0; j < n/2; j++) {
                                c = ways[i][j];
                                ways[i][j] = ways[i][n - 1 - j];
                                ways[i][n - 1 - j] = c;
                            }
                            int bufff = 0;
                            for (int j = 0; j < n; j++) {
                                bufff = ways[i][j];
                                arr_way_2[j] = bufff;
                            }
                            for (int j = 0; j < n; j++) {
                                ways[i][j] = 0;
                            }
                            bufff = 0;
                            int inum = 0;
                            for (int j = 0; j < n; j++) {
                                if (arr_way_2[j] == 0) {
                                    continue;
                                }
                                bufff = arr_way_2[j];
                                ways[i][inum] = bufff;
                                inum++;
                            }
                        }
                        int k_ind1 = 0;
                        int amount_ways_num = 0;
                        for (int j = 0; j < num_3d; j++) {
                            k_ind1  = 0;
                            amount_ways_num = 0;
                            for (int k = 0; k < n; k++) {
                                if (ways[j][k] == 0) {
                                    break;
                                }
                                if (ways[j][k] == arr_way[k]) {
                                    k_ind1++;
                                }
                                amount_ways_num++;
                            }
                            if (k_ind1 == amount_ways_num) {
                                for (int k = 0; k < n; k++) {
                                    if (ways[j][k] == 0) {
                                        break;
                                    }
                                    ways[j][k] = 0;
                                }
                            }
                        }
                        for (int i = 0; i < num_3d; i++) {
                            if (ways[i][0] == 0) {
                                continue;
                            }
                            for (int j = 0; j < n; j++) {
                                if (ways[i][j] == 0) {
                                    break;
                                }
                                arr_way[j] = ways[i][j];
                            }
                            k_ind1 = 0;
                            amount_ways_num = 0;
                            for (int j = 0; j < num_3d; j++) {
                                k_ind1  = 0;
                                amount_ways_num = 0;
                                for (int k = 0; k < n; k++) {
                                    if (ways[j][k] == 0) {
                                        break;
                                    }
                                    if (ways[j][k] == arr_way[k]) {
                                        k_ind1++;
                                    }
                                    amount_ways_num++;
                                }
                                if (k_ind1 == amount_ways_num) {
                                    for (int k = 0; k < n; k++) {
                                        if (ways[j][k] == 0) {
                                            break;
                                        }
                                        ways[j][k] = 0;
                                    }
                                }
                            }

                            mx_printstr("========================================\n");
                            mx_printstr("Path: ");
                            mx_printstr(buff_island);
                            mx_printstr(" -> ");
                            mx_printstr(buff_island2);
                            mx_printstr("\nRoute: ");
                            mx_printstr(buff_island);
                            mx_printstr(" -> ");
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
                                mx_printstr(buff_island3);
                                mx_printstr(" ->");
                                count++;
                            }
                            mx_printstr(buff_island2);
                            mx_printstr("\n");
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
                
                            mx_printstr("Distance:");
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
                                    mx_printstr(" ");
                                    mx_printint(print_num_arr_dist_way);
                                    break;
                                }
                                mx_printstr(" ");
                                mx_printint(print_num_arr_dist_way);
                                mx_printstr(" +");
                            }
                
                            mx_printstr(" = ");
                            mx_printint(arr[index_is - 1][index_is2 - 1]);
                            mx_printstr("\n");
                            mx_printstr("========================================");
                            mx_printstr("\n");
                        }
                    }
                }
            }
            else {
                continue;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            free(res2[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        free(arr[i]);
        free(res[i]);
        free(start_arr[i]);
        free(arr_dist_way[i]);
        free(res_duplicate[i]);
        free(res2[i]);
    }
    for (int i = 0; i < num_3d; i++) {
        free(ways[i]);
    }
    free(arr);
    free(res);
    free(start_arr);
    free(arr_dist_way);
    free(arr_way);
    free(arr_way_2);
    free(arr_way_3);
    free(res_duplicate);
    free(arr4);
    free(ways);
    free(arr_duplicate);
    free(res2);
    Remove_all_island_list(islands);
    Remove_all_node_list(node_lists);
    exit(0);
}

