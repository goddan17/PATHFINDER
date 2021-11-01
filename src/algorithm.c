#include "../inc/header.h"

void algorithm(char* argv[]) {
    char buffer;
    int fl = open(argv[1], O_RDONLY);
    int size = read(fl, &buffer, 1);
    int line_num = 0;
    int amount_sym = 0;
    int amount_bridges = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 0) {
            if (buffer == '\n') {
                line_num++;
            }
        }
        if (line_num > 0) {
            if (buffer == '\n') {
                continue;
            }
            if (buffer == '-') {
                amount_bridges++;
            }
            if (mx_isdigit(buffer)) {
                continue;
            }
            amount_sym++;
        }
    }
    close(fl);
    fl = open(argv[1], O_RDONLY);
    char *isl = mx_strnew(amount_sym);
    char *dist = mx_strnew(amount_bridges);
    int i = 0;
    int j = 0;
    line_num = 0;
    while (size == read(fl, &buffer, 1)) {
        if (line_num == 0) {
            if (buffer == '\n') {
                line_num++;
            }
        }
        if (line_num > 0) {
            if (buffer == '\n') {
                continue;
            }
            if (buffer == ',') {
                dist[i] = buffer;
                i++;
            }
            if (mx_isdigit(buffer)) {
                dist[i] = buffer;
                i++;
                continue;
            }
            isl[j] = buffer;
            j++;
        }
    }
    //char **arr_bridges = mx_strsplit(isl, ',');
    //char **arr_distance = mx_strsplit(dist, ',');
    //mx_printerr(arr_bridges[1]);
    //mx_printerr(arr_distance[1]);
    n_list *tmp = (n_list*)malloc(sizeof(n_list));
    tmp = create_node(0, "Greenlan0", "Fraser0", 666);
    add_ellem_end(1, "Greenlan", "Fraser", 2, tmp);
    add_ellem_end(2, "Greenlan1", "Fraser1", 21, tmp);
    add_ellem_end(3, "Greenlan2", "Fraser2", 12, tmp);
    add_ellem_end(4, "Greenlan3", "Fraser3", 23, tmp);
    while (tmp != NULL) {
        printf("\n%d\n", tmp->index);
        printf("%s -", tmp->element.island1);
        printf("%s, ", tmp->element.island2);
        printf("%d", tmp->element.distance);
        tmp = tmp -> next;
    }
    close(fl);
}

