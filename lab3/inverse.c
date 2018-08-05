#include <stdio.h>

#include <string.h>;
#include <stdlib.h>;
#include "./determinant.h"

const int max=20;
int i , j , n , k , size=0 , row , column ;
float num , det=0 , inverse_matrix[max][max] , matrix[max][max] , new_mat[max][max] , m_minor[max][max] , m_Transpose[max][max];

float determinant(float matrix[max][max]);
float minor(float matrix[max][max],int k);
float Transpose(float matrix[max][max]);

int main()
{
      printf("\n What is degree of your matrix?");
      scanf("%d",&n);
      printf("\n Please entre your matrix's rooms:");

      for(i=1;i<=n;i++)
      {
         for(j=1;j<=n;j++)
         {
             printf("\n\t[ %d , %d ] = ",i,j);
             scanf("%d",&matrix[i][j]);
         }
         printf("\n");
      }
      size=n;
      det=get_determinant(matrix, 20);

      if(det==0)
      {
          printf("\n\t* * * * * * * * * * * * * * * * * * * * * * * *\n\tINVERSE DOESN'T EXIST");
          getch();
          return 0;
      }
      else
      {
          num=1/det;
          m_Transpose[n][n]=Transpose(matrix);
          printf("\n\t* * * * * * * * * * * * * * * * * * * * * * * *\n\tMATRIX REVERSE IS:\n\n\t");
          /*complex of determinant with Transpose*/
          for(i=1;i<=n;i++)
          {
               for(j=1;j<=n;j++)
               {
                    inverse_matrix[i][j]=num*m_Transpose[i][j];
                    if(inverse_matrix[i][j]>=0)
                        printf("     %d",inverse_matrix[i][j]);
                    else
                        printf("     %d",inverse_matrix[i][j]);
               }
               printf("\n\t");
          }
      }


      getch();
      return 0;
}



/*calculate minor of matrix and return to determinant's function*/
float minor(float matrix[][max],int k)
{
      int m=1 , p , r , c , row=1 , column;
      column=k;
      for(r=2;r<=n;r++)
      {
          p=1;
          for(c=1;c<=n;c++)
          {
              if(r!=row &amp;&amp; c!=column)
              {
                  new_mat[m][p]=matrix[r][c];
                  p++;
              }
          }
          if(r!=row)
             m++;
      }
      n--;
      return new_mat[m][p];

}

/*calculate Transpose*/
float Transpose(float matrix[][max])
{
    for(int i=1;i<=n;i++)
       for(j=1;j<=n;j++)
          m_Transpose[i][j]=matrix[j][i];
    return m_Transpose[n][n];
}