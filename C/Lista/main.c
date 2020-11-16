#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    char elem;
    struct lista * next;
} LISTA;

void stampa_lista(LISTA * head)
{
    while (head != NULL)
    {
        printf("%c\t", head->elem);
        head = head->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int elim = 0, i = 0;
    LISTA * head, * prec, * tmp = malloc(sizeof(LISTA));
    head = tmp;

    while(argv[1][i+1] != '\0')
    {
        tmp->elem = argv[1][i];
        tmp->next = malloc(sizeof(LISTA));
        tmp = tmp->next;
        i++;
    }

    tmp->elem = argv[1][i];
    tmp->next = NULL;

    tmp = head;
    stampa_lista(tmp);
    
    do{
        printf("Scegli il carattere da eliminare (tra 0 e %d comprese): ", i);
        scanf("%d", &elim);
    }while (elim >= i && elim < 0);

    if(elim == 0){
        head = head->next;
    }
    else
    {
        i = 0;
        tmp = head;
        prec = head;
        while (i < elim)
        {
            i++;
            prec = tmp;
            tmp = tmp->next;
        }

        prec->next = tmp->next;
    }
    
    stampa_lista(head);
    
    return(0);
}