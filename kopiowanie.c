#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *plik,*plik1;
    char tekst[100];
    char slowo[10]="pan";

    if((plik = fopen("Kiepski.txt","r")) == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    if((plik1 = fopen("Kiepskikopia.txt","w")) == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    while(fscanf(plik,"%s",&tekst)==1)
    {
        fprintf(plik1,"%s ",tekst);
    }
    fclose(plik);
    fclose(plik1);




    return 0;
}
