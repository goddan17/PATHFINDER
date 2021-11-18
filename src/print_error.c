#include "../inc/header.h" 

void print_error(int argc, char* argv[]) {
    char buffer;
    int fl = open(argv[1], O_RDONLY);
    int size = read(fl, &buffer, 1);
    if (argc < 2 || argc > 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    if (fl < 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(0);
    }
    if (size == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(0);
    }
    close(fl);
    ////////////////////////////////////////////////////////
    fl = open(argv[1], O_RDONLY);
    int k = 0;
    while (size == read(fl, &buffer, 1)) {
        if (k > 0 && buffer == '\n') {
            break;
        }
        if (!mx_isdigit(buffer)) {
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
        else {
            k++;
            continue;
        }
    }
    close(fl);
    ////////////////////////////////////////////////////////

    fl = open(argv[1], O_RDONLY);
    int line_num = 1;
    int i = 0;
    int i1 = 0;
    int i2 = 0;
    while (size == read(fl, &buffer, 1)) {
        if (buffer == '\n') {
            if (line_num > 1) {
                if (i <= 0 || i1 <= 0 || i2 == 0) {
                    mx_printerr("error: line ");
                    mx_printerr(mx_itoa(line_num));
                    mx_printerr(" is not valid\n");
                    exit(0);
                }
            }
            i2 = 0;
            i = 0;
            i1 = 0;
            line_num++;
        }
        if (line_num > 1) {
            if (buffer == '-') {
                i++;
            }
            if (buffer == ',') {
                i1++;
            }
            if (i >= 2 || i1 >= 2) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(line_num));
                mx_printerr(" is not valid\n");
                exit(0);
            }
            if (buffer != '\n') {
                i2++;
            }
        }
    }
    close(fl);

    //////////////////////////////////////////////////////////

    fl = open(argv[1], O_RDONLY);
    int g = 0;
    double num1 = 0;
    double num2 = 0;
    while (size == read(fl, &buffer, 1)) {
        if(buffer == '\n') {
            num1 = num1 * mx_pow(10, g - 1);
            break;
        }
        if (g == 0) {
            num1 = mx_atoi(&buffer);
        }
        else {
            num2 = mx_atoi(&buffer);
            num1 = num1 + num2 / mx_pow(10, g);
        }
        g++;
    }
    int file_num_islands = num1;
    //mx_printerr(mx_itoa(num1)); 
    close(fl);

    fl = open(argv[1], O_RDONLY);
    //char *arr = mx_strnew(num1);
    //int side_buff = 0;
    line_num = 0;
    int ss_size = 0;
    int kk_size = 0;
    while (size == read(fl, &buffer, 1)) {
        if (buffer == '\n') {
            line_num++;
            continue;
        }
        if (line_num > 0) {
            if (buffer == '\n') {
                kk_size++;
                ss_size++;
                continue;
            }
            if (buffer == ',') {
                kk_size++;
                continue;
            }
            kk_size++;
            ss_size++;
        }
    }
    close(fl);

    fl = open(argv[1], O_RDONLY);
    i = 0;
    int size_arr = 0;
    char *ss = mx_strnew(ss_size);
    char **arr;
    int amount_dist = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 0) {
            if (buffer == '\n') {
                line_num++;
            }
            continue;
        }
        if (line_num > 0 && !mx_isdigit(buffer)) {
            if (buffer == '-') {
                amount_dist++;
                size_arr = size_arr + 2;
            }
            if (buffer == '\n') {
                ss[i] = '-';
                i++;
                continue;
            }
            if (buffer == ',') {
                continue;
            }
            ss[i] = buffer;
            i++;
        }  
    }
    //mx_printerr(ss);
    arr = mx_strsplit(ss, '-');
    //mx_printerr("=  ");
    //mx_printerr(arr[0]);
    //mx_printerr(mx_itoa(size_arr));
    char *buff_char;
    int num_islands = 0;
    int ind = 0;
    for (int i = 0; i < size_arr; i++) {
        ind = 0;
        buff_char = mx_strdup(arr[i]);
        for (int j = 0; j < i; j++) {
            if (mx_strcmp(buff_char, arr[j]) == 0) {
                ind++;
                break;
            }
        }
        if (ind == 0) {
            num_islands++;
        }
        else {
            continue;
        }
    }
    //mx_printerr(mx_itoa(num_islands));
    if (num_islands != file_num_islands) {
        mx_printerr("error: invalid number of islands\n");
        free(ss);
        mx_strdel(arr);
        exit(0);
    }
    free(ss);
    mx_strdel(arr);
    close(fl);
    //////////////////////////////////////////////////////////

    fl = open(argv[1], O_RDONLY);
    char *kk = mx_strnew(kk_size);
    char **arr1;
    int arr1_size = 0;
    line_num = 0;
    i = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 0) {
            if (buffer == '\n') {
                line_num++;
            }
            continue;
        }
        if (line_num > 0 && !mx_isdigit(buffer)) {
            if (buffer == '-') {
                arr1_size++;
            }
            kk[i] = buffer;
            i++;
        }
    }
    arr1 = mx_strsplit(kk, '\n');
    char *buff_char1;
    for (int i = 0; i < arr1_size; i++) {
        buff_char1 = mx_strdup(arr1[i]);
        for (int j = 0; j < i; j++) {
            if (mx_strcmp(buff_char1, arr1[j]) == 0) {
                mx_printerr("error: duplicate bridges\n");
                free(kk);
                mx_strdel(arr1);
                exit(0);
            }
        }
    }
    free(kk);
    mx_strdel(arr1);
    close(fl);
    fl = open(argv[1], O_RDONLY);
    line_num = 0;
    i = 0;
    int ind1 = 0;
    char *gg = mx_strnew(kk_size);
    char **arr2;
    long long int sum_dist = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 0) {
            if (buffer == '\n') {
                line_num++;
            }
            continue;
        }
        if (line_num > 0) {
            if (buffer == '\n') {
                continue;
            }
            if (ind1 == 0 && buffer == ',') {
                ind1++;
                continue;
            }
            if (ind1 > 0) {
                if (buffer == ',' || mx_isdigit(buffer)) {
                    gg[i] = buffer;
                    i++;
                    continue;
                }
            }
        }
    }
    ///mx_printerr(gg);
    arr2 = mx_strsplit(gg, ',');
    for (int i = 0; i < amount_dist; i++) {
        sum_dist = sum_dist + mx_atoi(arr2[i]);
    }
    if (sum_dist == 0 || sum_dist > 2147483647) {
        mx_printerr("error: sum of bridges lengths is too big\n");
        free(gg);
        mx_strdel(arr2);
        exit(0);
    }
    free(gg);
    mx_strdel(arr2);
    close(fl);
}

