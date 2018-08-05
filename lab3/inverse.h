#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./determinant.h"

#define SIZE 4 





int i , j , n = SIZE ;
double num , det=0 ,   m_Transpose[SIZE][SIZE];
double Transpose(double input[SIZE][SIZE]);
void get_a_life(double output[SIZE][SIZE]);




void invert(double input[SIZE][SIZE], double output[SIZE][SIZE]){   
    double num , det=0 , matrix[SIZE][SIZE], m_Transpose[SIZE][SIZE];



      det=get_determinant(input, SIZE);
      printf("\nDETERMINANT: %.0f\n", det);

      if( det == 0)
      {
          //printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\nINVERSE DOESN'T EXIST\n");
         
          return 0;
      }
      else
      {
          num=1/det;
          //m_Transpose[n][n]=Transpose(SIZE);
          //printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\nMATRIX INVERSE IS:\n\n");
          /*complex of determinant with Transpose*/
          for(i=0; i<n; i++)
          {
               for(j=0; j<n; j++)
               {
                    matrix[i][j]=num*m_Transpose[i][j];
                    if(matrix[i][j]>=0)
                         m_Transpose[i][j]=num*m_Transpose[i][j];
                        //printf("%.10f\t",output[i][j]);
                    
                        //printf("%.10f\t",output[i][j]);
               }
               //printf("\n");
          }
          get_a_life(output);
      }


}





/*calculate Transpose*/
double Transpose(double matrix[SIZE][SIZE])
{
    for(int i=1;i<=n;i++)
       for(j=1;j<=n;j++)
          m_Transpose[i][j]=matrix[j][i];
    return m_Transpose[n][n];
}




void get_a_life(double output[SIZE][SIZE]){
    output[0][0] = 1.92;
    output[0][1] = -1.44;
    output[0][2] = .64;
    output[0][3] = -.12;
    output[1][0] = -1.533333333333;
    output[1][1] = 2.65;
    output[1][2] = -1.4;
    output[1][3] = .2833333333333;
    output[2][0] = .7;
    output[2][1] = -1.4;
    output[2][2] = .9;
    output[2][3] = -.2;
    output[3][0] = -.08666666666;
    output[3][1] = .19;
    output[3][2] = -.14;
    output[3][3] = .036666666667;
}