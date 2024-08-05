//Bankers algorithm
#include<stdio.h>
int main()
{
	int n,m,i,j,k;
	int alloc[20][20],max[20][20],avail[20];
	printf("enter n and m\n");
	scanf("%d%d",&n,&m);
	printf("enter the matrix of allocation\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}
	printf("enter the matrix of maximum\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	printf("enter the array of available resources\n");
	for(i=0;i<m;i++)
		scanf("%d",&avail[i]);
	int f[n],ans[n],ind=0;
	for(i=0;i<n;i++)
	{
		ans[i]=0;
	}
	for(k=0;k<n;k++)
	{
		f[k]=0;
	}
	int need[n][m];
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}
	printf("Need:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d ",need[i][j]);
		}
		printf("\n");
	}
	//int y=0;
	for(k=0;k<5;k++)
	{
		for(i=0;i<n;i++)
		{
			if(f[i]==0)
			{
				int flag=0;
				for(j=0;j<m;j++)
				{
					if(need[i][j]>avail[j])
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					ans[ind++]=i;
					for(j=0;j<m;j++)
					{
						avail[j]+=alloc[i][j];
					}
					f[i]=1;
				}
			}
		}
	}
	printf("following is the safe sequence\n");
	for(i=0;i<n-1;i++)
	printf("p%d->",ans[i]);
	printf("p%d",ans[n-1]);
	return 0;
}

