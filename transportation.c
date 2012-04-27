
#include<stdio.h>
int main()
{
  int input[100][100],cost[100][100];
  int s,d,i,j,count,sum;
  printf("\n-------solving by northwest corner method-------\n");
  printf("\nenter the number of sources and destination:");
  scanf("%d%d",&s,&d);
  for(i=0;i<=s;i++)
    for(j=0;j<=d;j++)
      {
	input[i][j]=0;
	cost[i][j]=0;
      }
  printf("\n enter the supply of each source");
  for(i=0;i<s;i++)
    scanf("%d",&input[i][d]);
  printf("\n enter the demand of each destination");
  for(j=0;j<d;j++)
    scanf("%d",&input[s][j]);
  printf("\n enter the cost for shipping for each combination:");
  for(i=0;i<s;i++)
    for(j=0;j<d;j++)
      scanf("%d",&cost[i][j]);
   for(i=0;i<=s;i++)
    {
      for(j=0;j<=d;j++)
	{
	  printf("%d ",input[i][j]);
	}
      printf("\n");
    }
  i=0;j=0;
  count=0;
  while(count<s+d-2)
    {
      if(input[i][d]<input[s][j])
	{
	  input[i][j]=input[i][d];
	  input[s][j]=input[s][j]-input[i][d];
	  input[i][d]=0;
	  i=i+1;
	  count++;
	}
      else if(input[s][j]<input[i][d])
	{
	  input[i][j]=input[s][j];
	  input[i][d]=input[i][d]-input[s][j];
	  input[s][j]=0;
	  j=j+1;
	  count++;
	}
      else
	{
	  input[i][j]=input[s][j];
	  input[i][d]=0;
	  j=j+1;
	  count++;
	}
    }
  input[i][j]=input[i][d];
  printf("\n the initial solution of the given transportation problem is:");\
  printf("\n");
  for(i=0;i<s;i++)
    {
      for(j=0;j<d;j++)
	{
	  printf("%d ",input[i][j]);
	}
      printf("\n");
    }
  sum=0;
  for(i=0;i<s;i++)
    for(j=0;j<d;j++)
      sum=sum+cost[i][j]*input[i][j];
  printf("\n the shipping cost for this initial solution is:%d",sum);
}
