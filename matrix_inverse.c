#include <stdio.h>
#include <math.h>
#define SIZE 5

float C[SIZE];
void compare(float A[][SIZE], float B[][SIZE], float *C, int i, int n)
{
  int j;
  int count =0;
  for(j=0;j<n;j++)
    {
      if(A[j][i] != B[j][i])
		{
	  		count = 1;
	  		break;
		}
    }
   for(j=0;j<n;j++)
	  C[j] = A[j][i];                   
}

void multiply(float inverseB[][SIZE], float *C, float *E, int n)
{
  	int i,j;
	for(i=0;i<n;i++)
      E[i] = 0;

  	for(j=0;j<n;j++)
	{
      for(i=0;i<n;i++)
	  			E[j] = E[j] + inverseB[j][i]*C[i]; 
   }
  	return ;
}

void change(float *E, int i, int n)
{
  int j;
  float pivot_element;
  pivot_element = E[i];
  E[i] = 1/pivot_element;

  for(j=0;j<n;j++)
    {
      if(j != i)
			E[j] = (-1)*E[j]/pivot_element;
    }
  return ;
}

void multiplication(float P[][SIZE], float inverseB[][SIZE], int n)
{
  int i,j,k;
  float K[SIZE][SIZE];

  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
			K[i][j] = 0;
    }

  for(i=0;i<n;i++)
    {
		for(k=0;k<n;k++)
		{
      	for(j=0;j<n;j++)
				K[i][k] = K[i][k] + P[i][j]*inverseB[j][k];
    	}
	}

  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
		inverseB[i][j] = K[i][j];
    }
  return;
}

int main()
{
  float A[SIZE][SIZE];
  float B[SIZE][SIZE];
  float inverseB[SIZE][SIZE];
  float P[SIZE][SIZE];
  float E[SIZE];
  int i,j,n,k;

  printf("Enter size of non-singular matrix : ");
  scanf("%d",&n);

  for(i=0;i<n;i++)
   {
     for(j=0;j<n;j++)
       {
	 B[i][j] = 0;
	 inverseB[i][j] = 0;
	 P[i][j] = 0;
       }
   }

  for(i=0;i<n;i++)
    {
      inverseB[i][i] = 1;
      B[i][i] = 1;
      P[i][i] = 1;
    }

  printf("Enter matrix whose inverse required:\n");
  for(i=0;i<n;i++)
   {
     for(j=0;j<n;j++)
       scanf("%f",&A[i][j]);
   }

	printf("\nMatrix A :\n");
 	for(i=0;i<n;i++)
   {
     for(j=0;j<n;j++)
       printf("%0.2f\t",A[i][j]);
     printf("\n");
   }
   
  	for(i=0;i<n;i++)
    {
      compare(A,B,C,i,n);
      multiply(inverseB,C,E,n);
      change(E,i,n);

      for(j=0;j<n;j++)
			P[j][i] = E[j]; 
      
     	multiplication(P,inverseB,n);

		for(k=0;k<n;k++)
    	{
      	for(j=0;j<n;j++)
				P[k][j] = 0;
    	}
  		for(k=0;k<n;k++)
      	P[k][k] = 1;
    }

	printf("Final answer for inverse A is :\n");
  	for(k=0;k<n;k++)
    {
      for(j=0;j<n;j++)
			printf("%0.2f\t",inverseB[k][j]);
      printf("\n");
    }
  return 0;
}


/* OUTPUT 1:

Enter size of non-singular matrix : 3
Enter matrix whose inverse required:
2 2 2
2 4 1
1 0 1

Matrix A :
2.00    2.00    2.00
2.00    4.00    1.00
1.00    0.00    1.00

Final answer for inverse A is :
-2.00   1.00    3.00
0.50    0.00    -1.00
2.00    -1.00   -2.00

*/




