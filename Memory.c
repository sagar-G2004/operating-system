//mem alloc
#include<stdio.h>
#include<stdlib.h>
typedef struct free_block
{
   int start_addr;
   int size;
   struct free_block *next;
}free_block;
typedef struct allocated_block
{
	int start_addr;
	int size;
	struct allocated_block *next;
}allocated_block;
free_block *free_head=NULL;
allocated_block *allocated_head=NULL;
void insert_free_block(int start_addr,int size)
{
	free_block *new_block=(free_block*)malloc(sizeof(free_block));
	new_block->start_addr=start_addr;
	new_block->size=size;
	new_block->next=NULL;
	if(free_head==NULL)
	{
		free_head=new_block;
	}
	else
	{
		free_block *curr=free_head;
		while(curr->next!=NULL)
		{
			curr=curr->next;
		}
		curr->next=new_block;
	}
}
void insert_allocated_block(int start_addr,int size)
{
	allocated_block *new_block=(allocated_block*)malloc(sizeof(allocated_block));
	new_block->start_addr=start_addr;
	new_block->size=size;
	new_block->next=allocated_head;
	allocated_head=new_block;
}
void best_fit(int size)
{
	free_block *curr=free_head;
	free_block *best=NULL;
	int best_size=-1;
	while(curr)
	{
		if(curr->size>=size&&(best==NULL||curr->size<best_size))
		{
			best=curr;
			best_size=curr->size;
		}
		curr=curr->next;
	}
	if(best)
	{
		insert_allocated_block(best->start_addr,size);
		if(best->size==size)
		{
			free_head=best->next;
			free(best);
		}
		else
		{
			best->size-=size;
			best->start_addr+=size;
		}
	}
}
void first_fit(int size)
{
	free_block *curr=free_head;
	free_block *first=NULL;
	while(curr)
	{
		if(curr->size>=size)
		{
			first=curr;
			break;
		}
		curr=curr->next;
	}
	if(first)
	{
		insert_allocated_block(first->start_addr,size);
		if(first->size==size)
		{
			free_head=first->next;
			free(first);
		}
		else
		{
			first->size-=size;
			first->start_addr+=size;
		}
	}
}
void worst_fit(int size)
{
	free_block *curr=free_head;
	free_block *worst=NULL;
	int worst_size=-1;
	while(curr)
	{
		if(curr->size>=size&&(worst==NULL||curr->size>worst_size))
		{
			worst=curr;
			worst_size=curr->size;
		}
		curr=curr->next;
	}
	if(worst)
	{
		insert_allocated_block(worst->start_addr,size);
		if(worst->size==size)
		{
			free_head=worst->next;
			free(worst);
		}
		else
		{
			worst->size-=size;
			worst->start_addr+=size;
		}
	}
}
void print_free_list()
{
	free_block *curr=free_head;
	printf("free list:\n");
	while(curr)
	{
		printf("[%d-%d]\n",curr->start_addr,curr->start_addr+curr->size);
		curr=curr->next;
	}
	//printf("NULL\n");
}
void print_allocated_list()
{
	allocated_block *curr=allocated_head;
	printf("allocated list:\n");
	while(curr)
	{
		printf("[%d-%d]\n",curr->start_addr,curr->start_addr+curr->size);
		curr=curr->next;
	}
	//printf("NULL\n");
}

int main()
{
	int ch,n,ba,s,i;
	printf("enter no:of block:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("enter the base address and size\n");
		scanf("%d%d",&ba,&s);
		insert_free_block(ba,s);
	}
	printf("Initial free list:");
	print_free_list();
	while(1)
	{
		printf("enter choice 1:bestfit,2:first fit,3:worst fit");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("enter the size of the process to be allocated:\n");
			      scanf("%d",&s);
			      best_fit(s);
			      printf("after best fit allocation:");
			      print_free_list();
			      print_allocated_list();
			      break;
	        case 2:printf("enter the size of the process to be allocated:\n");
			      scanf("%d",&s);
			      first_fit(s);
			      printf("after first fit allocation:");
			      print_free_list();
			      print_allocated_list();
			      break;
		    case 3:printf("enter the size of the process to be allocated:\n");
			      scanf("%d",&s);
			      worst_fit(s);
			      printf("after worst fit allocation:");
			      print_free_list();
			      print_allocated_list();
			      break;
			case 4:return 0;
		}
	}
	return 0;
}
