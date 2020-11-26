#include <stdio.h>
#include <stdlib.h>

typedef struct variabile{
    char nome[20];
    int address;
    int val;
} VAR;

char * nome_file(char str[])
{
    int i = 0, asmfile = 0;
    while (str[i+3] != '\0') 
    {
        if (str[i] == '.' && str[i+1] == 'a' && str[i+2] == 's' && str[i+3] == 'm')
        {
            asmfile = 1;
        }
        i++;
    }
    if ((asmfile-1))
    {
        return NULL;
    }
    char *tmp = malloc((++i)*sizeof(char));
    i = 0;
    while(asmfile && str[i] != '.')
    {   
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '.';
    tmp[++i] = 'h';
    tmp[++i] = 'a';
    tmp[++i] = 'c';
    tmp[++i] = 'k';
    return tmp;
}

char * getCommand(char str[64])
{
    char * command = malloc(64*sizeof(char));
    char * tmp = command;

    

    return command;
}

int write_bit(FILE * fhack, int write[16])
{
    int i = 0;
    while(i != 16)
    {
        fprintf(fhack, "%d", write[i]);
        i++;
    }
    fprintf(fhack, "\n");
}

int *num_to_bit(int n){
    int *write = malloc(16*sizeof(int));
    int resto = 0, i = 15;
    while (n != 0)
    {
        resto = n % 2;
        n /= 2;
        write[i] = resto;
        i--;
    }
    return write;
}

int main(int argc, char **argv)
{
    FILE *fasm, *fhack;
    int *write = malloc(16*sizeof(int));
    char command[64], str[64];
    int i, comment, riga = 1;
    
    // esce se non inserisce argomenti
    if(argc < 2)
    {
        printf("Errore: inserire un argomento\n");
        return(-1);
    }

    fasm = fopen(argv[1], "r");
    char * nomefile = nome_file(argv[1]);
    // finisce il programma se l'argomento inserito non è valido
    if(nomefile == NULL)
    {
        printf("Errore: argomento non valido\n");
        return(0);
    }
    fhack = fopen(nomefile, "w");

    while(fgets(str, 64, fasm) != NULL)
    {
        
        i = 0;
        comment = 0;

        // pulisto dal comando prima
        for (int j = 0; command[j] != '\0'; j++)
            command[j] = NULL;

        // prendo il comando dalla riga letta
        // elimino commenti, \n e spazi
        while (str[i] != '\n')
        {   
            if (str[i] != '/' && str[i+1] != '/'){
                if ((comment-1) && (str[i] > 32 && str[i] < 125)) command[i] = str[i];
            }else
            {
                fgets(str, 64, fasm);
                i = -1;
                comment = 0;
            }

            i++;
        }
        command[i] = '\0';

        //printf("%s\n", command);
        int length = i;
        if(command[0] == '@') // a-istr
        {
            char * numero = &command[1];
            write = num_to_bit(atoi(numero));
            write_bit(fhack, write);
        }
        else if (command[1] == ';') //jump
        {
            // se 0;JMP salta sempre
            write[0] = 1;
            write[13] = 1;
            write[14] = 1;
            write[15] = 1;
            write_bit(fhack, write);
        }
        else if (command[1] == '=' || command[2] == '=') // c-istr
        {
            write[0] = 1;
            /*if(command[1] == 'D' || command[1] == 'M' || command[1] == 'A')
            {

            } else if(command[1] == '=')
            {
                //assign(command[0], &command[2]);
            }
            */
        }
        else if (command[0] == '(') //label
        {
            //label_istr(command);
        }
        else if (command[0] != NULL)
            printf("ERRORE: controlla la sintassi di %s a riga %d\n", command, riga);            

        riga++;
    }
    fclose(fasm);
    fclose(fhack);
    return(0);
}