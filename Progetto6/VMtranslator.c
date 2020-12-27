#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct count
{
    int eq;
    int gt;
    int lt;
    int func;
} *COUNT;

char command[3][50];

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

COUNT inizialize()
{
    COUNT c = malloc(sizeof(COUNT));
    c->eq=0;
    c->gt=0;
    c->lt=0;
    c->func = 0;
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
    decreseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "D=M\n");
    fprintf(fasm, "@%s\n", name);
    fprintf(fasm, "0;JMP\n");
}

void call(FILE *fasm, int n, char *name, char *val, int riga)
{
    fprintf(fasm, "@%d\n", n);
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    fprintf(fasm, "@THIS\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    fprintf(fasm, "@THAT\n");
    fprintf(fasm, "D=A\n");
    increseStack(fasm);
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@LCL\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D\n");
    fprintf(fasm, "@SP\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=D\n");
    fprintf(fasm, "@5\n");
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=M-D\n");
    fprintf(fasm, "@%s\n", val);
    fprintf(fasm, "D=A\n");
    fprintf(fasm, "@ARG\n");
    fprintf(fasm, "A=M\n");
    fprintf(fasm, "M=M-D\n");

    for (int i = 0; i < atoi_custom(val); i++)
        pop("argument", (char*)48+i, fasm, riga);
    
    fprintf(fasm, "@%s\n", name);
    fprintf(fasm, "0;JMP\n");
}

void exec_command(int riga, FILE *fasm, COUNT c)
{
    if (strcmp(command[0], (char *)"push") == 0)
        push(command[1], command[2], fasm, riga);
    else if (strcmp(command[0], (char *)"pop") == 0)
        pop(command[1], command[2], fasm, riga);
    else if (strcmp(command[0], (char *)"add") == 0)
        add(fasm);
    else if (strcmp(command[0], (char *)"sub") == 0)
        sub(fasm);
    else if (strcmp(command[0], (char *)"neg") == 0)
        neg(fasm, riga);
    else if (strcmp(command[0], (char *)"eq") == 0)
    {
        eq(fasm, riga, c->eq);
        c->eq++;
    }
    else if (strcmp(command[0], (char *)"gt") == 0)
    {
        gt(fasm, riga, c->gt);
        c->gt++;
    }
    else if (strcmp(command[0], (char *)"lt") == 0)
    {
        lt(fasm, riga, c->lt);
        c->lt++;
    }
    else if (strcmp(command[0], (char *)"and") == 0)
        and(fasm, riga);
    else if (strcmp(command[0], (char *)"or") == 0)
        or(fasm, riga);
    else if (strcmp(command[0], (char *)"not") == 0)
        not(fasm, riga);
    else if (strcmp(command[0], (char *)"label") == 0)
        fprintf(fasm, "(%s)\n", command[1]);
    else if (strcmp(command[0], (char *)"if-goto") == 0)
        if_goto(fasm, command[1]);
    else if (strcmp(command[0], (char *)"goto") == 0)
        go_to(fasm, command[1]);
    else if (strcmp(command[0], (char *)"function") == 0)
    {
        fprintf(fasm, "(%s)\n", command[1]);
        for (int i = 0; i < atoi_custom(command[2]); i++)
            push("constant", ((char*)i+48), fasm,  riga);
    }
    else if (strcmp(command[0], (char *)"call") == 0)
    {
        c->func++;
        //call(fasm, c->func, command[1], command[2], riga);
    }
    else if (strcmp(command[0], (char *)"return") == 0)
    {
        /* code */
    }
    else
        error(riga);
}

int main(int argc, char **argv)
{
    FILE *fvm, *fasm;
    char str[128];
    int riga = 1, i, y, z;
    COUNT c = inizialize();
    
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
        //prendo il comando come un array con 3 parole lungo al massimo 50
        i = 0; y = 0; z = 0;
        for (int k = 0; k < 3; k++)
            for (int w = 0; w < 50; w++)
                command[k][w] = '\0';
        
        while(str[i] != '\n' && str[i] != '\r' && str[i] != '\0')
        {
            if (str[i] == '/' && str[i+1] == '/')
                break;
            if (str[i] != ' ')
            {
                command[y][z] = str[i];
                z++;
            }
            else
            {
                y++;
                z = 0;
            }
            i++;
        }

        if (command[0][0] != '\0')
        {
            fprintf(fasm, "//");
            for (int i = 0; i < 3; i++)
                fprintf(fasm, "%s ", command[i]);
            fprintf(fasm, "\n");
            exec_command(riga, fasm, c);
        }

        riga++;
    }

    fclose(fvm);
    fclose(fasm);
    return(0);
}