#pragma once

#include <stdbool.h>

#define CLS 100
#define LNS 100
#define BFF 100

#define ERROR 0
#define WARNING 1
#define DEBUG 2

#define MINIMIZE 0
#define MAXIMIZE 1

typedef struct Tableaux{
    int mode;

    char variables[CLS][BFF];
    char bases[LNS][BFF];
    
    int values[LNS][CLS];
    int solutions[CLS];
    int nvars, nexps;
} * Tableaux;


// File Manipulation
bool FileToTableaux(char * file_dir, Tableaux tableaux);

// Tableaux Operations
Tableaux NewTableaux();

// Utils
void ShowTableaux(Tableaux tableaux);
void Alert(const int type, char *message);
int FindIndex(char string_array[][BFF], char *value, int size);
void printCL(int qtd);
void ping();
