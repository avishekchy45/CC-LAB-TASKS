/*
** Author: avishekchy45
*/

#include <stdio.h>
int main()
{
    int i, j_5, k;
    // print name if divisible by 5
    for (i = 0, k = 0; i <= 10; i++, k++)
    {
        if (i % 5 == 0)
            printf("%d Avishek Chowdhury\n", k);
    }
}
