#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
 #include "determinant.h"

int main()
{

 
    double matrix[6][6] = {{1, 0, 2, -1, 2, 3},
                     {3, 0, 0, 5, 2, 3},
                     {2, 1, 4, -3, 2, 3},
                     {1, 0, 5, 0, 2, 3},
                     {-1, 0, 4, 2, 1, -4},
                     {2, 1, 7, -3, -2, 0}
                    };
    srand(time(NULL));

 
    printf("Determinant of the matrix is : %.01f\n",
            get_determinant(matrix, 6));
    return 0;
}
