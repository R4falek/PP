#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void szescian(char a[][15])
{
    int i;
    srand(time(NULL));
    i=rand()%5;
    printf("%s\n",a[i]);
}

int main()
{
    char a[][15]={"kielbasa","browar","renta wysoka","taniec i spiew","obiecanki"};
    szescian(a);

    return 0;
}





