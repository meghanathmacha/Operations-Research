
#include <stdio.h>
#include <math.h>
#define SIZE 10
#define M 1000

int temp(float Z[SIZE], int total_var);

int main()
{
	int i,j;
	int basic_var,var,total_var;
	float A[SIZE][SIZE]; 
	float B[SIZE],Z[SIZE],X[SIZE],Y[SIZE];
	float min;
	int temp_1,temp_2;
	float multiplying_factor,dividing_factor;
	int track[SIZE];

   printf("Program to solve LPP using Big M method introducing surplus and artificial variables. \n");

	printf("Number of equations are : ");
	scanf("%d",&basic_var);

	printf("Enter number of variables in equation present : ");
	scanf("%d",&var);
	
	total_var = 2*basic_var + var;
	for(i=0;i<=basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			A[i][j] = 0;
	}

	for(j=0;j<=total_var;j++)
			Z[j] = 0;
	
	for(j=0;j<=basic_var;j++)
			B[j] = 0;
	
	for(j=0;j<basic_var;j++)
		track[j] = basic_var + var + j + 1;

	printf("Enter the coefficients of variables. \n");
   
	for(j=0;j<basic_var;j++)
	{
		printf("for equation %d : ",j+1);
		for(i=0;i<var;i++)
			scanf("%f",&A[j][i]);
	}
	
	for(i=0;i<basic_var;i++)
	{
		A[i][var+i] = -1;
		A[i][var+basic_var+i] = 1;
	}
	
	printf("The right side matrix is: ");
	for(i=0;i<basic_var;i++)
	{
		scanf("%f",&B[i]);
		A[i][total_var] = B[i];
	}
	
	printf("Enter the coefficients of minimization function : ");
	for(i=0;i<var;i++)
	{
		scanf("%f",&Z[i]);
		A[basic_var][i] = Z[i];
		Y[i] = Z[i];
	}
	
	for(i=0;i<basic_var;i++)
		Z[basic_var+ var+i] = M;

	for(i=0;i<basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			Z[j] = Z[j] - M*A[i][j];	
	}
	
	Z[total_var] = 0;
	for(j=0;j<=total_var;j++)
		A[basic_var][j] = Z[j];


	for(i=0;i<=basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			printf("%0.2f\t",A[i][j]);
		printf("\n");
	}

	do{
		min = 9999;
		for(i=0;i<total_var;i++)
		{
			if(Z[i] < min && Z[i] < 0)
			{
				min = Z[i];
				temp_1 = i;
			}
		}

		printf("entering variable : x[%d] \n",temp_1+1);
		
		min = 9999;
		for(i=0;i<basic_var;i++)
		{	
			X[i] = A[i][total_var] / A[i][temp_1];
			if(X[i] <= min && X[i] >= 0)
				{
					min = X[i];
					temp_2 = i;
				}
		}
		printf("leaving variable = x[%d]\n",track[temp_2]); 
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

		Z[total_var] = 0;
		A[basic_var][total_var] = Z[total_var];


	for(i=0;i<=basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			printf("%0.2f\t",A[i][j]);
		printf("\n");
	}

	}while(temp(Z,total_var) != 0);



	for(i=0;i<=basic_var;i++)
	{
		for(j=0;j<=total_var;j++)
			printf("%0.2f\t",A[i][j]);
		printf("\n");
	}

	for(i=0;i<basic_var;i++)
	{
		for(j=0;j<basic_var;j++)
		{
		if(track[j]-1 == i)
				Z[total_var] =  Y[i] * A[j][total_var] + Z[total_var];
		}
	}

	printf("\nMin value of Z is : %f \n",Z[total_var]);

/*	printf("Minimum value of z is : %f occurs at ",A[basic_var][total_var]);
	for(i=0;i<basic_var;i++)
		printf("x[%d] = %f \t",track[i],A[i][total_var]);*/
	return 1;	 
}

	int temp(float Z[SIZE], int total_var)
	{
	int i;
	int count = 0;
	for(i=0;i<total_var;i++)
	{
		if( Z[i] < 0 && (int)Z[i] != -0)
			count = 1;
	}
	return count;
	}


/* OUTPUT 1  **************

Program to solve LPP using Big M method introducing surplus and artificial varia
bles.
Number of equations are : 3
Enter number of variables in equation present : 2
Enter the coefficients of variables.
for equation 1 : 1 1
for equation 2 : 1 2
for equation 3 : 1 4
The right side matrix is: 100 120 160
Enter the coefficients of minimization function : 1 4
1.00    1.00    -1.00   0.00    0.00    1.00    0.00    0.00    100.00
1.00    2.00    0.00    -1.00   0.00    0.00    1.00    0.00    120.00
1.00    4.00    0.00    0.00    -1.00   0.00    0.00    1.00    160.00
-2999.00        -6996.00        1000.00 1000.00 1000.00 0.00    0.00    0.00
0.00
entering variable : x[2]
leaving variable = x[8]
entering variable : x[1]
leaving variable = x[7]
entering variable : x[4]
leaving variable = x[6]
0.00    0.00    -0.67   1.00    -0.33   0.67    -1.00   0.33    0.00
1.00    0.00    -1.33   0.00    0.33    1.33    0.00    -0.33   80.00
0.00    1.00    0.33    0.00    -0.33   -0.33   0.00    0.33    20.00
0.00    0.00    -0.00   0.00    1.00    1000.00 1000.00 999.00  0.00

Min value of Z is : 160.000000

OUTPUT 2 ***********

Program to solve LPP using Big M method introducing surplus and artificial varia
bles.
Number of equations are : 2
Enter number of variables in equation present : 2
Enter the coefficients of variables.
for equation 1 : 2 3
for equation 2 : 5 2
The right side matrix is: 8 12
Enter the coefficients of minimization function : 3 4
2.00    3.00    -1.00   0.00    1.00    0.00    8.00
5.00    2.00    0.00    -1.00   0.00    1.00    12.00
-6997.00        -4996.00        1000.00 1000.00 0.00    0.00    0.00
entering variable : x[1]
leaving variable = x[6]
entering variable : x[2]
leaving variable = x[5]
0.00    1.00    -0.45   0.18    0.45    -0.18   1.45
1.00    0.00    0.18    -0.27   -0.18   0.27    1.82
0.00    0.00    1.27    0.09    998.73  999.91  0.00

Min value of Z is : 11.272728

*/
