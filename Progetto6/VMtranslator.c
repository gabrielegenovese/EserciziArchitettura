#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct count
{
    int eq;
    int gt;
    int lt;
} *COUNT;

COUNT inizialize()
{
    COUNT c = malloc(sizeof(COUNT));
    c->eq=0;
    c->gt=0;
    c->lt=0;
}

void getCommand(char *str, char **command)
{
    char * p;
    int i = 0, y = 0, z = 0;
    for (int k = 0; k < 3; k++)
    {
        p = command[k];
        for (int w = 0; w < 50; w++)
            p[w] = '\0';
    }
    
    while(str[i] != '\n' && str[i] != '\r' && str[i] != '\0')
    {
        p = command[y];
        if (str[i] == '/' && str[i+1] == '/')
            break;
        if (str[i] != ' ')
        {
            p[z] = str[i];
            z++;
        }
        else
        {
            y++;
            z = 0;
        }
        i++;
    }
}

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

void writeBootstrap(FILE *fasm)
{
    fprintf(fasm, "//bootstrap\n");
    fprintf(fasm, "@256\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "M=D\n");
}

void increseStack(FILE *fasm)
{
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D\n");
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "M=M+1\n");
}

void decreseStack(FILE *fasm)
{
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "M=M-1\n");
}

void error(int riga)
{
    printf("Errore: controlla la riga %d\n", riga);
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

void push(char *type, char *val, FILE *fasm, int riga)
{
    if (strcmp(type, (char *)"constant") == 0)
    {
        fprintf(fasm, "@%s\n", val);
        fprintf(fasm, "D=A\n");
        increseStack(fasm);
    }
    else if (strcmp(type, (char *)"static") == 0)
    {
        fprintf(fasm, "@%d\n", 16+atoi_custom(val));
        fprintf(fasm, "D=M\n");
        increseStack(fasm);
    }
    else if (strcmp(type, (char *)"local") == 0)
    {
        fprintf(fasm, "@LCL\n");
        fprintf(fasm, "D=M\n");
        fprintf(fasm, "@%d\n", atoi_custom(val));
        fprintf(fasm, "D=D+A\n");
        fprintf(fasm, "A=D\n");
        fprintf(fasm, "D=M\n");
        increseStack(fasm);
    }
    else if (strcmp(type, (char *)"argument") == 0)
    {
        fprintf(fasm, "@ARG\n");
        fprintf(fasm, "D=M\n");
        fprintf(fasm, "@%d\n", atoi_custom(val));
        fprintf(fasm, "D=D+A\n");
        fprintf(fasm, "A=D\n");
        fprintf(fasm, "D=M\n");
        increseStack(fasm);
    }
    else error(riga);
}

void pop(char *type, char *val, FILE *fasm, int riga)
{
    if (strcmp(type, (char *)"static") == 0)
    {
        decreseStack(fasm);
        fprintf(fasm, "@SP\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=M\n");
        fprintf(fasm, "@%d\n", 16+atoi_custom(val));
        fprintf(fasm, "M=D\n");
    }
    else if (strcmp(type, (char *)"local") == 0)
    {
        fprintf(fasm, "@%d\n", atoi_custom(val));
        fprintf(fasm, "D=A\n");
        fprintf(fasm, "@LCL\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=D+A\n");
        fprintf(fasm, "@LCL\n");
        fprintf(fasm, "M=D\n");
        decreseStack(fasm);
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=M\n");
        fprintf(fasm, "@LCL\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "M=D\n");
        fprintf(fasm, "@%d\n", atoi_custom(val));
        fprintf(fasm, "D=A\n");
        fprintf(fasm, "@LCL\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=A-D\n");
        fprintf(fasm, "@LCL\n");
        fprintf(fasm, "M=D\n");
    }
    else if (strcmp(type, (char *)"argument") == 0)
    {
        fprintf(fasm, "@%d\n", atoi_custom(val));
        fprintf(fasm, "D=A\n");
        fprintf(fasm, "@ARG\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=D+A\n");
        fprintf(fasm, "@ARG\n");
        fprintf(fasm, "M=D\n");
        decreseStack(fasm);
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=M\n");
        fprintf(fasm, "@ARG\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "M=D\n");
        fprintf(fasm, "@%d\n", atoi_custom(val));
        fprintf(fasm, "D=A\n");
        fprintf(fasm, "@ARG\n");
        fprintf(fasm, "A=M\n");
        fprintf(fasm, "D=A-D\n");
        fprintf(fasm, "@ARG\n");
        fprintf(fasm, "M=D\n");
    }
    else error(riga);
}

void add(FILE *fasm)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=D+M\n");
    increseStack(fasm);
}

void sub(FILE *fasm)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "D=M\n");
    increseStack(fasm);
}

void eq(FILE *fasm, int n_eq, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@EQ%d\n", n_eq);
    fprintf(fasm, "D;JEQ\n");
    push("constant", "0", fasm, riga);
    fprintf(fasm, "@END_EQ%d\n", n_eq);
    fprintf(fasm, "0;JMP\n");
    fprintf(fasm, "(EQ%d)\n", n_eq);
    fprintf(fasm, "@0\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "D=D-1\n");
    increseStack(fasm);
    fprintf(fasm, "(END_EQ%d)\n", n_eq);
}

void gt(FILE *fasm, int n_gt, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@GT%d\n", n_gt);
    fprintf(fasm, "D;JGT\n");
    push("constant", "0", fasm, riga);
    fprintf(fasm, "@END_GT%d\n", n_gt);
    fprintf(fasm, "0;JMP\n");
    fprintf(fasm, "(GT%d)\n", n_gt);
    fprintf(fasm, "@0\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "D=D-1\n");
    increseStack(fasm);
    fprintf(fasm, "(END_GT%d)\n", n_gt);
}

void lt(FILE *fasm, int n_lt, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@LT%d\n", n_lt);
    fprintf(fasm, "D;JLT\n");
    push("constant", "0", fasm, riga);
    fprintf(fasm, "@END_LT%d\n", n_lt);
    fprintf(fasm, "0;JMP\n");
    fprintf(fasm, "(LT%d)\n", n_lt);
    fprintf(fasm, "@0\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "D=D-1\n");
    increseStack(fasm);
    fprintf(fasm, "(END_LT%d)\n", n_lt);
}

void and(FILE *fasm, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D&M\n");
    fprintf(fasm, "D=M\n");
    increseStack(fasm);
}

void or(FILE *fasm, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D|M\n");
    fprintf(fasm, "D=M\n");
    increseStack(fasm);
}

void not(FILE *fasm, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "D=!D\n");
    increseStack(fasm);
}

void neg(FILE *fasm, int riga)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "D=-D\n");
    increseStack(fasm);
}

void if_goto(FILE *fasm, char *name)
{
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@%s\n", name);
    fprintf(fasm, "D;JNE\n");
}

void go_to(FILE *fasm, char *name)
{
    fprintf(fasm, "@%s\n", name);
    fprintf(fasm, "0;JMP\n");
}

void call(FILE *fasm, int n, char *name, char *val)
{
    //push return address
    fprintf(fasm, "@RETURNCALL%d\n", n);
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    //push LCL
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    //push ARG
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    //push THIS
    fprintf(fasm, "@THIS\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    //push THAT
    fprintf(fasm, "@THAT\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    //aggiorno LCL
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "M=D\n");
    //aggiorno ARG
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "M=D\n");
    fprintf(fasm, "@5\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "@%s\n", val);
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "@%s\n", name);
    fprintf(fasm, "0;JMP\n");
    fprintf(fasm, "(RETURNCALL%d)\n", n);
}

void returncall(FILE *fasm)
{
    //FRAME (R13) = LCL
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@R13\n");
    fprintf(fasm, "M=D\n");
    
    //RET (R14) = *(FRAME-5)
    fprintf(fasm, "@5\n");
    fprintf(fasm, "D=D-A\n");
    fprintf(fasm, "A=D\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@R14\n");
    fprintf(fasm, "M=D\n");

    //*ARG = pop()
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D\n");

    //SP = ARG+1
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=A+1\n");
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "M=D\n");

    //THAT = *(FRAME-1)
    fprintf(fasm, "@R13\n");
    fprintf(fasm, "M=M-1\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@THAT\n");
    fprintf(fasm, "M=D\n");

    //THIS = *(FRAME-2)
    fprintf(fasm, "@R13\n");
    fprintf(fasm, "M=M-1\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@THIS\n");
    fprintf(fasm, "M=D\n");

    //ARG = *(FRAME-3)
    fprintf(fasm, "@R13\n");
    fprintf(fasm, "M=M-1\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "M=D\n");

    //LCL = *(FRAME-4)
    fprintf(fasm, "@R13\n");
    fprintf(fasm, "M=M-1\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "M=D\n");

    fprintf(fasm, "@R14\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "0;JMP\n");
}

void writeComment(FILE *fasm, char **command)
{
    fprintf(fasm, "//");
    for (int i = 0; i < 3; i++)
        fprintf(fasm, "%s ", command[i]);
    fprintf(fasm, "\n");
}

void exec_command(char *command, char *type, char *val, int riga, FILE *fasm, COUNT c)
{
    if (strcmp(command, (char *)"push") == 0)
        push(type, val, fasm, riga);
    else if (strcmp(command, (char *)"pop") == 0)
        pop(type, val, fasm, riga);
    else if (strcmp(command, (char *)"add") == 0)
        add(fasm);
    else if (strcmp(command, (char *)"sub") == 0)
        sub(fasm);
    else if (strcmp(command, (char *)"neg") == 0)
        neg(fasm, riga);
    else if (strcmp(command, (char *)"eq") == 0)
    {
        eq(fasm, riga, c->eq);
        c->eq++;
    }
    else if (strcmp(command, (char *)"gt") == 0)
    {
        gt(fasm, riga, c->gt);
        c->gt++;
    }
    else if (strcmp(command, (char *)"lt") == 0)
    {
        lt(fasm, riga, c->lt);
        c->lt++;
    }
    else if (strcmp(command, (char *)"and") == 0)
        and(fasm, riga);
    else if (strcmp(command, (char *)"or") == 0)
        or(fasm, riga);
    else if (strcmp(command, (char *)"not") == 0)
        not(fasm, riga);
    else if (strcmp(command, (char *)"label") == 0)
        fprintf(fasm, "(%s)\n", type);
    else if (strcmp(command, (char *)"if-goto") == 0)
        if_goto(fasm, type);
    else if (strcmp(command, (char *)"goto") == 0)
        go_to(fasm, type);
    else if (strcmp(command, (char *)"function") == 0)
    {
        fprintf(fasm, "(%s)\n", type);
        for (int i = 0; i < atoi_custom(val); i++)
            push("constant", "0", fasm,  riga); 
    }
    else if (strcmp(command, (char *)"call") == 0)
        call(fasm, riga+1, type, val);
    else if (strcmp(command, (char *)"return") == 0)
        returncall(fasm);
    else
        error(riga);
}

int main(int argc, char **argv)
{
    FILE *fvm, *fasm;
    char str[128];
    
    char c0[50], c1[50], c2[50];
    char *command[] = {c0, c1, c2};

    int riga = 1;
    COUNT c = inizialize();
    
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