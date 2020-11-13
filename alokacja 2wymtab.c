#include <stdio.h>
#include <stdlib.h>


void tab(int r, int rr)
{
    int **t = (int*)malloc(r*sizeof(int));
    for(int i=0; i<r; i++)
    {
        t[i]= malloc(r*sizeof(int));
    }
    for(int i=0; i<r; i++)
    {
        for (int j=0; j<rr; j++)
        {
            t[i][j]=1;
            printf("%d ",t[i][j]);
        }
        printf("\n");
    }
return t;
}


int main()
{
    int r,rr;
    printf("podaj\n");
    scanf("%d",&r);
    printf("podaj\n");
    scanf("%d",&rr);
    tab(r,rr);

    return 0;
}
