/*
bubble x 
*/
#include <stdio.h>
#include <stdlib.h>

void printRandoms(int min, int max, int count)
{
    unsigned int seed = time(0);
    for(int i = 0; i < count; i++)
    {
        int rd_num = rand_r(&seed) % (max - min + 1) + min;
        printf("%d\n", rd_num);
    }
}

int main(void)
{
    int min = 0, max = 100, count = 10;
    printRandoms(min,max,count);
    return 0;
}