#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funz.h"

int main(int argc, char **argv)
{
    FILE *fasm, *fhack;
    int write[16];
    char *command = NULL, str[128];
    VAR variables = NULL;
    int riga = 1;
    
    // esce se non inserisce argomenti
    if(argc < 2)
    {
        printf("Errore: inserire un argomento\n");
        return(-1);
    }

    fasm = fopen(argv[1], "r");
    char * nomefile = nome_file(argv[1]);
    // esce se l'argomento inserito non è un file asm
    if(nomefile == NULL)
    {
        printf("Errore: argomento non valido\n");
        return(0);
    }
    fhack = fopen(nomefile, "w");

    variables = getLabel(variables, fasm);

    fasm = fopen(argv[1], "r");
    variables = getVar(variables, fasm);

    fasm = fopen(argv[1], "r");

    while(fgets(str, 128, fasm) != NULL)
    {
        command = getCommand(str);
        
        if (command[0] != 13 && command[0] != '\0')
            exec_command(command, riga, write, fhack, variables);

        free(command);
        riga++;
    }
    free(variables);
    fclose(fasm);
    fclose(fhack);
    return(0);
}