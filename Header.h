#pragma once

#include <stdbool.h>

#define CLS 100
#define LNS 100
#define BFF 100

#define ERROR 0
#define WARNING 1
#define DEBUG 2

typedef struct Tableaux{
    char variables[CLS][BFF];
    int values[LNS][CLS];
    int solutions[LNS][CLS];
    int bases[LNS][CLS];
    int nvars, nexps;
} * Tableaux;


// File Manipulation
bool FileToTableaux(char * file_dir, Tableaux tableaux);

// Tableaux Operations
Tableaux NewTableaux();

// Utils
void ShowTableaux(Tableaux tableaux);
void Alert(const int type, char * message);
int FindIndex(char string_array[][BFF], char * value, int size);
void ping();
