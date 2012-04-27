
#include <stdio.h>
#include <math.h>
#define SIZE 10

int temp(float Z[SIZE], int total_var);

int main()
{
	int i,j;
	int basic_var,var,total_var;
	float A[SIZE][SIZE]; 
	float B[SIZE],Z[SIZE],X[SIZE];
	float max,min;
	int temp_1,temp_2;
	float multiplying_factor,dividing_factor;
	int track[SIZE];

   	printf("Program to solve LPP using simplex method introducing slack variables. \n");

	printf("Number of equations are : ");
	scanf("%d",&basic_var);

	printf("Enter number of variables in equation present : ");
	scanf("%d",&var);
	
	total_var = basic_var + var;
	for(i=0;i<=total_var;i++)
	{
		for(j=0;j<total_var;j++)
			A[i][j] = 0;
	}

	for(j=0;j<=total_var;j++)
			Z[j] = 0;
	
	for(j=0;j<=basic_var;j++)
			B[j] = 0;
	
	for(j=0;j<basic_var;j++)
		track[j] = var + j + 1;

	printf("Enter the coefficients of variables. \n");
   
	for(j=0;j<basic_var;j++)
	{
		printf("for equation %d : ",j);
		for(i=0;i<var;i++)
			scanf("%f",&A[j][i]);
	}
	
	for(i=0;i<basic_var;i++)
		A[i][var+i] = 1;
	
	printf("The right side matrix is: ");
	for(i=0;i<basic_var;i++)
	{
		scanf("%f",&B[i]);
		A[i][total_var] = B[i];
	}
	
	printf("Enter the coefficients of maximization function : ");
	for(i=0;i<var;i++)
	{
		scanf("%f",&Z[i]);
		A[basic_var][i] = Z[i];
	}
	
	do{
		max = 0;
		for(i=0;i<total_var;i++)
		{
			if(Z[i] > max )
			{
				max = Z[i];
				temp_1 = i;
			}
		}
		printf("entering variable : x[%d] \n",temp_1+1);
		
		min = 9999;
		for(i=0;i<basic_var;i++)
		{	
			X[i] = A[i][total_var] / A[i][temp_1];
			if(X[i] < min && X[i] > 0)
				{
					min = X[i];
					temp_2 = i;
				}
		}
		printf("leaving variable = x[%d]\n",var + temp_2 + 1); 
		track[temp_2] = temp_1 + 1;
		
		dividing_factor = A[temp_2][temp_1];
		for(i=0;i<=total_var;i++)
			A[temp_2][i] = A[temp_2][i] / dividing_factor;
	
		for(i=0;i<=basic_var;i++)
		{
			if(i != temp_2)
			{	
				multiplying_factor = A[i][temp_1];
				for(j=0;j<=total_var;j++)
					A[i][j] = A[i][j] - multiplying_factor*A[temp_2][j];
			}
		}
		
		for(i=0;i<total_var;i++)
			Z[i] = A[basic_var][i];

		Z[total_var] = Z[total_var] + multiplying_factor * A[temp_2][total_var];
		A[basic_var][total_var] = Z[total_var];

	}while(temp(Z,total_var) != 0);

	printf("Maximum value of z is : %f occurs at ",A[basic_var][total_var]);
	for(i=0;i<basic_var;i++)
		printf("x[%d] = %f \t",track[i],A[i][total_var]);
	return 1;	 
}

	int temp(float Z[SIZE], int total_var)
	{
	int i;
	int count = 0;
	for(i=0;i<total_var;i++)
	{
		if( Z[i] > 0)
			count = 1;
	}
	return count;
	}




















/***    OUTPUT 1 : 

	Program to solve LPP using simplex method introducing slack variables.
	Number of equations are : 4
	Enter number of variables in equation present : 2
	Enter the coefficients of variables.
	for equation 0 : 1 2
	for equation 1 : 1 1
	for equation 2 : 1 -1
	for equation 3 : 1 -2
	The right side matrix is: 10 6 2 1
	Enter the coefficients of maximization function : 2 1
	entering variable : x[1]
	leaving variable = x[6]
	entering variable : x[2]
	leaving variable = x[5]
	entering variable : x[6]
	leaving variable = x[4]
	Maximum value of z is : 10.000000 occurs at x[3] = 2.000000     x[6] = 1.000000
        x[2] = 2.000000         x[1] = 4.000000


  	OUTPUT 2 :

	Program to solve LPP using simplex method introducing slack variables.
	Number of equations are : 3
	Enter number of variables in equation present : 2
	Enter the coefficients of variables.
	for equation 0 : 1 1
	for equation 1 : 1 4
	for equation 2 : 10 20
	The right side matrix is: 100 160 1100
	Enter the coefficients of maximization function : 40 120
	entering variable : x[2]
	leaving variable = x[4]
	entering variable : x[1]
	leaving variable = x[5]
	Maximum value of z is : 5400.000000 occurs at x[3] = 15.000000  x[2] = 25.000000
        x[1] = 60.000000

*****************/
