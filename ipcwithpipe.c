#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
/*
int main()
{
	int fd[2],i,j,n;
	pid_t pid;

	if(pipe(fd)==-1)
	{
		perror("pipe error");
		return 0;
	}

	pid=fork();

	if(pid<0)
	{
		printf("Child creation failed");
		return 0;
	}

	else if(pid>0)
	{
		close(fd[0]);

		printf("P: Enter the total numbers:\n");
		scanf("%d",&n);

		int numbers[n];

		printf("P: Enter the numbers:\n");
		for(i=0;i<n;i++)
		{
			scanf("%d",&numbers[i]);
		}
		
		write(fd[1],&n,sizeof(int));
		write(fd[1],numbers,n*sizeof(int));
		close(fd[1]);
		
		//wait(NULL);
	}

	else if(pid==0)
	{
		close(fd[1]);

		read(fd[0],&n,sizeof(int));

		int r_numbers[n];

		read(fd[0],r_numbers,n*sizeof(int));
		close(fd[0]);

		printf("c: Numbers Read from the pipe:\n");
		for(i=0;i<n;i++)
		{
			printf("%d\t",r_numbers[i]);
		}

		for(i=0;i<n-1;i++)
		{
			for(j=0;j<n-i-1;j++)
			{
				if(r_numbers[j]>r_numbers[j+1])
				{
					int temp=r_numbers[j];
					r_numbers[j]=r_numbers[j+1];
					r_numbers[j+1]=temp;
				}
			}
		}

		printf("\nC: Sorted numbers are:\n");
		for(i=0;i<n;i++)
			printf("%d\t",r_numbers[i]);

		exit(EXIT_FAILURE);
	}
	return 0;
}
*/

int main()
{
	int fd[2],fd2[2];
	int pid;
	
	//key_t key=112;
	
	if (pipe(fd) == -1  || pipe(fd2)==-1)
	{ 
		perror("erroring pipe creation");
		return 1;
	}
	
	
	pid=fork();
	if(pid>0)
	{
		int n;
		close(fd[0]);
		printf("Enter the n:\n");
		scanf("%d",&n);
		write(fd[1],&n,sizeof(int));
		int numbers[n];
		printf("Enter the %d numbers:\n",n);
		for(int i=0;i<n;i++)
			scanf("%d",&numbers[i]);
		
		write(fd[1],numbers,n*sizeof(int));
		close(fd[1]);
		close(fd2[1]);
		int s,flag=0;
		read(fd2[0],&s,sizeof(int));
		for(int i=0;i<n;i++)
		{
			if(numbers[i]==s)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
			printf("Found");
		else
			printf("Not Found");
		close(fd2[0]);
		exit (0);
	}
	else if(pid==0)
	{
		close(fd[1]);
		int n;
		read(fd[0],&n,sizeof(int));
		int numbers[n];
		read(fd[0],numbers,n*sizeof(int));
		for(int i=0;i<n;i++)
			printf("%d ",numbers[i]);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(numbers[j]>numbers[j+1])
				{
					int temp=numbers[j];
					numbers[j]=numbers[j+1];
					numbers[j+1]=temp;
				}
			}
		}
		printf("After sorting:\n");
		for(int i=0;i<n;i++)
			printf("%d ",numbers[i]);
		printf("\n");
		close(fd2[0]);
		int s;
		printf("Enter number to search\n");
		scanf("%d",&s);
		write(fd2[1],&s,sizeof(int));
		close(fd2[1]);
		exit (0);
	}
	return 0;
}


