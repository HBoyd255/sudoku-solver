#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint16_t checkMasks[10] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};

#define ROW_NUMBER(i) i / 9
#define COLUMN_NUMBER(i) i % 9
#define GRID_NUMBER(i) ((i / 3) % 3) + ((i / 27) * 3)

uint16_t rowChecks[9] = {0};
uint16_t columnChecks[9] = {0};
uint16_t gridChecks[9] = {0};

typedef struct {
    uint8_t value;
    uint8_t is_clue;

    uint16_t *rowChecker;
    uint16_t *columnChecker;
    uint16_t *gridChecker;

} cell_t;

#define CELL_INIT                \
    (cell_t){.value = 0,         \
             .is_clue = 0,       \
             .rowChecker = 0,    \
             .columnChecker = 0, \
             .gridChecker = 0}

typedef struct {
    cell_t cells[81];
} sudoku_t;

void printCheckCode(uint16_t data) {
    for (uint8_t i = 0; i < 9; i++) {
        printf("%c", ((data & 1)) ? '1' + i : '.');

        data = data >> 1;
    }
}

void printSudokuString(char *sudokuString) {
    char cell;

    for (uint8_t i = 0; i < 82; i++) {
        cell = sudokuString[i];

        uint8_t numerical = cell - '0';

        if (numerical > 9) {
            cell = ' ';
        }

        printf("%c", cell);

        if (!((i + 1) % 9)) {
            printf("\n");
        } else if (!((i + 1) % 3)) {
            printf("|");
        }
        if ((i + 1) == 27 || (i + 1) == 54) {
            printf("---+---+---\n");
        }
    }
}
void printSudoku(sudoku_t *sudoku) {
    for (uint8_t i = 0; i < 81; i++) {
        printf("%d", sudoku->cells[i].value);

        if (!((i + 1) % 9)) {
            printf("\n");
        } else if (!((i + 1) % 3)) {
            printf("|");
        }
        if ((i + 1) == 27 || (i + 1) == 54) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
    printf("Row         Column      Grid\n");
    for (uint8_t i = 0; i < 9; i++) {
        // printf("[%3d] [%3d] [%3d]\n", rowChecks[i], columnChecks[i],
        //        gridChecks[i]);

        printf("[");
        printCheckCode(rowChecks[i]);
        printf("] [");
        printCheckCode(columnChecks[i]);
        printf("] [");
        printCheckCode(gridChecks[i]);
        printf("]");
        printf("\n");
    }
}

void initialiseSudoku(sudoku_t *sudoku, char *sudokuString) {
    char cellChar;

    for (uint8_t i = 0; i < 81; i++) {
        cellChar = sudokuString[i];
        cell_t *cell = &sudoku->cells[i];

        *cell = CELL_INIT;

        uint8_t numerical = cellChar - '0';

        cell->rowChecker = &rowChecks[ROW_NUMBER(i)];
        cell->columnChecker = &columnChecks[COLUMN_NUMBER(i)];
        cell->gridChecker = &gridChecks[GRID_NUMBER(i)];

        if (numerical <= 9) {
            cell->value = numerical;
            cell->is_clue = 1;

            *cell->rowChecker |= checkMasks[numerical];
            *cell->columnChecker |= checkMasks[numerical];
            *cell->gridChecker |= checkMasks[numerical];
        }
    }
}

int main() {
    // https://en.wikipedia.org/wiki/sudoku
    static char *inputSudokuString =
        "53##7####"
        "6##195###"
        "#98####6#"
        "8###6###3"
        "4##8#3##1"
        "7###2###6"
        "#6####28#"
        "###419##5"
        "####8##79";

    printSudokuString(inputSudokuString);

    static sudoku_t sudoku;

    initialiseSudoku(&sudoku, inputSudokuString);

    printf("\n\n");

    printSudoku(&sudoku);
}
