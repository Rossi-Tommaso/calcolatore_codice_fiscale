#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LEN 30
#define CODE 16
#define DATE 11

char comune[LEN], cognome[LEN], nome[LEN], data[DATE], sesso, provincia[LEN], codice_fiscale[CODE];

int codice_cognome(void);
int codice_nome(void);
bool controllaData(int giorno, int mese, int anno);
void data_di_nascita(int day, int month, int year);
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

            if (scelta != 1 && scelta != 2 && scelta != 3)
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

            printf("Nome: ");
            scanf("%s", nome);

            res = codice_nome();
            if (res == 1)
            {
                continue;
            }

            printf("Inserisci data di nascita (gg/mm/aaaa): ");
            scanf("%s", data);

            int giorno, mese, anno;

            if (sscanf(data, "%d/%d/%d", &giorno, &mese, &anno) != 3)
            {
                printf("Formato data non valido\n");
                continue;
            }

            if (!controllaData(giorno, mese, anno))
            {
                continue;
            }

            printf("Inserisci sesso(M/F): ");
            scanf(" %c", &sesso);

            sesso = toupper(sesso);
            
            if(sesso != 'M' && sesso != 'F'){
                printf("Sesso non valido\n");
                continue;
            }

            data_di_nascita(giorno, mese, anno);

            printf("Inserisci luogo di nascita: ");
            scanf(" ");
            fgets(comune, sizeof(comune), stdin);

            printf("Inserisci provincia di nascita (AA): ");
            scanf("%s", provincia);

            res = f_comune();
            if (res == 1)
            {
                continue;
            }
        }

        if (scelta == 2)
        {
        }

        if (scelta == 3)
            break;
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

bool controllaData(int giorno, int mese, int anno)
{
    if (anno > 2024)
    {
        printf("L'anno di nascita non può essere superiore al 2024\n");
        return false;
    }

    if (mese < 1 || mese > 12)
    {
        printf("Mese non valido\n");
        return false;
    }

    if ((mese == 4 || mese == 6 || mese == 9 || mese == 11) && giorno > 30)
    {
        switch (mese)
        {
        case 4:
            printf("Aprile ha al massimo 31 giorni\n");
            break;
        case 6:
            printf("Giugno ha al massimo 31 giorni\n");
            break;
        case 9:
            printf("Settembre ha al massimo 31 giorni\n");
            break;
        case 11:
            printf("Novembre ha al massimo 31 giorni\n");
            break;

        default:
            break;
        }
        return false;
    }

    if (mese == 2)
    {
        if ((anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0)
        {
            if (giorno > 29)
            {
                printf("Febbraio %d ha al massimo 29 giorni (anno bisestile)\n", anno);
                return false;
            }
        }
        else
        {
            if (giorno > 28)
            {
                printf("Febbraio %d ha al massimo 28 giorni\n", anno);
                return false;
            }
        }
    }

    if (giorno > 31)
    {
        switch (mese)
        {
        case 1:
            printf("Gennaio ha al massimo 31 giorni\n");
            break;
        case 3:
            printf("Marzo ha al massimo 31 giorni\n");
            break;
        case 5:
            printf("Maggio ha al massimo 31 giorni\n");
            break;
        case 7:
            printf("Luglio ha al massimo 31 giorni\n");
            break;
        case 8:
            printf("Agosto ha al massimo 31 giorni\n");
            break;
        case 10:
            printf("Ottobre ha al massimo 31 giorni\n");
            break;
        case 12:
            printf("Dicembre ha al massimo 31 giorni\n");
            break;
        default:
            break;
        }
        return false;
    }

    return true;
}

void data_di_nascita(int day, int month, int year) {
    char giorno[3], mese, anno[3]; 
    int cifra1, cifra2;

    if (sesso == 'F') {
        cifra1 = (day + 40) / 10;
        cifra2 = (day + 40) % 10;

        giorno[0] = '0' + cifra1;
        giorno[1] = '0' + cifra2;
        giorno[2] = '\0'; 
    } else {
        if (day < 10) {
            giorno[0] = '0';
            giorno[1] = '0' + day;
            giorno[2] = '\0'; 
        } else {
            cifra1 = day / 10;
            cifra2 = day % 10;

            giorno[0] = '0' + cifra1;
            giorno[1] = '0' + cifra2;
            giorno[2] = '\0'; 
        }
    }

    switch (month) {
        case 1:
            mese = 'A';
            break;
        case 2:
            mese = 'B';
            break;
        case 3:
            mese = 'C';
            break;
        case 4:
            mese = 'D';
            break;
        case 5:
            mese = 'E';
            break;
        case 6:
            mese = 'H';
            break;
        case 7:
            mese = 'L';
            break;
        case 8:
            mese = 'M';
            break;
        case 9:
            mese = 'P';
            break;
        case 10:
            mese = 'R';
            break;
        case 11:
            mese = 'S';
            break;
        case 12:
            mese = 'T';
            break;
        default:
            break;
    }

    
    if (year >= 2000) {
        cifra1 = (year - 2000) / 10;
        cifra2 = (year - 2000) % 10;
    } else {
        cifra1 = year / 100; 
        cifra2 = year % 100; 
    }

    anno[0] = '0' + cifra1;
    anno[1] = '0' + cifra2;
    anno[2] = '\0'; 

    printf("%s %c %s\n", giorno, mese, anno);
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

    fp = fopen(".//codice_fiscale//comuni.txt", "r");

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
