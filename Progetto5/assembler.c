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

char * getCommand(FILE * fasm, char str[64])
{
    char * command = malloc(64*sizeof(char));
    char * tmp = command;
    int i = 0, z = 0, comment = 0;

    while (str[i] != '\n')
    {
        command[z+1] = '\0';
        if (str[i] == '/' && str[i+1] == '/')
            return command;
        else
        {
            if (str[i] != ' ') command[z] = str[i];
            else z--;
        }
        z++;
        i++;
    }

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

void error(char *c, int riga)
{
    printf("Errore: controlla la sintassi di %c a riga %d\n", c, riga);
}

int isStringEqual(char * p1, char * p2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if(p1[i] != p2[i])
            return 0;
    }
    return 1;
}

int assegnamento(int *write, char c, char *op)
{

    if (c == 'A')
        write[10] = 1;
    else if (c == 'D')
        write[11] = 1;
    else if (c == 'M')
        write[12] = 1;

    if (op[0] == '0')
    {
        write[4] = 1;
        write[6] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"1", 1))
    {
        for (int i = 4; i <= 9; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"-1", 2))
    {
        write[4] = 1;
        write[5] = 1;
        write[6] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"D", 1))
    {
        write[6] = 1;
        write[7] = 1;
    }
    else if (isStringEqual(op, (char *)"A", 1) || isStringEqual(op, (char *)"M", 1))
    {
        if(op[0]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
    }
    else if (isStringEqual(op, (char *)"!D", 2))
    {
        write[6] = 1;
        write[7] = 1; 
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"!A", 2) || isStringEqual(op, (char *)"!M", 2))
    {
        if(op[1]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"-D", 2))
    {
        write[6] = 1;
        write[7] = 1;
        write[8] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"-A", 2) || isStringEqual(op, (char *)"-M", 2))
    {
        if(op[1]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
        write[8] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"D+1", 3))
    {
        for (int i = 5; i <= 9; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"A+1", 3) || isStringEqual(op, (char *)"M+1", 3))
    {
        if(op[0]=='M') write[3] = 1;
        for (int i = 4; i <= 9; i++)
            write[i] = 1;
        write[6] = 0;
    }
    else if (isStringEqual(op, (char *)"D-1", 3))
    {
        for (int i = 6; i <= 8; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"A-1", 3) || isStringEqual(op, (char *)"M-1", 3))
    {
        if(op[0]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"D+A", 3) || isStringEqual(op, (char *)"D+M", 3))
    {
        if(op[2]=='M') write[3] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"D-A", 3) || isStringEqual(op, (char *)"D-M", 3))
    {
        if(op[2]=='M') write[3] = 1;
        write[5] = 1;
        write[8] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"A-D", 3) || isStringEqual(op, (char *)"M-D", 3))
    {
        if(op[0]=='M') write[3] = 1;
        for (int i = 7; i <= 9; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"D&A", 3) || isStringEqual(op, (char *)"D&M", 3))
        if(op[2]=='M') write[3] = 1;
    else if (isStringEqual(op, (char *)"D|A", 3) || isStringEqual(op, (char *)"D|M", 3))
    {
        if(op[2]=='M') write[3] = 1;
        write[5] = 1;
        write[7] = 1;
        write[9] = 1;
    }
    else return 0;
    
    return 1;
}

void exec_command(char command[64], int riga, int write[16], FILE * fhack)
{
    if(command[0] == '@') // a-istr
    {
        char * numero = &command[1];
        write = num_to_bit(atoi(numero));
    }
    else if (command[1] == ';') //jump
    {   
        write[0] = 1;
        write[1] = 1;
        write[2] = 1;
        
        char comp = command[0];
        char *jmp = &command[2];
        if (comp == 'A')
        {
            write[4] = 1;
            write[5] = 1;
        }
        else if (comp == 'D')
        {
            write[6] = 1;
            write[7] = 1;
        }
        else if (comp == 'M')
        {
            write[3] = 1;
            write[4] = 1;
            write[5] = 1;
        }
        else error(command, riga);

        if (jmp[0] == 'J')
        {
            if (jmp[1] == 'G' && jmp[2] == 'T')
                write[15] = 1;
            else if (jmp[1] == 'E' && jmp[2] == 'Q')
                write[14] = 1;
            else if (jmp[1] == 'G' && jmp[2] == 'E')
            {
                write[14] = 1;
                write[15] = 1;
            }
            else if (jmp[1] == 'L' && jmp[2] == 'T')
                write[13] = 1;
            else if (jmp[1] == 'N' && jmp[2] == 'E')
            {
                write[13] = 1;
                write[15] = 1;
            }
            else if (jmp[1] == 'L' && jmp[2] == 'E')
            {
                write[13] = 1;
                write[14] = 1;
            }
            else if (jmp[1] == 'M' && jmp[2] == 'P')
            {
                write[13] = 1;
                write[14] = 1;
                write[15] = 1;
            }
            else error(command, riga);
        }
        else error(command, riga);
    }
    else if (command[1] == '=' || command[2] == '=') // c-istr
    {
        write[0] = 1;
        write[1] = 1;
        write[2] = 1;

        if(command[1] == '=')
            if(assegnamento(&write[0], command[0], &command[2])){}
            else error(command, riga);
        else if(command[2] == '=')
        {
            if(assegnamento(&write[0], command[0], &command[3])){}
            else error(command, riga);
            if (assegnamento(&write[0], command[1], &command[3])){}
            else error(command, riga);
        }
    }
    else if (command[0] == '(') //label
    {
        fprintf(fhack, "label istr");
        //label_istr(command);
    }
    else if (command[0] != NULL) error(command, riga);

    write_bit(fhack, write);
}

int main(int argc, char **argv)
{
    FILE *fasm, *fhack;
    int *write = malloc(16*sizeof(int));
    char *command, str[64];
    int riga = 1;
    
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
        command = malloc(64*sizeof(char));
        command = getCommand(fasm, str);
        printf("%s\n", command);
        
        exec_command(command, riga, write, fhack);

        free(command);
        riga++;
    }
    //fprintf(fhack, "END");
    fclose(fasm);
    fclose(fhack);
    return(0);
}