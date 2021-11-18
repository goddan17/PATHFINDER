#include "../inc/header.h"

void algorithm(char* argv[]) {
    char buffer;
    int fl = open(argv[1], O_RDONLY);
    int size = read(fl, &buffer, 1);
    int num_bridges = 0;
    int ss_size = 0;
    int kk_size = 0;
    int gg_size = 0;
    int line_num = 1;
    fl = open(argv[1], O_RDONLY);
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 1) {
            if (buffer == '\n') {
                line_num++;
                continue;
            }
        }
        else if (line_num > 1) {
            if (buffer == '-') {
                num_bridges += 2;
            }
            if (mx_isdigit(buffer)) {
                gg_size++;
                continue;
            }
            if (buffer == ',') {
                gg_size++;
            }
            ss_size++;
            kk_size++;
        }
    }
    close(fl);

    fl = open(argv[1], O_RDONLY);
    char *ss = mx_strnew(ss_size);
    line_num = 1;
    int i = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 1) {
            if (buffer == '\n') {
                line_num++;
                continue;
            }
        }
        else if (line_num > 1) {
            if (buffer == '\n') {
                ss[i] = '-';
                i++;
                continue;
            }
            if (buffer == ',' || mx_isdigit(buffer)) {
                continue;
            }
            ss[i] = buffer;
            i++;
        }
    }
    close(fl);

    fl = open(argv[1], O_RDONLY);
    char *kk = mx_strnew(kk_size);
    line_num = 1;
    int j = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 1) {
            if (buffer == '\n') {
                line_num++;
                continue;
            }
        }
        else if (line_num > 1) {
            if (buffer == '\n' || mx_isdigit(buffer)) {
                continue;
            }
            kk[j] = buffer;
            j++;
        }
    }
    close(fl);

    fl = open(argv[1], O_RDONLY);
    char *gg = mx_strnew(gg_size);
    line_num = 1;
    int h = 0;
    int nn_size = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 1) {
            if (buffer == '\n') {
                line_num++;
                continue;
            }
            nn_size++;
        }
        else if (line_num > 1) {
            if (buffer == ',' || mx_isdigit(buffer)) {
                gg[h] = buffer;
                h++;
                continue;
            }
        }
    }
    close(fl);
    char **arr1_buff;
    char **arr2_buff;
    char **arr3_buff;
    arr1_buff = mx_strsplit(ss, '-');
    arr2_buff = mx_strsplit(ss, '-');
    arr3_buff = mx_strsplit(gg, ',');
    char *buff;
    for (int i = 0; i < num_bridges; i++) {
        buff = arr1_buff[i];
        for (int j = i + 1; j < num_bridges; j++) {
            if (mx_strcmp(buff, arr1_buff[j]) == 0) {
                arr1_buff[j] = mx_strdup("\0");
            }
        }
    }
    fl = open(argv[1], O_RDONLY);
    char *nn = mx_strnew(nn_size);
    i = 0;
    while (size == read(fl, &buffer, 1)) {
        if (buffer == '\n') {
            break;
        }
        nn[i] = buffer;
    }
    close(fl);
    int n = mx_atoi(nn);
    char **arr_island = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        arr_island[i] = "\0";
    }
    j = 0;
    for (int i = 0; i < num_bridges; i++) {
        if (mx_strcmp(arr1_buff[i], "\0") == 0) {
            continue;
        }
        arr_island[j] = arr1_buff[i];
        j++;
    }
    pathfinder(arr_island, arr2_buff, arr3_buff, n, num_bridges);
}

