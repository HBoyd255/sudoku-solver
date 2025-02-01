#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/sudoku
char *inputSudoku =
    "53##7####"
    "6##195###"
    "#98####6#"
    "8###6###3"
    "4##8#3##1"
    "7###2###6"
    "#6####28#"
    "###419##5"
    "####8##79";

void printSudoku(char *sudoku) {
    char cell;

    for (uint8_t i = 1; i <= 81; i++) {
        cell = sudoku[i - 1];

        if (cell == '#') {
            cell = ' ';
        }

        printf("%c", cell);

        if (!(i % 9)) {
            printf("\n");
        } else if (!(i % 3)) {
            printf("|");
        }
        if (i == 27 || i == 54) {
            printf("---+---+---\n");
        }
    }
}

void main() { printGrid(inputSudoku); }
