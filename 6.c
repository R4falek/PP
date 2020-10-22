#include <stdio.h>

int main()
{
    char s;
    char t[6][10]= {"ananas","banan","cebula","domek","eskimos"};

    scanf("%c",&s);

    if(s=='A'||s=='a')
    {
        printf("%s",t[0]);
    }
    if(s=='b'||s=='B')
    {
        printf("%s",t[1]);
    }
    if(s=='C'||s=='c')
    {
        printf("%s",t[2]);
    }
    if(s=='D'||s=='d')
    {
        printf("%s",t[3]);
    }
    if(s=='E'||s=='e')
    {
        printf("%s",t[4]);
    }

    return 0;
}




