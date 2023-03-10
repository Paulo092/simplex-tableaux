#include <stdio.h>
#include <stdlib.h>

#include "Header.h"

int main(int argc, char const *argv[]) {
    // ping();
    Tableaux tbl = NewTableaux();

    if(!FileToTableaux((char *) argv[1], tbl)) exit(1);

    // tbl->nexps = 5;

    ShowTableaux(tbl);

    ShowTableauxInfo(tbl);
    printf("\nBigger String: %d\n\n", tbl->vstrl);
    // printf("\nBigger String: %d\n\n", getBiggerString(tbl));

    return 0;
}
