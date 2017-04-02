//------------------------------------//
//		Author @ Isira Yapa			 //
//-----------------------------------//
//Note = You Consider free = 1 and used = 0

#include <stdio.h>
#include <stdlib.h>

char memory[25000];

typedef struct node Block_head; //setting an Alias called Block_head
struct node{
	int size;
	int status; // Free = 1 Used = 0
	Block_head *next;
};

Block_head *mymem = (void*)memory;

#define head_size sizeof(Block_head) //Defined the block size

void header(){
	if(mymem->size==0){
		mymem->status = 1;
		mymem->size = sizeof(memory)-head_size;
		mymem->next = NULL;
		//printf("The header : %d \n",mymem->size);
	}
}
//Finding the position using the firstfit method
struct node * findpos(int size){
	Block_head *current = mymem;
	Block_head *firstfit = NULL;
	while(current != NULL){
		if((current->size >= size)&&(current->status = 1)){

			firstfit = current;
		}
	current = current->next;
	}
	if(firstfit==NULL){
		firstfit = mymem;
	}
	printf("\nThe head size = %d\n",head_size );
	return firstfit;
}
void * mymalloc(int n){
	header();
	void * temp;
	Block_head *free_space = findpos(n);
	printf("Show the pointer of free space in the begining= %p\n",(void*)free_space);

	if((free_space->size < n+head_size) || (free_space->status == 0)){
		printf("\nSorry! There is not enough memory to run this task\n" );

	}else{

		Block_head *newnode = (void*)free_space + n+ head_size;//Header for the current node
		newnode->status = 1;
		newnode->next = free_space->next;
		newnode->size = free_space->size - (n+head_size);

		free_space->next = newnode;
		free_space->size = n;
		printf("\nNew block %p size %d ",newnode,25000-newnode->size);
	}	

	

	free_space->status = 0;
	free_space = (void*)free_space + head_size;

	temp = (void*)free_space;
	printf("Pointer after calling malloc = %p\n",temp);
	return temp;
}
void myfree(void * del){
	Block_head *temp = (Block_head *)((void *)del-head_size);
	temp->status = 1;
 
	temp = mymem;

	while(temp->next!=NULL){
		if((temp->status==1) && (temp->next->status==1)){
			temp->next = temp->next->next;
			temp->size += temp->next->size +head_size;

		}
		temp = temp->next;
	}

}

void main(int argc, char const *argv[])
{
	printf("In the begining :%p\n",(void*)mymem);
	void *temp1 = (void*)mymalloc(12);
	void *temp2 = (void*)mymalloc(2);
	void *temp5 = (void*)mymalloc(4);
	void *temp3 = (void*)mymalloc(24990);
	void *temp6 = (void*)mymalloc(4);
	myfree(temp2);

}
