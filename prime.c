/*
找出n以内的质数并且求有几对相加等于n；
比如n=10;有（5,5），（3,7）两对
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int NUM=0;
int *getPrime(int *prime,int n)
{
  int i,j;
  prime=(int*)malloc(sizeof(int));
  for (i=2;i<n;i++)
{
    int flag=1;
    for(j=2;j<i;j++)
    {
        if(i%j==0)
            {
                flag=0;
                break;
            }
    }
    if(flag)
    {
        prime=(int*)realloc(prime,sizeof(int)*(NUM+1));
        prime[NUM++]=i;
    }
}
return prime;
}
int main()
{
    int i,j,tmp,sum=0;
    int *prime=NULL;
    prime=getPrime(prime,100);
    for(i=0;i<NUM;i++)
    {
        tmp=100-prime[i];
        for(j=i;j<NUM;j++)
        {
            if(prime[j]==tmp)
            {
                sum++;
                break;
            }
        }


    }
    printf("%d",sum);
    free(prime);
    return 0;
}
