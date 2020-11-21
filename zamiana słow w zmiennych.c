#include <stdio.h>
#include <stdlib.h>

void rotate(int *a, int *b)
{
    int tmo = *a;
    *a = *b;
    *b = tmo;
}

int main()
{
    char a[]="pies",b[]="doga";
    printf("%s %s\n",a,b);

    rotate(a,b);

    printf("%s %s",a,b);
    return 0;
}
