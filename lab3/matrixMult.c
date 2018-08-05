#include <stdio.h>
#include "./matrixMult.h"
// source: https://www.programmingsimplified.com/c-program-multiply-matrices
int main()
{
  int m, n, p, q, c, d, k, sum = 0;

  int counter = 0; // to give each of the matrices different values
  printf("Enter number of rows and columns of first matrix\n");
  scanf("%d%d", &m, &n);
  printf("Enter elements of first matrix\n");
   int first[m][n];
  for (c = 0; c < m; c++)
    for (d = 0; d < n; d++){
		first[c][d] = counter;
		counter += 1;
	}
 
  printf("Enter number of rows and columns of second matrix\n");
  scanf("%d%d", &p, &q);
 int second[p][q];
 int multiply[m][q];
  if (n != p)
    printf("The matrices can't be multiplied with each other.\n");
  else
  {
    //printf("Enter elements of second matrix\n");
	counter = 0; // it will get large really fast if we don't reset it to 0.
    for (c = 0; c < p; c++)
      for (d = 0; d < q; d++){
	second[c][d] = counter;
	counter += 1;
}
 
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k = 0; k < p; k++) {
          sum = sum + first[c][k]*second[k][d];
        }
 
        multiply[c][d] = sum;
        sum = 0;
      }
    }
 
    printf("Product of the matrices without function:\n");
 
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++)
        printf("%d\t", multiply[c][d]);
 
      printf("\n");
    }
	
	printf("Product of the matrices with function:\n");
	setMatricesDimensions(m, p, n, q);
	matrixMult(first, second, multiply);
	for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++)
        printf("%d\t", multiply[c][d]);
 
      printf("\n");
    }
  }
 
  return 0;
}
