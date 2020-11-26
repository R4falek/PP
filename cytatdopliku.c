#include <stdio.h>

int main()
{
    FILE *plik;
    const char tekst[]="Panie co pan";

    if((plik = fopen("Kiepski.txt","w")) == NULL)
    {
     printf("ERROR");
     exit(1);
    }
    fprintf(plik,"%s",tekst);
    fclose(plik);

    return 0;
}
