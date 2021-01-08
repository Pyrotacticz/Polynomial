#include <stdio.h>
#include <stdlib.h>

#define NUM_INTS 4

int main()
{
        int* blck = (int *)malloc(NUM_INTS * sizeof(int));

        for (int j =0; j<NUM_INTS; j++){
                blck[j] = j;
                printf("Value at Block %d: %d\n",j,blck[j]);
        }

        printf("The %dth int is %d\n", NUM_INTS,blck[NUM_INTS]);

        printf("The -1st int is %d\n", blck[-1]);
        free(blck);
        return 0;

}
