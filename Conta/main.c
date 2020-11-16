#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *rf, *wf;
    char tmp;
    int c = 0;

    if(argc > 1)
    {
        rf = fopen(argv[1], "r");
        wf = fopen("conta.txt", "w");

        do
        {
            fscanf(rf, "%c", &tmp);

            if(tmp == ' ' || feof(rf))
            {
                fprintf(wf, "%d ", c);
                c = 0;
            }
            else if(tmp == '\n')
            {
                fprintf(wf, "%d\n", c);
                c = 0;
            }
            else c++;
        } while (!feof(rf));

        fclose(wf);
        fclose(rf);
    }
    else
        printf("Errore: inserire un argomento\n");
}