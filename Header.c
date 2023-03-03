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

    char cfchar,                // Actual char 
         bfchar;                // Before char

    float dfactor = 1;

    int index,         // Auxiliar, store index of variable in array
        buffer_pt = 0, // Buffer position of char in string
        scounter = 0,  // s1, s2, s3, ..., si
        acounter = 0,  // a1, a2, a3, ..., ai
        vnumber = 0,   // Store de var value integer
        dnumber = 0,   // Store de var value decimal
        bindex = 0,    // Base var index
        digitc = 0;    // Number digit counter

    short negative_factor = 1;  // 1 to positive -1 to negative, for each number
    
    bool an_varpart = false,    // If an variable name is in analisys 
         is_solution = false,   // Verify if is analising a solution
         dec_part = false,
         zline = true;          // Verify if is mounting a zline

    // Get maximize or minimize (a || i)
    fseek(problem_set, 1, SEEK_CUR);
    tableaux->mode = getc(problem_set) == 'a' ? MAXIMIZE : MINIMIZE;
    fseek(problem_set, 9, SEEK_SET);

    while (cfchar != EOF) {
        cfchar = getc(problem_set);

        if (cfchar == ' ' || cfchar == '\t') continue;

        if (cfchar == '.' && !an_varpart) {
            dec_part = true;
            digitc++;
        } else if (isdigit(cfchar) && !an_varpart) {
            if(dec_part) {
                dnumber = (dnumber * 10) + (cfchar - '0');
                dfactor *= 10;
            }
            else 
                vnumber = (vnumber * 10) + (cfchar - '0');

            digitc++;

            if (digitc > tableaux->vstrl) tableaux->vstrl = digitc;
        }
        else if (cfchar == '<' || cfchar == '>' || cfchar == '=' || cfchar == '\n' || cfchar == '+' || cfchar == '-' || cfchar == EOF)
        {
            index = FindIndex(tableaux->variables, tableaux->variables[tableaux->nvars], tableaux->nvars);

            if((cfchar == '\n' || cfchar == EOF) && is_solution) {
                tableaux->solutions[tableaux->nexps] = vnumber * negative_factor;

                if(cfchar == EOF) break;
            }

            if (an_varpart && index == -1) index = tableaux->nvars++;
            if (an_varpart) {
                tableaux->values[tableaux->nexps][index] = (vnumber + (dnumber / dfactor * 1.0)) * negative_factor * (zline ? -1 : 1);
            }
            if (cfchar == '\n' && bfchar != '\n') {
                tableaux->nexps++;
                zline = false;
                is_solution = false;
            }

            if(cfchar == '=') {
                is_solution = true;

                sprintf(tableaux->bases[tableaux->nexps - 1], "%c%d", bfchar == '<' ? 's' : 'a', bfchar == '=' ? 1 + acounter : 1 + scounter);

                if (bfchar == '<' || bfchar == '>') {
                    sprintf(tableaux->variables[tableaux->nvars++], "s%d", 1 + scounter++);
                    tableaux->values[tableaux->nexps][tableaux->nvars - 1] = bfchar == '<' ? 1 : -1;
                }
                
                if (bfchar != '<') {
                    sprintf(tableaux->variables[tableaux->nvars++], "a%d", 1 + acounter++);
                    tableaux->values[tableaux->nexps][tableaux->nvars - 1] = 1;
                }
            }

            negative_factor = cfchar == '-' ? -1 : 1;
            buffer_pt = vnumber = digitc = dnumber = 0;
            dec_part = an_varpart = false;
            dfactor = 1;
        }
        else {
            if(cfchar == '-') continue;
            if (vnumber == 0) vnumber = 1;

            an_varpart = true;
            tableaux->variables[tableaux->nvars][buffer_pt++] = cfchar;
            tableaux->variables[tableaux->nvars][buffer_pt] = '\0';

            if(buffer_pt > tableaux->vstrl) tableaux->vstrl = buffer_pt;
        }

        bfchar = cfchar;
    }

    fclose(problem_set);

    return true;
}

void SolveTableaux(Tableaux tableaux) {
    printf("Solve...");
}

void PrintCollumnsSep(int qtd, char type[]) {
    for (size_t i = 0; i < qtd; i++)
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
    printf("%c\n", 206);
}

void ShowTableauxInfo(Tableaux tableaux) {
    printf("\n");
    printf("Method: %s\n", tableaux->mode == MAXIMIZE ? "Maximize" : "Miniminize");
    printf("Variables Amount: %d\n", tableaux->nvars);
    printf("Expressions Amount: %d\n", tableaux->nexps);
    printf("\nVariables: ");
    for (size_t i = 0; i < tableaux->nvars; i++)
        printf("%s%s", tableaux->variables[i], i != tableaux->nvars - 1 ? ", " : "\n");

    printf("Base: ");
    for (size_t i = 0; i < tableaux->nexps; i++)
        printf("%s%s", tableaux->bases[i], i != tableaux->nexps - 1 ? ", " : "\n");
    
}

void ShowTableaux(Tableaux tableaux) {
    int collumns = tableaux->nvars + 2;

    printf("\n");

    PrintCollumnsSep(collumns, "");

    printf("%c       Bs      ", 186);

    // Variables
    for (size_t i = 0; i < tableaux->nvars; i++) 
        printf("%c\t%s\t", 186, tableaux->variables[i]);
    printf("%c\tSl\t", 186);
    printf("%c\n", 186);
    
    PrintCollumnsSep(collumns, "");

    printf("%c\tz\t", 186);

    // Z line values
    for (size_t i = 0; i < tableaux->nvars; i++) {
        printf("%c\t%.2lf\t", 186, tableaux->values[0][i]);
    }
    printf("%c\t%.2lf\t", 186, tableaux->solutions[0]);
    printf("%c\n", 186);

    PrintCollumnsSep(collumns, "");

    // Values & base variables tag
    for (size_t i = 1; i <= tableaux->nexps; i++) {
        for (size_t j = 0; j < tableaux->nvars; j++) {
            if(j == 0)
                printf("%c\t%s\t", 186, tableaux->bases[i - 1]);

            printf("%c\t%.2lf\t", 186, tableaux->values[i][j]);
        }

        printf("%c\t%.2lf\t", 186, tableaux->solutions[i]);

        printf("%c\n", 186);
    } 

    PrintCollumnsSep(collumns, "");        
}

int FindIndex(char string_array[][BFF], char * string, int size) {
    for (size_t i = 0; i < size; i++) {
        if(!strcmp(string_array[i], string)) return i;
    }

    return -1;
}
