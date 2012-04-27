
#include <stdio.h>
#include <math.h>
#define SIZE 10

int temp1(float Z[SIZE], int total_var);
int main()
{
	int i,j,count;
	int basic_var,var,total_var;
	float A[SIZE][SIZE]; 
	float B[SIZE],Z[SIZE],X[SIZE],Y[SIZE],P[SIZE][SIZE],W[SIZE];
	char C[SIZE];
	float min;
	int temp[SIZE],row[SIZE],col[SIZE];
	int temp_1,temp_2;
	float multiplying_factor,dividing_factor,y;
	int track[SIZE];

   printf("Program to solve LPP using Two Phase Method introducing slack,surplus and artificial variables. \n");

	printf("Number of equations are : ");
	scanf("%d",&basic_var);

	printf("Enter number of variables in equation present : ");
	scanf("%d",&var);
   
	for(j=0;j<=basic_var;j++)
	{
		B[j] = 0;
		row[j] = -1;
	}

	for(j=0;j<SIZE;j++)
		temp[j] = 0;

	total_var = var;
	for(j=0;j<basic_var;j++)
	{
		printf("for equation %d : \n",j+1);
		printf("Enter the coefficients of variables. ");
		for(i=0;i<var;i++)
			scanf("%f",&P[j][i]);

		printf("Enter the right hand side value : ");
		scanf("%f",&B[j]);
		
		C[j] = getchar();
		printf("Enter the equality in between < / > / = ,i.e, L/G/E respectively : ");
		scanf("%c",&C[j]);
		
		if(C[j] == 'E')
			{
				temp[j] = total_var ;
				row[j] = j;
				total_var = total_var + 1;	
				col[j] = total_var;
			}

		if(C[j] == 'G')
			{
				temp[j] = total_var + 1 ;
				row[j] = j;
				total_var = total_var + 2;
				col[j] = total_var;
			}

		if(C[j] == 'L')	
			total_var = total_var + 1;
	}

	for(i=0;i<=basic_var+1;i++)
	{
		for(j=0;j<=total_var;j++)
			A[i][j] = 0;
	}

	for(j=0;j<=total_var;j++)
		Z[j] = 0;

	count = var-1;
	for(i=0;i<basic_var;i++)
	{
		for(j=0;j<var;j++)
			A[i][j] = P[i][j];
		
		if(C[i] == 'G')
			{
				A[i][count+1] = -1;
				A[i][count+2] = 1;
				track[i] = count + 3; 
				count = count + 2;
			}
		if(C[i] == 'L')
			{
				A[i][count+1] = 1;
				track[i] = count+2;
				count = count +1;
			}
		if(C[i] == 'E')
			{	
				A[i][count+1] = 1;
				track[i] = count+2;
				count = count + 1;
			}
		A[i][total_var] = B[i];
	}

	//Phase 1 starts
	for(i=0;i<=basic_var;i++)
	{
		if(row[i] != -1)
		{
			W[temp[i]] = 1;
			A[basic_var][temp[i]] = W[temp[i]];
		}
	}

	for(i=0;i<basic_var;i++)
	{
		if(row[i] != -1)
		{
			for(j=0;j<total_var;j++)
				A[basic_var][j] = -A[i][j] + A[basic_var][j];
			A[basic_var][total_var] += A[i][total_var];
		}
	}
	for(i=0;i<=total_var;i++)
		W[i] = A[basic_var][i];

	printf("\nIf objective function is maximum type, multiply coefficents by -1 and then enter,i.e., convert it in minimization function: \n");
	printf("Enter the coefficients of objective function : "); 
	for(i=0;i<var;i++)
	{
		scanf("%f",&Z[i]);
		A[basic_var+1][i] = Z[i];
		Y[i] = Z[i];
	}
	
	printf("\n");
	for(i=0;i<=basic_var+1;i++)
	{
		for(j=0;j<=total_var;j++)
			printf("%0.2f\t",A[i][j]);
		printf("\n");
	}
	printf("\n");

	do{
		min = 9999;
		for(i=0;i<total_var;i++)
		{
			if(W[i] < min && W[i] < 0)
			{
				min = W[i];
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
	
		for(i=0;i<=basic_var+1;i++)
		{
			if(i != temp_2)
			{	
				multiplying_factor = A[i][temp_1];
				if(i == basic_var)
					y = multiplying_factor;
				for(j=0;j<=total_var;j++)
					A[i][j] = A[i][j] - multiplying_factor*A[temp_2][j];
			}
		}

		A[basic_var][total_var] += 2*y*A[temp_2][total_var];
		
		for(i=0;i<=total_var;i++)
			W[i] = A[basic_var][i];
		
	}while(temp1(W,total_var) != 0);

		for(i=0;i<=total_var;i++)
		{
			if((int)A[basic_var][i] == -0)
				A[basic_var][i] = 0;
		}

	A[basic_var+1][total_var] = (-1)* A[basic_var+1][total_var];

	printf("\nAt the end of Phase 1: \n");
	for(i=0;i<=basic_var+1;i++)
	{
		for(j=0;j<=total_var;j++)
			printf("%0.2f\t",A[i][j]);
		printf("\n");
	}
	printf("\n");

	W[total_var] = A[basic_var][total_var];
	if(W[total_var] > 0)
		printf("No optimal feasible solution \n");

	if(W[total_var] < 0)
		printf("Incorrect result");
	
	// phase 2 starts
	if(W[total_var] == 0)
		{
		for(i=0;i<=basic_var+1;i++)
		{
			for(j=0;j<basic_var;j++)
				A[i][col[j]-1] = 0;
		}
		
		for(i=0;i<=total_var;i++)
		{
			A[basic_var][i] = A[basic_var+1][i];
			Z[i] = A[basic_var][i];
		}

		printf("Table for Phase 2 is: \n");
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
				if(X[i] <= min && X[i] > 0)
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
			A[basic_var][total_var] += 2*multiplying_factor*A[temp_2][total_var];

			for(i=0;i<total_var;i++)
				Z[i] = A[basic_var][i];

		}while(temp1(Z,total_var) != 0);
		printf("\nMinimum value of Z is : %0.2f \n",Z[total_var]);
	}		
	return 1 ;
}


	int temp1(float W[SIZE], int total_var)
	{
	int i;
	int count = 0;
	for(i=0;i<total_var;i++)
	{
		if( W[i] < 0 && (int)W[i] != -0)
			count = 1;
	}
	return count;
	}

/* OUTPUT 1: 

Program to solve LPP using Two Phase Method introducing slack,surplus and artifi
cial variables.
Number of equations are : 2
Enter number of variables in equation present : 3
for equation 1 :
Enter the coefficients of variables. 1 1 0
Enter the right hand side value : 2
Enter the equality in between < / > / = ,i.e, L/G/E respectively : G
for equation 2 :
Enter the coefficients of variables. 2 0 1
Enter the right hand side value : 5
Enter the equality in between < / > / = ,i.e, L/G/E respectively : G

If objective function is maximum type, multiply coefficents by -1 and then enter
,i.e., convert it in minimization function:
Enter the coefficients of objective function : 4 8 3

1.00    1.00    0.00    -1.00   1.00    0.00    0.00    2.00
2.00    0.00    1.00    0.00    0.00    -1.00   1.00    5.00
-3.00   -1.00   -1.00   1.00    0.00    1.00    0.00    7.00
4.00    8.00    3.00    0.00    0.00    0.00    0.00    0.00

entering variable : x[1]
leaving variable = x[5]
entering variable : x[4]
leaving variable = x[7]

At the end of Phase 1:
1.00    0.00    0.50    0.00    0.00    -0.50   0.50    2.50
0.00    -1.00   0.50    1.00    -1.00   -0.50   0.50    0.50
0.00    0.00    0.00    0.00    1.00    0.00    1.00    0.00
0.00    8.00    1.00    0.00    0.00    2.00    -2.00   10.00

Table for Phase 2 is:
1.00    0.00    0.50    0.00    0.00    -0.50   0.00    2.50
0.00    -1.00   0.50    1.00    0.00    -0.50   0.00    0.50
0.00    8.00    1.00    0.00    0.00    2.00    0.00    10.00
entering variable : x[4]
leaving variable = x[4]

Minimum value of Z is : 10.00


OUTPUT 2:

Program to solve LPP using Two Phase Method introducing slack,surplus and artifi
cial variables.
Number of equations are : 2
Enter number of variables in equation present : 2
for equation 1 :
Enter the coefficients of variables. 2 1
Enter the right hand side value : 1
Enter the equality in between < / > / = ,i.e, L/G/E respectively : L
for equation 2 :
Enter the coefficients of variables. 3 4
Enter the right hand side value : 12
Enter the equality in between < / > / = ,i.e, L/G/E respectively : G

If objective function is maximum type, multiply coefficents by -1 and then enter
,i.e., convert it in minimization function:
Enter the coefficients of objective function : -5 -3

2.00    1.00    1.00    0.00    0.00    1.00
3.00    4.00    0.00    -1.00   1.00    12.00
-3.00   -4.00   0.00    1.00    0.00    12.00
-5.00   -3.00   0.00    0.00    0.00    0.00

entering variable : x[2]
leaving variable = x[3]

At the end of Phase 1:
2.00    1.00    1.00    0.00    0.00    1.00
-5.00   0.00    -4.00   -1.00   1.00    8.00
5.00    0.00    4.00    1.00    0.00    8.00
1.00    0.00    3.00    0.00    0.00    -3.00

No optimal feasible solution

*/
