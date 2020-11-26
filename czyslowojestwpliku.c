#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *plik;
    char tekst[100];
    char slowo[10]="ser";

    if((plik = fopen("Kiepski.txt","r")) == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    while(fscanf(plik,"%s",&tekst)==1)
    {
        if(strcmp(tekst,slowo)==0)
        {
            printf("Usinieto");
            fclose(plik);
            remove("Kiepski.txt");
        }
    }







    return 0;
}

