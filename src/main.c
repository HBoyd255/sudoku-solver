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
    "7##2###6"
    "#6####28#"
    "###419##5"
    "####8##79";

void printGrid() {
    for (uint8_t i = 1; i <= 81; i++) {
        printf("%2d ", i);

        if (!(i % 9)) {
            printf("\n");
        }
    }
}

void main() { printGrid(); }
