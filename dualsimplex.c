#include <stdio.h>
#include <math.h>
#define MAXVAL 10

int temp(float B[MAXVAL], int basic)
{
  int i;
  int count = 0;
  for(i=0;i<basic;i++)
    {
      if( B[i] < 0)
	count = 1;
    }
  return count;
}

int main()
{
  int i,j;
  int basic,var,total;
  float A[MAXVAL][MAXVAL]; 
  float B[MAXVAL],Z[MAXVAL],X[MAXVAL];
  float max,min;
  int t1,t2;
  float multi,divi;
  int check[MAXVAL];
  char C,d;

  printf("***************Dual-simplex method****************\n");
  
  printf("Enter the number of equations: ");
  scanf("%d",&basic);
  
  printf("Enter number of variables in the equation: ");
  scanf("%d",&var);
  
  total = basic + var;
  
  for(j=0;j<=total;j++)
    Z[j] = 0;
  
  for(j=0;j<=basic;j++)
    B[j] = 0;
  
  for(j=0;j<basic;j++)
    check[j] = var + j + 1;
  
  for(i=0;i<=basic;i++)
    {
      for(j=0;j<=total;j++)
	A[i][j] = 0;
    }
  
  printf("Enter the coefficients of variables. \n");
  
  for(j=0;j<basic;j++)
    {
      printf("for equation %d : ",j+1);
      for(i=0;i<var;i++)
	scanf("%f",&A[j][i]);
      
      printf("Right side element: ");
      scanf("%f",&B[j]);
      A[j][var+basic] = B[j];
      
      d = getchar();
      printf("Enter the equality if greater than or less than(Enter G or L): ");
      scanf("%c",&C);
      
      if(C == 'G')
	{
	  for(i=0;i<var;i++)
	    A[j][i] = (-1)*A[j][i];
	  A[j][total] = (-1)*A[j][total];
	  B[j] = (-1)*B[j]; 
	}
    }
  
  for(i=0;i<basic;i++) 
    A[i][var+i] = 1;
  
  printf("Enter the maximization function(if minimization function then multiply coefficients by -1 and then enter:\n ");
  for(i=0;i<var;i++)
    {
      scanf("%f",&Z[i]);
      A[basic][i] = Z[i];
    }
  
  for(i=0;i<=basic;i++)
    {
      for(j=0;j<=total;j++)
	printf("%0.2f\t",A[i][j]);
      printf("\n");
    }
  
  do{
    max = 0;
    for(i=0;i<basic;i++)
      {
	if(B[i] < max )
	  {
	    max = B[i];
	    t1 = i;
	  }
      }
    
    min = 9999;
    for(i=0;i<total;i++)
      {	
	X[i] = Z[i] / A[t1][i];
	if(X[i] < min && X[i] > 0)
	  {
	    min = X[i];
	    t2 = i;
	  }
      }
    
    check[t1] = t2 + 1;
    
    divi = A[t1][t2];
    for(i=0;i<=total;i++)
      A[t1][i] = A[t1][i] / divi;
    
    for(i=0;i<=basic;i++)
      {
	if(i != t1)
	  {	
	    multi = A[i][t2];
	    for(j=0;j<=total;j++)
	      A[i][j] = A[i][j] - multi*A[t1][j];
	  }
      }
    
    for(i=0;i<total;i++)
      Z[i] = A[basic][i];
    
    for(i=0;i<basic;i++)
      B[i] = A[i][total];
    
    Z[total] = Z[total] + multi * A[t1][total];
    A[basic][total] = Z[total];
    
  }while(temp(B,basic) != 0);
  
  printf("\nMaximum value of z is %f which occurs at ",A[basic][total]);
  for(i=0;i<basic;i++)
    printf("x[%d] = %f \t",check[i],A[i][total]);
  printf("\n");
  return 1;	 
}

/*OUTPUT

[fist@fist34 ~]$ cd kunal
[fist@fist34 kunal]$ cc dualsimplex.c
[fist@fist34 kunal]$ ./a.out
***************Dual-simplex method****************
Enter the number of equations: 3
Enter number of variables in the equation: 2
Enter the coefficients of variables.
for equation 1 : 1 1
Right side element: 10
Enter the equality if greater than or less than(Enter G or L): G
for equation 2 : 1 2
Right side element: 11
Enter the equality if greater than or less than(Enter G or L): G
for equation 3 : 1 4
Right side element: 16
Enter the equality if greater than or less than(Enter G or L): G
Enter the maximization function(if minimization function then multiply coefficients by -1 and then enter:
 -1 -3
-1.00   -1.00   1.00    0.00    0.00    -10.00
-1.00   -2.00   0.00    1.00    0.00    -11.00
-1.00   -4.00   0.00    0.00    1.00    -16.00
-1.00   -3.00   0.00    0.00    0.00    0.00

Maximum value of z is -14.000000 which occurs at x[1] = 8.000000        x[4] = 1.000000         x[2] = 2.000000
[fist@fist34 kunal]$

*/
