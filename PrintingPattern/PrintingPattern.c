#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n;
    scanf("%d", &n);
  	// Complete the code to print the pattern.

    int size = n*2-1;
    for (int i = 0; i < size; i++) {
        //i = max to subtract each row (until middle)
        int z = i < n ? i : size - i - 1;
        for (int j = 0; j < size; j++) {
            //j = how much to subtract each col (until middle)
            int y = j < n ? j : size - j - 1;
            int x = y > z ? z : y;
            printf("%d ", n - x);
        }

        printf("\n");
    }
    return 0;
}
