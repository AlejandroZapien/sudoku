#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"
int main(int argc, char *argv[]) {
    int rc = 0;
    char *puzzle = NULL;

    if(argc != 2) {
        display_usage();
        return -1;
    } else {
        puzzle = argv[1];
    }

    Board b = allocate_board(9,9);
    rc = load_board(&b, puzzle);
    if(rc < 0) {
        printf("Failed to load board\n");
        display_usage();
        return -1;
    }
    print_board(b);
    free_board(&b);
    return 0;
}


