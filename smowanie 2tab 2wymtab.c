#include <stdio.h>
#include <stdlib.h>


int** tab(int r, int rr)
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
            t[i][j]=i+j;
        }
    }
    return t;
}

void fre(int **t,int r)
{
    for(int i=0; i<r; i++)
    {
        free(t[i]);
    }
    free(t);
}
void pisz(int **t,int r,int rr)
{
    for(int i=0; i<r; i++)
    {
        for (int j=0; j<rr; j++)
        {
            printf("%d ",t[i][j]);
        }
        printf("\n");
    }
}

int sum(int **t1,int **t2,int **t3,int r,int rr)
{

    for(int i=0; i<r; i++)
    {
        for (int j=0; j<rr; j++)
        {
            t3[i][j]=t1[i][j]+t2[i][j];
        }

    }
    return t3;
}

int main()
{
    int r,rr;
    printf("podaj\n");
    scanf("%d",&r);
    printf("podaj\n");
    scanf("%d",&rr);

    int** t1 = tab(r,rr);
    pisz(t1,r,rr);
    printf("\n");
    int** t2 = tab(r,rr);
    pisz(t2,r,rr);
    int** t3 = tab(r,rr);
    t3 = sum(t1,t2,t3,r,rr);
    printf("\n");
    pisz(t3,r,rr);
    fre(tab(r,rr),r);

    return 0;
}
