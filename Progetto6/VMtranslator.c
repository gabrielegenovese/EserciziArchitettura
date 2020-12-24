#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getNameFile(char str[])
{
    int i = 0, asmfile = 0;
    while (str[i+2] != '\0') 
    {
        if (str[i] == '.' && str[i+1] == 'v' && str[i+2] == 'm')
            asmfile = 1;
        i++;
    }

    if ((asmfile-1))
        return NULL;

    char *tmp = malloc((++i)*sizeof(char));
    i = 0;
    while(str[i] != '.')
    {   
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '.';
    tmp[++i] = 'a';
    tmp[++i] = 's';
    tmp[++i] = 'm';
    return tmp;
}

char** getCommand(char str[128])
{
    char *command[3];
    for (int i = 0; i < 3; i++)
        command[i] = malloc(20*sizeof(char));
    
    int y = 0, z = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '/' && str[i+1] == '/')
        {
            for (int i = 0; i < 3; i++)
                command[i][z] = '\0';
            
            return command;
        }
        else
        {
            if (str[i] != ' ')
            {
                command[y][z] = str[i];
                z++;
            }
            else
            {
                command[y][z] = '\0';
                y++;
                z = 0;
            }
        }
    }
    command[y][z] = '\0';
    return command;
}

void writeBootstrap(FILE *fasm)
{
    fprintf(fasm, "//bootstrap\n");
    fprintf(fasm, "@256\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "M=D\n");
}

void incStack(FILE *fasm)
{
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D\n");
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "M=M+1\n");
}

void error(char c[], int riga)
{
    printf("Errore: controlla la sintassi di %s a riga %d\n", c, riga);
}

void exec_command(char **command, int riga, FILE *fasm)
{

    incStack(fasm);
}

int main(int argc, char **argv)
{
    FILE *fvm, *fasm;
    char *command[3], str[128];
    int riga = 1;
    
    // esce se non inserisce argomenti
    if(argc < 2)
    {
        printf("Errore: inserire un argomento\n");
        return(-1);
    }

    char * namefile = getNameFile(argv[1]);
    // esce se l'argomento inserito non è un file vm
    if(namefile == NULL)
    {
        printf("Errore: argomento non valido\n");
        return(0);
    }
    
    fvm = fopen(argv[1], "r");
    fasm = fopen(namefile, "w");

    writeBootstrap(fasm);
    
    while(fgets(str, 128, fvm) != NULL)
    {
        command = getCommand(str);
        
        if (command[0][0] != 13 && command[0][0] != '\0')
        {
            fprintf(fasm, "//writing command = %s\n", command);
            exec_command(command, riga, fasm);
        }

        free(command);
        riga++;
    }

    fclose(fvm);
    fclose(fasm);
    return(0);
}