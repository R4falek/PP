#include <stdio.h>

int szescian(int a)
{
    int x=1;
    for(int i=1;i<=a;++i)
    {
        x=x*i;
    }
    return x;
}

int main()
{
    printf("%d\n",szescian(2));
    printf("%d\n",szescian(3));
    printf("%d\n",szescian(4));
    printf("%d\n",szescian(13));

    return 0;
}



