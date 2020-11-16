#include <stdio.h>
//prova
int main(int argc, char **argv)
{
    FILE *rf, *wf;
    char str[60];
    if(argc > 1)
    {
        rf = fopen(argv[1], "r");
        fgets(str, 60, rf);

        wf = fopen(argv[2], "w");
        fprintf(wf, str);

        printf("File %s copiato con successo su %s\n", argv[1], argv[2]);
    }
    else
    {
        printf("Inserire il nome del file da copiare\n");
        scanf("%s",str);
        rf = fopen(str, "r");
        printf("Inserire il nome del file su cui scrivere\n");
        scanf("%s",str);
        wf = fopen(str, "w");

        while (fgets(str, 60, rf) != NULL) fprintf(wf, str);
    }
    
    fclose(wf);
    fclose(rf);
}