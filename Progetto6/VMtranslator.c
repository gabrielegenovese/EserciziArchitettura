#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funz.h"

int main(int argc, char **argv)
{
    FILE *fvm, *fasm;
    char str[128];
    
    char c0[50], c1[50], c2[50];
    char *command[] = {c0, c1, c2};

    int riga = 1;
    COUNT c = inizializza();
    
    if(argc < 2)
    {
        printf("Errore: inserire un argomento\n");
        return(-1);
    }

    char * namefile = getNameFile(argv[1]);
    
    if(namefile == NULL)
    {
        printf("Errore: argomento non valido\n");
        return(-1);
    }

    fvm = fopen(argv[1], "r");
    fasm = fopen(namefile, "w");

    writeBootstrap(fasm);
    
    while(fgets(str, 128, fvm) != NULL)
    {
        getCommand(str, command);
        if (command[0][0] != '\0')
        {
            writeComment(fasm, command);
            exec_command(command[0], command[1], command[2], riga, fasm, c);
            riga++;
        }
    }

    fclose(fvm);
    fclose(fasm);
    return(0);
}