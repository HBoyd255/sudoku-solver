#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A struct to represent a cell within a Sudoku. This stores the value of
 * the cell, whether the value was provided as a clue (and therefor should not
 * be edited), as well as 3 pointers to check codes, used to calculate the
 * presence of other numbers within the cell's row, column and group.
 */
typedef struct {
    uint8_t value;
    uint8_t is_clue;

    uint16_t *rowCheck_ptr;
    uint16_t *columnCheck_ptr;
    uint16_t *gridCheck_ptr;
} cell_t;

/**
 * @brief A strucy representing the Sudoku.
 *
 * The Sudoku contains an array of 81 cells, as well as  27 check codes. 9 for
 * each row, column, and group.
 *
 * A check code is a 9 bit unsigned integer value, where each bit represents
 * whether each number is present or not.
 *
 * For example, a row with the check code "0b001001101" would contain a 1,
 * 3,4 and 7. The locates of each number are not stored by each check code.
 */
typedef struct {
    // An array of all 81 cells making up the Sudoku.
    cell_t cells[81];

    // An array of pointers, to cells that need to be solved.This allows for
    // better traversal while solving the Sudoku, without the need to skip over
    // the clues.
    cell_t *nonClueCells_ptrarr[81];

    // The number of cells that need solving.
    uint8_t nonClueCount;

    // Arrays of pointers to all 27 check codes.
    uint16_t rowCheck_arr[9];
    uint16_t columnCheck_arr[9];
    uint16_t gridCheck_arr[9];
} sudoku_t;

// Gets the row number of a cell(both 0-indexed)
#define ROW_NUMBER(i) i / 9

// Gets the column number of a cell(both 0-indexed)
#define COLUMN_NUMBER(i) i % 9

// Gets the grid number of a cell(both 0-indexed)
#define GRID_NUMBER(i) ((i / 3) % 3) + ((i / 27) * 3)

// An array of masks for check codes.
static const uint16_t checkMasks[10] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};

/**
 * @brief Prints the value of a check code to the terminal, by replacing each
 * bit with the corrsponding value.
 *
 * For example the check code "0b001001101" would be printed as "1.34..7.."
 *
 * @param checkCodeValue The value of the check code to print.
 */
static void printCheckCode(uint16_t checkCodeValue) {
    for (uint8_t i = 0; i < 9; i++) {
        printf("%c", ((checkCodeValue & 1)) ? '1' + i : '.');

        checkCodeValue = checkCodeValue >> 1;
    }
}

static void printSudokuString(char *sudokuString) {
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

static void printSudoku(sudoku_t *sudoku) {
    printf("%d cells to solve.\n", sudoku->nonClueCount);
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
        printf("[");
        printCheckCode(sudoku->rowCheck_arr[i]);
        printf("] [");
        printCheckCode(sudoku->columnCheck_arr[i]);
        printf("] [");
        printCheckCode(sudoku->gridCheck_arr[i]);
        printf("]");
        printf("\n");
    }
}

static void printSudokuSimple(sudoku_t *sudoku) {
    for (uint8_t i = 0; i < 81; i++) {
        if (sudoku->cells[i].value) {
            printf("%d", sudoku->cells[i].value);
        } else {
            printf(".");
        }

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

static void initialiseSudoku(sudoku_t *sudoku, char *sudokuString) {
    // Set all the check codes to 0.
    for (uint8_t i = 0; i < 9; i++) {
        sudoku->rowCheck_arr[i] = 0;
        sudoku->columnCheck_arr[i] = 0;
        sudoku->gridCheck_arr[i] = 0;
    }

    sudoku->nonClueCount = 0;

    for (uint8_t i = 0; i < 81; i++) {
        cell_t *cell = &sudoku->cells[i];

        uint8_t numerical = sudokuString[i] - '0';

        cell->rowCheck_ptr = &sudoku->rowCheck_arr[ROW_NUMBER(i)];
        cell->columnCheck_ptr = &sudoku->columnCheck_arr[COLUMN_NUMBER(i)];
        cell->gridCheck_ptr = &sudoku->gridCheck_arr[GRID_NUMBER(i)];

        if (numerical <= 9) {
            cell->value = numerical;
            cell->is_clue = 1;

            *cell->rowCheck_ptr |= checkMasks[numerical];
            *cell->columnCheck_ptr |= checkMasks[numerical];
            *cell->gridCheck_ptr |= checkMasks[numerical];
        } else {
            cell->value = 0;
            cell->is_clue = 0;

            sudoku->nonClueCells_ptrarr[sudoku->nonClueCount] = cell;

            sudoku->nonClueCount++;
        }
    }
}

int main() {
    system("cls");

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

    // printSudokuString(inputSudokuString);

    static sudoku_t sudoku;

    initialiseSudoku(&sudoku, inputSudokuString);

    // printf("\n\n");

    // printSudoku(&sudoku);

    printSudokuSimple(&sudoku);
}
