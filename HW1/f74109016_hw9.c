//F74109016_葉惟欣 Finished in 2021/10/18 Homework#9
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
   int data;				  
   struct node *right_link;		  
   struct node *left_link;
   struct node *back;
};
struct link_list{
	int data;
	struct link_list *back;
	struct link_list *front;
};
typedef struct node NODE;
typedef struct link_list LINK_LIST;
NODE* read(int arr[50],int len){
	int i=0;
	NODE *first,*new_NODE;
	NODE *current =(NODE *)malloc(sizeof(NODE));
	
	while(i<len){
		new_NODE= (NODE *)malloc(sizeof(NODE));
		new_NODE->left_link = NULL;
		new_NODE->right_link = NULL;
		new_NODE->back = NULL; 
		if(i==0){
			new_NODE->data = arr[i];
			current = new_NODE;
			first = current;
			i++;
		}
		else{
			if(current->left_link == NULL){  //左節點還沒滿 
				new_NODE->data = arr[i];
				current->left_link = new_NODE;
				new_NODE->back = current;
				current = new_NODE;
				if(new_NODE->data == -1){
					current = current->back;
				}
				i++;
			}
			else if(current->right_link == NULL){ //右節點還沒滿 
				new_NODE->data = arr[i];
				current->right_link = new_NODE;
				new_NODE->back = current;
				current = new_NODE;
				if(new_NODE->data == -1){
					current = current->back;
				}
				i++;
			}
			else{
				current = current->back;
			}
		}
	}
	return first;
}
void Nonpostorder(NODE * first,int length){
	NODE *S[length];
	LINK_LIST * result=(LINK_LIST *)malloc(sizeof(LINK_LIST));
	result->front=NULL;
	int top = -1;
	NODE *current = first; //current是root 
	S[++top] = first;      //stack 裡面放root 
	while(top!=-1){
		current = S[top--]; //將stack 現在放出來 
		LINK_LIST *new_result =(LINK_LIST *)malloc(sizeof(LINK_LIST)); //產生一個result
		new_result->data = current->data; //將放出來的放到result
		if(result!=NULL){		
		result->back = new_result;
		new_result->front = result; //互指 
		}
		result = new_result;   
		if(current->left_link->data!=-1){
			S[++top] = current->left_link;
		}
		if(current->right_link->data!=-1){
			S[++top] = current->right_link;
		}
	}
	int i;
	do{
		printf("%d ",result->data);
		result = result->front;
	}while(result->front!=NULL);
}
void Nonpreorder(NODE * first,int length){
	NODE *Stack[length];
	NODE *current;
	int top = -1;
	Stack[++top]= first;
	while(top!=-1){
		current = Stack[top--]; 
		if(current->right_link->data!=-1){
			Stack[++top] = current->right_link;
		}
		if(current->left_link->data!=-1){
			Stack[++top] = current->left_link;
		}
		if(current->data!=-1){
			printf("%d ",current->data);
		}
	}
}
int main(){
	NODE *first =(NODE *)malloc(sizeof(NODE));
	NODE *second =(NODE *)malloc(sizeof(NODE));
	char string [50];
	int len,i;
	scanf("%d",&len);
	int string1 [len];
	for(i=0;i<len;i++){
		scanf("%s",string);
		string1[i] = atoi(string);
	}
	first = read(string1,len);
	Nonpreorder(first,len);
	printf("\n");
	Nonpostorder(first,len);
	
} 
