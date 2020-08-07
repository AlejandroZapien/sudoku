#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PUZZLE_DIR "./puzzles/"
#define true 1
#define false 0

typedef struct Board {
    char **grid;
    int rows;
    int cols;
} Board;

Board allocate_board(int, int);
int print_board(Board);
int load_board(Board *, char *);
int free_board(Board *);
void display_usage(void);

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

void display_usage(void) {
    char cmd[20] = "ls ";
    char path[] = PUZZLE_DIR;
    strcat(cmd, path);
    printf("Specify a puzzle name. Usage: ./Sudoku s01a.txt\n");
    system(cmd);
}

Board allocate_board(int rows, int cols) {

    int i = 0;
    int j = 0;

    Board b;
    b.rows = rows;
    b.cols = cols;
    b.grid = calloc(b.rows, sizeof(char *));

    for(i = 0; i < b.rows; i++) {
        b.grid[i] = calloc(b.cols, sizeof(char));
        for(j = 0; j < b.cols; j++) {
            b.grid[i][j] = '0';
        }
    }
    
    return b;
}

int print_board(Board b) {
    int i = 0;
    int j = 0;

    putchar('\n');
    for(i = 0; i < b.rows; i++) {
        for(j = 0; j < b.cols; j++) {
            putchar(b.grid[i][j]);
        }
        putchar('\n');
    }

    return 1;
}

int load_board(Board *b, char *puzzle) {
    int i = 0;
    int j = 0;

    char buf[256];
    
    char puzzledir[50] = PUZZLE_DIR;
    strcat(puzzledir, puzzle);

    FILE *fp = fopen(puzzledir, "r");
    if(fp == NULL) { 
        printf("file not found: %s\n", puzzledir);
        return -1;
    }

    for(i = 0; i < b->rows; i++) {
        fgets(buf, sizeof(buf), fp); //get a line of numbers from the text file
        for(j = 0; j < b->cols; j++) {
           b->grid[i][j] = buf[j]; //fill cells with numbers from string 
        }
    }

    fclose(fp);

    return 1;
}

int free_board(Board *b) {
    
    int i = 0;

    for(i = 0; i < b->rows; i++) {
        free(b->grid[i]);
    }

    free(b->grid);
    return 1;
}

