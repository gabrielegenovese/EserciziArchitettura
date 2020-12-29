#include <stdio.h>

typedef struct count
{
    int eq;
    int gt;
    int lt;
} *COUNT;

COUNT inizializza();
void getCommand(char *str, char **command);
char *getNameFile(char str[]);
void writeBootstrap(FILE *fasm);
void increseStack(FILE *fasm);
void decreseStack(FILE *fasm);
void error(int riga);
int pow_custom(int n, int e);
int atoi_custom(char * num);
void push(char *type, char *val, FILE *fasm, int riga);
void pop(char *type, char *val, FILE *fasm, int riga);
void add(FILE *fasm);
void sub(FILE *fasm);
void eq(FILE *fasm, int n_eq, int riga);
void gt(FILE *fasm, int n_gt, int riga);
void lt(FILE *fasm, int n_lt, int riga);
void and(FILE *fasm, int riga);
void or(FILE *fasm, int riga);
void not(FILE *fasm, int riga);
void neg(FILE *fasm, int riga);
void if_goto(FILE *fasm, char *name);
void go_to(FILE *fasm, char *name);
void call(FILE *fasm, int n, char *name, char *val);
void returncall(FILE *fasm);
void writeComment(FILE *fasm, char **command);
void exec_command(char *command, char *type, char *val, int riga, FILE *fasm, COUNT c);