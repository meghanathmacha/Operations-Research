#include <stdio.h>
#include <math.h>
#define SIZE 20

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

  if(count != 0)
    {
      for(j=0;j<n;j++)
	  C[j] = A[j][i];                   
    }
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
}

void inverse(float A[SIZE][SIZE], int basic_var)
{
	float C[SIZE];
  	float B[SIZE][SIZE];
  	float inverseB[SIZE][SIZE];
  	float P[SIZE][SIZE];
  	float E[SIZE];
  	int i,j,n,k;

	n = basic_var;
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

	for(k=0;k<n;k++)
    {
      for(j=0;j<n;j++)
			A[k][j] = inverseB[k][j];
    }
}

void multiply_1(float Y[SIZE],float CB[SIZE],float B[SIZE][SIZE],int basic_var)
{
	int i,j;
	for(i=0;i<basic_var;i++)
		Y[i] = 0;

	for(i=0;i<basic_var;i++)
	{
		for(j=0;j<basic_var;j++)
			Y[i] = Y[i] + CB[j]*B[j][i];
	}
}

void multiply_2(float Z[SIZE],float Y[SIZE],float P[SIZE][SIZE],int i,int basic_var)
{
	int j;
	Z[i] = 0;

	for(j=0;j<basic_var;j++)
		Z[i] = Z[i] + Y[j]*P[i][j];
}

void multiply_3(float X[SIZE],float B[SIZE][SIZE],float D[SIZE],int basic_var)
{
	int i,j;
	for(i=0;i<basic_var;i++)
		X[i] = 0;

	for(i=0;i<basic_var;i++)
	{
		for(j=0;j<basic_var;j++)
			X[i] = X[i] + B[i][j]*D[j];
	}
}

void subtract(float Z[SIZE],float W[SIZE],int i)
{
	Z[i] = Z[i] - W[i];
}

int min(float Z[SIZE],int total_var)
{
	int i;
	int min = 999;
	int temp_1 = 100;
	for(i=0;i<total_var;i++)
	{
		if(Z[i]<min && Z[i]<0)
		{
			min = Z[i];
			temp_1 = i;
		}
	}	
	return temp_1;
}

int max(float X[SIZE],int basic_var)
{
	int i;
	int max = 0;
	int temp_2 = 100;
	for(i=0;i<basic_var;i++)
	{
		if(X[i] > max)
		{
			max = X[i];
			temp_2 = i;
		}
	}
	return temp_2;
}

int main()
{
	int i,j;
	int basic_var,var,total_var;
	float A[SIZE][SIZE],B[SIZE][SIZE],P[SIZE][SIZE]; 
	float Z[SIZE],X[SIZE],W[SIZE],D[SIZE],CB[SIZE],Y[SIZE];
	int track[SIZE];
	int count;
	int maximum, minimum;
	float sum = 0;

   printf("Program to solve LPP using revised simplex method introducing slack variables.\n");

	printf("Number of equations are : ");
	scanf("%d",&basic_var);

	printf("Number of variables present in equation are : ");
	scanf("%d",&var);
	
	total_var = basic_var + var;
	for(i=0;i<=basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			A[i][j] = 0;
	}

	for(j=0;j<=total_var;j++)
	{	
		D[j] = 0;
		W[j] = 0;
		Z[j] = 0;
	}
	
	for(j=0;j<basic_var;j++)
		track[j] = var + j + 1;

	printf("Enter the coefficients of variables. \n");
   
	for(j=0;j<basic_var;j++)
	{
		printf("for equation %d : ",j+1);
		for(i=0;i<var;i++)
			scanf("%f",&A[j][i]);

		printf("The right side matrix is: ");
		scanf("%f",&D[j]);
		A[j][total_var] = D[j];
	}
	
	for(i=0;i<basic_var;i++)
		A[i][var+i] = 1;
		
	printf("Enter the coefficients of maximization function : ");
	for(i=0;i<var;i++)
	{
		scanf("%f",&W[i]);
		A[basic_var][i] = W[i];
	}

	for(i=0;i<total_var;i++)
	{
		for(j=0;j<basic_var;j++)
			P[i][j] = A[j][i];
	}

	for(i=0;i<basic_var;i++)
		B[i][i] = 1;

	for(i=0;i<=basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			printf("%0.2f\t",A[i][j]);
		printf("\n");
	}

	for(i=0;i<total_var;i++)
	{
		printf("P[%d] is : \t",i+1);
		for(j=0;j<basic_var;j++)
			printf("%0.2f\t",P[i][j]);
		printf("\n");
	}

	//loop starts
	do{
		printf("\nB matrix is :\n");
		for(i=0;i<basic_var;i++)
		{
			for(j=0;j<basic_var;j++)
				printf("%0.2f\t",B[i][j]);
			printf("\n");
		}

		// Finding inverse of B
		inverse(B,basic_var); 
		printf("\nB inverse is: \n");
		for(i=0;i<basic_var;i++)
		{
			for(j=0;j<basic_var;j++)
				printf("%0.2f\t",B[i][j]);
			printf("\n");
		}

	// Coefficients of basic variable
		for(i=0;i<basic_var;i++)
			CB[i] = A[basic_var][track[i]-1];

	multiply_1(Y,CB,B,basic_var);
	
	printf("\nY = CB(transpose) * B(inverse) is\n");
	for(j=0;j<basic_var;j++)
		printf("%0.2f\t",Y[j]);
	printf("\n");
	
	for(i=0;i<total_var;i++)
	{
		count = 0;
		for(j=0;j<basic_var;j++)
		{
			if(i == track[j]-1)
			{
				count = 1;
				Z[i] = 0;
			}
		}
		
		if(count != 1)
		{
			multiply_2(Z,Y,P,i,basic_var);
			subtract(Z,W,i);
		}
	}

 	//ENTERING VARIABLE, returns the position
	minimum = min(Z,total_var);
	multiply_3(X,B,D,basic_var);

	// LEAVING VARIABLE, returns the position
	maximum = max(X,basic_var); 
	if(maximum == 100)
	{
		printf("Unbounded Solution\n");
		break;
	}
	if(minimum != 100)
	{
		printf("enetering variable is : x[%d]\n",minimum+1);
		printf("leaving variable is : x[%d]\n",track[maximum]);
		track[maximum] = minimum+1;
	}

	printf("\nThe X (solution) matrix is : \n");
	for(i=0;i<basic_var;i++)
		printf("%0.2f\t",X[i]);
	printf("\n");


	for(j=0;j<basic_var;j++)
		B[j][maximum] = A[j][minimum];

	}while(min(Z,total_var) != 100 );

	if(maximum != 100)
	{
		for(i=0;i<basic_var;i++)
			sum = sum + CB[i]*X[i];
		printf("Maximum value of Z is %0.2f which occurs at\n",sum);
		for(i=0;i<basic_var;i++)
			printf("X[%d] = %0.2f \t",track[i],X[i]); 
	}
	printf("\n");
	return 1;	 
}
	
/* OUTPUT : 

Program to solve LPP using revised simplex method introducing slack variables.
Number of equations are : 2
Number of variables present in equation are : 3
Enter the coefficients of variables.
for equation 1 : 1 4 1
The right side matrix is: 24
for equation 2 : 1 5 2
The right side matrix is: 30
Enter the coefficients of maximization function : 2 3 4
1.00    4.00    1.00    1.00    0.00    24.00
1.00    5.00    2.00    0.00    1.00    30.00
2.00    3.00    4.00    0.00    0.00    0.00
P[1] is :       1.00    1.00
P[2] is :       4.00    5.00
P[3] is :       1.00    2.00
P[4] is :       1.00    0.00
P[5] is :       0.00    1.00

B matrix is :
1.00    0.00
0.00    1.00

B inverse is:
1.00    -0.00
-0.00   1.00

Y = CB(transpose) * B(inverse) is
0.00    0.00
enetering variable is : x[3]
leaving variable is : x[5]

The X (solution) matrix is :
24.00   30.00

B matrix is :
1.00    1.00
-0.00   2.00

B inverse is:
1.00    -0.50
0.00    0.50

Y = CB(transpose) * B(inverse) is
0.00    2.00

The X (solution) matrix is :
9.00    15.00
Maximum value of Z is 60.00 which occurs at
X[4] = 9.00     X[3] = 15.00

*/	
	




