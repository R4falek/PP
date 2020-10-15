#include <stdio.h>
#include <math.h>

int main()
{
    char t[4][10];
    int x;

    scanf("%s",&t[0]);
    scanf("%s",&t[1]);
    scanf("%s",&t[2]);
    scanf("%s",&t[3]);

    printf("podaj numer słowa");
    scanf("%d",&x);
    printf("%s",t[x-1]);

    return 0;
}



