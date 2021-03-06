#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funz.h"

char *nome_file(char str[])
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

char *getCommand(char str[128])
{
    char * command = malloc(50*sizeof(char));
    int i = 0, z = 0;

    while (str[i] != '\n')
    {
        if (str[i] == '/' && str[i+1] == '/')
        {
            command[z] = '\0';
            return command;
        }
        else
        {
            if (str[i] != ' ') command[z] = str[i];
            else z--;
        }
        z++;
        i++;
    }
    command[z-1] = '\0';
    return command;
}

void write_bit(FILE * fhack, int write[16])
{
    for (int i = 0; i < 16; i++)
        fprintf(fhack, "%d", write[i]);
    fprintf(fhack, "\n");
}

int *num_to_bit(int n)
{
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

int pow_custom(int n, int e)
{
    int r = 1;
    
    while(e != 0)
    {
        r *= n;
        e--;
    }
    return r;
}

int atoi_custom(char * num)
{
    int numero = 0;
    while(num[0] != '\0')
    {
        if(((int)(num[0])-48) < 0 || ((int)(num[0])-48) > 9) return 0;
        numero += ((int)(num[0])-48) * (pow_custom(10,(strlen(num)-1)));
        num++;
    }
    return numero;
}

void error(char *c, int riga)
{
    printf("Errore: controlla la sintassi di %s a riga %d\n", c, riga);
}

int isStringEqual(char * p1, char * p2)
{
    int length1 = 0, i = 0;
    char * tmp = p1;
    while (tmp[i] != '\0')
    {
        length1++;
        i++;
    }

    int length2 = 0;
    i = 0;
    tmp = p2;
    while (tmp[i] != '\0')
    {
        length2++;
        i++;
    }

    if (length1 != length2)
        return 0;

    for (int i = 0; i < length1; i++)
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
    else if (isStringEqual(op, (char *)"1"))
    {
        for (int i = 4; i <= 9; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"-1"))
    {
        write[4] = 1;
        write[5] = 1;
        write[6] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"D"))
    {
        write[6] = 1;
        write[7] = 1;
    }
    else if (isStringEqual(op, (char *)"A") || isStringEqual(op, (char *)"M"))
    {
        if(op[0]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
    }
    else if (isStringEqual(op, (char *)"!D"))
    {
        write[6] = 1;
        write[7] = 1; 
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"!A") || isStringEqual(op, (char *)"!M"))
    {
        if(op[1]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"-D"))
    {
        write[6] = 1;
        write[7] = 1;
        write[8] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"-A") || isStringEqual(op, (char *)"-M"))
    {
        if(op[1]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
        write[8] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"D+1"))
    {
        for (int i = 5; i <= 9; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"A+1") || isStringEqual(op, (char *)"M+1"))
    {
        if(op[0]=='M') write[3] = 1;
        for (int i = 4; i <= 9; i++)
            write[i] = 1;
        write[6] = 0;
    }
    else if (isStringEqual(op, (char *)"D-1"))
    {
        for (int i = 6; i <= 8; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"A-1") || isStringEqual(op, (char *)"M-1"))
    {
        if(op[0]=='M') write[3] = 1;
        write[4] = 1;
        write[5] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"D+A") || isStringEqual(op, (char *)"D+M"))
    {
        if(op[2]=='M') write[3] = 1;
        write[8] = 1;
    }
    else if (isStringEqual(op, (char *)"D-A") || isStringEqual(op, (char *)"D-M"))
    {
        if(op[2]=='M') write[3] = 1;
        write[5] = 1;
        write[8] = 1;
        write[9] = 1;
    }
    else if (isStringEqual(op, (char *)"A-D") || isStringEqual(op, (char *)"M-D"))
    {
        if(op[0]=='M') write[3] = 1;
        for (int i = 7; i <= 9; i++)
            write[i] = 1;
    }
    else if (isStringEqual(op, (char *)"D&A") || isStringEqual(op, (char *)"D&M"))
    {
        if(op[2]=='M') write[3] = 1;
    }
    else if (isStringEqual(op, (char *)"D|A") || isStringEqual(op, (char *)"D|M"))
    {
        if(op[2]=='M') write[3] = 1;
        write[5] = 1;
        write[7] = 1;
        write[9] = 1;
    }
    else return 0;

    return 1;
}

void exec_command(char *command, int riga, int write[16], FILE * fhack, VAR var)
{
    int do_write = 1;
    if (command[0] == '@') // a-istr
    {
        char * numero = &command[1]; // es. @17
        if (command[1] == 'R' && (command[2] == '0' || (command[2] == '1') || (command[2] == '2') || (command[2] == '3') || (command[2] == '4') || (command[2] == '5') || (command[2] == '6') || (command[2] == '7') || (command[2] == '8') || (command[2] == '9')))
            numero = &command[2];  // es. @R1

        int num = atoi_custom(numero);
 
        if (num == 0 && numero[0] != '0')
        {
            while (var != NULL)
            {
                if(isStringEqual(var->nome, numero))
                {
                    num = var->val;
                    break;
                }
                var = var->next;
            }
        }

        if (isStringEqual(numero, (char *)"SCREEN"))
        {
            num = 16384;
        }
        else if (isStringEqual(numero, (char *)"KBD"))
        {
            num = 24576;
        }
        else if (isStringEqual(numero, (char *)"SP"))
        {
            num = 0;
        }
        else if (isStringEqual(numero, (char *)"LCL"))
        {
            num = 1;
        }
        else if (isStringEqual(numero, (char *)"ARG"))
        {
            num = 2;
        }
        else if (isStringEqual(numero, (char *)"THIS"))
        {
            num = 3;
        }
        else if (isStringEqual(numero, (char *)"THAT"))
        {
            num = 4;
        }

        write = num_to_bit(num);
    }
    else if (command[1] == ';') //jump
    {   
        write = malloc(16*sizeof(int));
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
        else if (comp == '0')
        {
            write[4] = 1;
            write[6] = 1;
            write[8] = 1;
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
        write = malloc(16*sizeof(int));
        
        write[0] = 1;
        write[1] = 1;
        write[2] = 1;

        char assegna = command[0];
        char * op = &command[2];

        if(command[1] == '=')
        {
            if(assegnamento(write, assegna, op)){}
            else error(command, riga);
        }
        else if(command[2] == '=')
        {
            op = &command[3];
            if(assegnamento(write, assegna, op)){}
            else error(command, riga);
            assegna = command[1];
            if (assegnamento(write, assegna, op)){}
            else error(command, riga);
        }
    }
    else if (command[0] == '(') //label
    {
        do_write = 0;
    }
    else error(command, riga);

    if(do_write) write_bit(fhack, write);
}

VAR newVariable(VAR head, char * name, int val)
{
    VAR tmp = head;
    if(head == NULL)
    {
        head = malloc(sizeof(VAR));
        head->nome = malloc(50*sizeof(char));
        strcpy(head->nome, name);
        head->val = val;
        head->next = NULL;
        return head;
    }
    while (head->next != NULL)
    {
        head = head->next;
    }

    head->next = malloc(sizeof(VAR));
    head->next->nome = malloc(50*sizeof(char));
    strcpy(head->next->nome, name);
    head->next->val = val;
    head->next->next = NULL;
    return tmp;
}

VAR getLabel(VAR variables, FILE * fasm)
{
    int riga = 1;
    char * command, str[128];
    
    while (fgets(str, 128, fasm) != NULL)
    {
        command = getCommand(str);
        if(command[0] == '(')
        {
            int length1 = 0, i = 0;
            char * tmp = &command[1];
            while (tmp[i] != '\0')
                i++;

            if(tmp[i-1] == ')')
            {
                tmp[i-1] = '\0';
                variables = newVariable(variables, &tmp[0], riga-1);
            }
            else error(command, riga);
        }
        if(command[0] == '0' || command[0] == 'A' || command[0] == 'M' || command[0] == 'D' || command[0] == '@')
            riga++;
        
        free(command);
    }

    fclose(fasm);
    return variables;
}

VAR getVar(VAR variables, FILE * fasm)
{
    int n_val = 16;
    char * command, str[128];
    
    while (fgets(str, 128, fasm) != NULL)
    {
        command = getCommand(str);
        if (command[0] != 10 && command[0] != 13)
        {
            if(command[0] == '@')
            {
                char * var = &command[1];
                VAR tmp = variables;
                int to_store = 1;
                while (tmp != NULL)
                {
                    if(isStringEqual(var, tmp->nome))
                        to_store = 0;
                    tmp = tmp->next;
                }
                if (to_store && var[0] != '0' && !atoi_custom(&command[2]) && var[1] != '0' && !atoi_custom(var) && !isStringEqual(var, (char *)"SCREEN") && !isStringEqual(var, (char *)"KBD") && !isStringEqual(var, (char *)"SP") && !isStringEqual(var, (char *)"ARG") && !isStringEqual(var, (char *)"LCL") && !isStringEqual(var, (char *)"THIS") && !isStringEqual(var, (char *)"THAT"))
                {
                    variables = newVariable(variables, var, n_val);
                    n_val++;
                }
                
            }
        }
        free(command);
    }

    fclose(fasm);
    return variables;
}
