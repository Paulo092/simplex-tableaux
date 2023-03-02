#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"

void ping() {
    printf("\n ________  ________  ________   ________     \n");
    printf("|\\   __  \\|\\   __  \\|\\   ___  \\|\\   ____\\    \n");
    printf("\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\___|    \n");
    printf(" \\ \\   ____\\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\  ___  \n");
    printf("  \\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \n");
    printf("   \\ \\__\\    \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n");
    printf("    \\|__|     \\|_______|\\|__| \\|__|\\|_______|\n");
}

Tableaux NewTableaux() {
    return (Tableaux) calloc(1, sizeof(struct Tableaux));
}

void Alert(const int type, char * message) {
    printf("\n");
    switch (type) {
        case ERROR:
            printf("ERROR: ");
            break;
        
        case WARNING:
            printf("WARNING: ");
            break;

        case DEBUG:
            printf("DEBUG: ");
            break;
    }

    printf(message);
}

bool FileToTableaux(char * file_dir, Tableaux tableaux) {
    FILE * problem_set = fopen(file_dir, "r");

    if(!problem_set) {
        Alert(ERROR, "Nao foi possivel abrir o arquivo especificado.\n");
        return false;
    }

    char cfchar,        // Actual char 
         bfchar,        // Before char
         method;        // Maximize (a) ou Minimize (i)
    
    int index,          // Auxiliar, store index of variable in array
        buffer_pt = 0,  // Buffer position of letter string
        scounter = 0,   // s1, s2, s3, ..., si
        acounter = 0,   // a1, a2, a3, ..., ai
        vnumber = 0,    // Store de var value
        bindex = 0;     // Base var index

    short negative_factor = 1; // 1 to positive -1 to negative, for each number
    
    bool an_varpart = false; // If an variable name is in analisys 

    // Get maximize or minimize (a || i)
    fseek(problem_set, 1, SEEK_CUR);
    method = getc(problem_set);
    fseek(problem_set, 9, SEEK_SET);

    while ((cfchar = getc(problem_set)) != EOF) {
        if (cfchar == ' ' || cfchar == '\t' || cfchar == EOF) continue;

        if (cfchar == '-') {
            negative_factor = -1;
        } else if (isdigit(cfchar) && !an_varpart) {
            vnumber = (vnumber * 10) + (cfchar - '0');
        } else if (cfchar == '<' || cfchar == '>' || cfchar == '=' || cfchar == '\n' || cfchar == '+') {
            index = FindIndex(tableaux->variables, tableaux->variables[tableaux->nvars], tableaux->nvars);

            if (an_varpart && index == -1) index = tableaux->nvars++;
            if (an_varpart && tableaux->nexps != 0) tableaux->values[tableaux->nexps-1][index] = vnumber * negative_factor;
            if (cfchar == '\n' && bfchar != '\n') tableaux->nexps++;


            if(cfchar == '=') {
                switch (bfchar) {
                    case '<':
                        printf(">>%d\n", tableaux->nexps - 1);
                        sprintf(tableaux->bases[tableaux->nexps - 1], "s%d", 1 + scounter);

                        sprintf(tableaux->variables[tableaux->nvars++], "s%d", 1 + scounter++);
                        tableaux->values[tableaux->nexps - 1][tableaux->nvars - 1] = 1;
                        break;

                    case '>':
                        sprintf(tableaux->bases[tableaux->nexps - 1], "a%d", 1 + acounter);

                        sprintf(tableaux->variables[tableaux->nvars++], "s%d", 1 + scounter++);
                        tableaux->values[tableaux->nexps - 1][tableaux->nvars - 1] = -1;
                        sprintf(tableaux->variables[tableaux->nvars++], "a%d", 1 + acounter++);
                        tableaux->values[tableaux->nexps - 1][tableaux->nvars - 1] = 1;
                        break;
                    
                    default:
                        sprintf(tableaux->bases[tableaux->nexps - 1], "a%d", 1 + acounter);

                        sprintf(tableaux->variables[tableaux->nvars++], "a%d", 1 + acounter++);
                        tableaux->values[tableaux->nexps - 1][tableaux->nvars - 1] = 1;
                        break;
                }
            }

            buffer_pt = vnumber = 0;
            negative_factor = 1;
            an_varpart = false;
        }
        else {
            if (vnumber == 0) vnumber = 1;

            an_varpart = true;
            tableaux->variables[tableaux->nvars][buffer_pt++] = cfchar;
            tableaux->variables[tableaux->nvars][buffer_pt] = '\0';
        }

        bfchar = cfchar;
    }

    fclose(problem_set);

    return true;
}

void ShowTableaux(Tableaux tableaux) {
    int collumns = tableaux->nvars+1;

    for (size_t i = 0; i < collumns; i++) printf("+---------------");
    printf("+\n");
    printf("|\tBases\t");
    for (size_t i = 0; i < tableaux->nvars; i++) printf("|\t%s\t", tableaux->variables[i]);
    printf("|\n");
    for (size_t i = 0; i < collumns; i++) printf("+---------------");
    printf("+\n");

    for (size_t i = 0; i < tableaux->nexps; i++) {
        for (size_t j = 0; j < tableaux->nvars; j++) {
            if(j == 0) 
                printf("|\t%s\t", tableaux->bases[i]);
                printf("|\t%d\t", tableaux->values[i][j]);
        }
        printf("|\n");
    } 

    for (size_t i = 0; i < collumns; i++) printf("+---------------");
    printf("+\n");
        
}

int FindIndex(char string_array[][BFF], char * string, int size) {
    for (size_t i = 0; i < size; i++) {
        if(!strcmp(string_array[i], string)) return i;
    }

    return -1;
}
