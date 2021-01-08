#include <stdio.h>
#include <stdlib.h>

#define NUM_INTS 4

int main()
{
        int* blck = (int *)malloc(NUM_INTS * sizeof(int));

        for (int j =0; j<NUM_INTS; j++){
                blck[j] = j;
        }

        return 0;

}
