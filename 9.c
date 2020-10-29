#include <stdio.h>

int szescian(int a[])
{

    for(int i=0;i<8;i++)
    {
        a[i]=0;
    }
    return a;
}

int main()
{
    int a[]={1,2,3,4,5,6,7,8};

    for(int i=0;i<8;i++)
    {
        printf("%d ",a[i]);
    }
printf("\n");
    szescian(a);

    for(int i=0;i<8;i++)
    {
        printf("%d ",a[i]);
    }

    return 0;
}




