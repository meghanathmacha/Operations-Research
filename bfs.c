 #include <stdio.h>
 #include <math.h>
 #define SIZE 100
 
 char case_matrix[100];
 int cases[100][100];
 int l = 0;
 
 void printc(int comb[], int k);
 int next_comb(int comb[], int k, int m);
 void rank(float coefficient_matrix[SIZE][SIZE], float solution_matrix[SIZE], int eq);
 void solution(float coefficient_matrix[SIZE][SIZE], float solution_matrix[SIZE], int eq);

 int main()
 {
	int i,j;
	float A[SIZE][SIZE];
	float B[SIZE];
	int var;
	int eq;
	int p,q;
	float arrayA[SIZE][SIZE];
	float arrayB[SIZE];
	
	printf("How many equations are there ?\n");
	scanf("%d",&eq);
	
	printf("How many varaibles does the equations contain? \n");
	scanf("%d",&var);
	
	printf("Enter the coefficient matrix :\n");
	for(i=0;i<eq;i++)
	{
		for(j=0;j<var;j++)
		    scanf("%f",&A[i][j]);
	}
	
	for(i=0;i<eq;i++)
	{
		for(j=0;j<var;j++)
			printf(" %f \t",A[i][j]);
		printf("\n");
	}
	
	printf("the RHS matrix is :\n");
	for(i=0;i<eq;i++)
	 {
	  scanf("%f",&B[i]);
	  printf("B[%d] = %f \n",i,B[i]);
	 }
	
	int m = var;                         /* The size of the set; for {1, 2, 3, 4} it's 4 */
	int k = eq;                          /* The size of the subsets; for {1, 2}, {1, 3}, ... it's 2 */
	int comb[100];                       /* comb[i] is the index of the i-th element in the combination */
	                                     
	for(i = 0; i < k; ++i)               /* Setup comb for the initial combination */
		comb[i] = i;

	printc(comb, k);                     /* Print the first combination */

	while (next_comb(comb, k, m))        /* Generate and print all the other combinations */     
		    printc(comb, k);
		
	printf("\n \nThus no. of cases are : %d\n\n", l);
	
	for(i = 0 ; i< l ; i++)
	{
		for(q =0;q<k;q++)
		   {
		    for(p=0;p<k;p++)
		      {
			     arrayA[p][q] = A[p][cases[i][q]-1];
			     arrayB[p] = B[p];
			   }	
		   }
		   		 
	    rank(arrayA,arrayB,k);
	    solution(arrayA,arrayB,k);
	 
	    printf("Thus Basic Variables for case[%d]  are : \n",i+1);
		
	    for(p=0;p<k;p++)
		     printf("x[%d] = %f \n",cases[i][p],arrayB[p]);
		     
		 printf("Variables which do not occur are zero, known as Non basic variables \n \n \n");    

	 }
	 
	 return 0;
 }
	
	
	void rank(float coefficient_matrix[SIZE][SIZE], float solution_matrix[SIZE], int eq)
	{
		int i,j;
		int k,l;
		int n = eq;
		float multiplying_factor;
		
		for(i=0;i<n;i++)
		{
			float dividing_factor = coefficient_matrix[i][i];
			for(j=i;j<n;j++)
			  coefficient_matrix[i][j] = coefficient_matrix[i][j] / dividing_factor; 
			   	  
			solution_matrix[i] = solution_matrix[i] / dividing_factor;
			 			  
			 for(k=i+1;k<n;k++)
			  {
				  multiplying_factor = coefficient_matrix[k][i];
				  solution_matrix[k] = solution_matrix[k] - solution_matrix[i] * multiplying_factor;
				  
				  for(l=i;l<n;l++)
			  			coefficient_matrix[k][l] = coefficient_matrix[k][l] - (coefficient_matrix[i][l] * multiplying_factor);
			  }
			  
		}
	}
		
		
	void solution(float coefficient_matrix[SIZE][SIZE], float solution_matrix[SIZE], int eq)
	{
		int i,j;
		int n = eq;
			
		for(i=n-2;i>=0;i--)
       {	
         for(j=i;j<n;j++)
	         solution_matrix[i] = solution_matrix[i] - (coefficient_matrix[i][j+1] * solution_matrix[j+1]);	
	    }
	}
			    

   void printc(int comb[], int k) 
   {
	  int i;       
	  for (i = 0; i < k; ++i)
    		cases[l][i] = comb[i] + 1;	
	  l = l+1;
	  
   }
   
   
   int next_comb(int comb[], int k, int m)
   {
	  int i = k - 1;
	  ++comb[i];
	  while ((i >= 0) && (comb[i] >= m - k + 1 + i))
	   {
		      --i;
		      ++comb[i];
	   }
	   
	  if (comb[0] > m - k)                                /* Combination (n-k, n-k+1, ..., n) reached */
		   return 0;                                       /* No more combinations can be generated */
                                                    
	  for (i = i + 1; i < k; ++i)                         /* comb now looks like (..., x, n, n, n, ..., n). Turn it into (..., x, x + 1, x + 2, ...) */    
		    comb[i] = comb[i - 1] + 1;

	  return 1;	  
    }


// OUTPUT
/*

How many equations are there ?
2
How many varaibles does the equations contain?
5
Enter the coefficient matrix :
3 4 1 2 4
2 2 3 5 2
 3.000000        4.000000        1.000000        2.000000        4.000000

 2.000000        2.000000        3.000000        5.000000        2.000000

the RHS matrix is :
10 20
B[0] = 10.000000
B[1] = 20.000000


Thus no. of cases are : 10

Thus Basic Variables for case[1]  are :
x[1] = 29.999998
x[2] = -19.999998
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[2]  are :
x[1] = 1.428571
x[3] = 5.714286
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[3]  are :
x[1] = 0.909091
x[4] = 3.636364
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[4]  are :
x[1] = 29.999998
x[5] = -19.999998
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[5]  are :
x[2] = 1.000000
x[3] = 6.000000
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[6]  are :
x[2] = 0.625000
x[4] = 3.750000
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[7]  are :
x[2] = -1.#INF00
x[5] = 1.#INF00
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[8]  are :
x[3] = -10.000000
x[4] = 10.000000
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[9]  are :
x[3] = 6.000000
x[5] = 1.000000
Variables which do not occur are zero, known as Non basic variables


Thus Basic Variables for case[10]  are :
x[4] = 3.750000
x[5] = 0.625000
Variables which do not occur are zero, known as Non basic variables


*/
