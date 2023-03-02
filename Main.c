#include <stdio.h>
#include <stdlib.h>

#include "Header.h"

int main(int argc, char const *argv[]) {
    // ping();
    Tableaux tbl = NewTableaux();

    if(!FileToTableaux((char *) argv[1], tbl)) exit(1);

    // tbl->nexps = 5;

    ShowTableaux(tbl);

    for (size_t i = 0; i <= tbl->nexps; i++) {
        printf(" %d ->", tbl->solutions[i]);
    }
        printf("\n>>> %d", tbl->nexps);
    

    return 0;
}
