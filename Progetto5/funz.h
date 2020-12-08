#include <stdio.h>

typedef struct variabile{
    char *nome;
    int val;
    struct variabile *next;
} *VAR;

char *nome_file(char str[]);
char *getCommand(char str[128]);
void write_bit(FILE * fhack, int write[16]);
int *num_to_bit(int n);
int atoi_custom(char * num);
void error(char *c, int riga);
int isStringEqual(char * p1, char * p2);
int assegnamento(int *write, char c, char *op);
void exec_command(char *command, int riga, int write[16], FILE * fhack, VAR var);
VAR newVariable(VAR head, char * name, int val);
VAR getLabel(VAR variables, FILE * fasm);
VAR getVar(VAR variables, FILE * fasm);