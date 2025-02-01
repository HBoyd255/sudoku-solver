#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSudokuString(char *sudokuString) {
    char cell;

    for (uint8_t i = 1; i < 82; i++) {
        cell = sudokuString[i - 1];

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

void numberSudokuCells(char *sudoku) {
    // Row number
    printf("Rows\n");
    for (uint8_t i = 0; i < 81; i++) {
        printf("%2d", i / 9);
        if (!((i + 1) % 9)) {
            printf("\n");
        }
    }

    // Column number
    printf("\nColumns\n");
    for (uint8_t i = 0; i < 81; i++) {
        printf("%2d", i % 9);
        if (!((i + 1) % 9)) {
            printf("\n");
        }
    }

    // Grid number
    printf("\nGrids\n");
    for (uint8_t i = 0; i < 81; i++) {
        // printf("%2d", (i / 3) % 3);
        printf("%2d", ((i / 3) % 3) + ((i / 27) * 3));

        if (!((i + 1) % 9)) {
            printf("\n");
        }
    }
}

typedef struct {
    uint8_t value;
    uint8_t fixed;

    uint16_t *rowChecker;
    uint16_t *columnChecker;
    uint16_t *gridChecker;

} cell_t;

typedef struct {
    cell_t cells[81];
} sudoku_t;

#define CREATE_SUDOKU

void main() {
    // https://en.wikipedia.org/wiki/sudoku
    static char *inputSudoku =
        "53##7####"
        "6##195###"
        "#98####6#"
        "8###6###3"
        "4##8#3##1"
        "7###2###6"
        "#6####28#"
        "###419##5"
        "####8##79";

    static sudoku_t sudoku;

    printSudokuString(inputSudoku);

}
