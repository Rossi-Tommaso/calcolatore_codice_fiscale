#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEN 30
#define CODE 16

char comune[LEN], provincia[LEN], cognome[LEN], nome[LEN], codice_fiscale[CODE];

int codice_cognome(void);
int codice_nome(void);
int f_comune(void);

int main()
{
    while (1)
    {
        int scelta, res;
        do
        {
            printf("(1) Da dati a codice fiscale \t (2) Da codice fiscale a dati\n\n\t\t(3)Esci dal programma\n\n");
            scanf("%d", &scelta);

            if (scelta != 1 && scelta != 2)
            {
                printf("Errore\n");
            }
        } while (scelta != 1 && scelta != 2);

        if (scelta == 1)
        {
            printf("Cognome: ");
            scanf("%s", cognome);

            res = codice_cognome();
            if (res == 1)
            {
                continue;
            }

            printf("\nNome: ");
            scanf("%s", nome);

            res = codice_nome();
            if (res == 1)
            {
                continue;
            }

            printf("Inserisci luogo di nascita:\n");
            scanf(" ");
            fgets(comune, sizeof(comune), stdin);

            printf("Inserisci provincia di nascita (AA):\n");
            scanf("%s", provincia);

            res = f_comune();
            if (res == 1)
            {
                continue;
            } // se il comune non viene trovato passa al prossimo ciclo
        }
    }
    return 0;
}

int codice_cognome(void)
{
    char voc[LEN] = "", cons[LEN] = "";
    int v = 0, c = 0;

    for (int i = 0; i < strlen(cognome); i++)
    {
        cognome[i] = toupper(cognome[i]);
        switch (cognome[i])
        {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            voc[v] = cognome[i];
            v++;
            break;

        default:
            cons[c] = cognome[i];
            c++;
            break;
        }
    }
    voc[v] = '\0';
    cons[c] = '\0';

    if (c >= 3)
    {
        for (int i = 0; i < 3; i++)
        {
            codice_fiscale[i] = cons[i];
        }
    }
    else if (c == 2 && v >= 1)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = cons[1];
        codice_fiscale[2] = voc[0];
    }
    else if (c == 1 && v >= 2)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = voc[0];
        codice_fiscale[2] = voc[1];
    }
    else if (c == 0 && v >= 3)
    {
        codice_fiscale[0] = voc[0];
        codice_fiscale[1] = voc[1];
        codice_fiscale[2] = voc[2];
    }
    else if (c == 1 && v == 1)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = voc[0];
        codice_fiscale[2] = 'X';
    }
    else if (c == 0 && v == 2)
    {
        codice_fiscale[0] = voc[0];
        codice_fiscale[1] = voc[1];
        codice_fiscale[2] = 'X';
    }
    else
    {
        printf("Errore nel calcolo del codice fiscale (cognome).\n");
        return 1;
    }

    printf("%s\n", codice_fiscale);
}

int codice_nome(void)
{
    char voc[LEN] = "", cons[LEN] = "";
    int v = 0, c = 0;

    for (int i = 0; i < strlen(nome); i++)
    {
        nome[i] = toupper(nome[i]);
        switch (nome[i])
        {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            voc[v] = nome[i];
            v++;
            break;

        default:
            cons[c] = nome[i];
            c++;
            break;
        }
    }
    voc[v] = '\0';
    cons[c] = '\0';

    if (c > 3)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = cons[2];
        codice_fiscale[2] = cons[3];
    }
    else if (c == 3)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = cons[1];
        codice_fiscale[2] = cons[2];
    }
    else if (c == 2)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = cons[1];
        codice_fiscale[2] = voc[0];
    }
    else if (c == 1 && v >= 2)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = voc[0];
        codice_fiscale[2] = voc[1];
    }
    else if (c == 1 && v == 1)
    {
        codice_fiscale[0] = cons[0];
        codice_fiscale[1] = voc[0];
        codice_fiscale[2] = 'X';
    }
    else if (c == 0 && v == 2)
    {
        codice_fiscale[0] = voc[0];
        codice_fiscale[1] = voc[1];
        codice_fiscale[2] = 'X';
    }
    else
    {
        printf("Errore nel calcolo del codice fiscale (Nome).\n");
        return 1;
    }

    printf("%s\n", codice_fiscale);
}

int f_comune(void)
{
    FILE *fp;
    char cod_catastale[LEN], com[LEN], pro[LEN];
    int count = 0;

    for (int i = 0; i < strlen(comune); i++)
    {
        comune[i] = toupper(comune[i]);

        if (comune[i] == ' ')
            comune[i] = '_';

        if (comune[i] == '\n')
        {
            comune[i] = '\0';
            i--;
        }

        if (comune[i + 1] == '\0' && (comune[i] == '_' || comune[i] == ' '))
        {
            comune[i] = '\0';
        }
    }

    for (int i = 0; i < strlen(provincia); i++)
    {
        provincia[i] = toupper(provincia[i]);
    }

    provincia[strlen(provincia)] = '\0';
    printf("%s\n%s\n\n", comune, provincia);

    fp = fopen("comuni.txt", "r");

    if (fp == NULL)
    {
        printf("Errore nell'apertura del file\n");
        return -1;
    }

    while (fscanf(fp, "%s %s %s", cod_catastale, com, pro) != EOF)
    {
        if (strcmp(com, comune) == 0 && strcmp(pro, provincia) == 0)
        {
            printf("\n%s\n", cod_catastale);
            count = 1;
            break;
        }
    }
    if (count == 0)
    {
        printf("Comune non trovato\n");
        return 1;
    }

    fclose(fp);
    return 0;
}
