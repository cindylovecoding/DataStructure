//F74109016_葉惟欣 Finished in 2021/10/18 Homework#10
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
int i=0;
typedef struct node NODE;
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
				if(new_NODE->data != -1){
					current = current->left_link;
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
void preorder(NODE * current){
	if(current==NULL){ 
		return;
	}
	if(current->data != -1){
		printf("%d ",current->data);
	}
	preorder(current->left_link);
	preorder(current->right_link);
}
void postorder(NODE * current){
	if(current==NULL){ 
		return;
	}
	postorder(current->left_link);
	postorder(current->right_link);
	if(current->data != -1){
		printf("%d ",current->data);
	}
}
void inorder(NODE * current){
	if(current==NULL){ 
		return;
	}
	inorder(current->left_link);
	if(current->data != -1){
		printf("%d ",current->data);
	}
	inorder(current->right_link);
}
void swap(NODE * current){
	if(current->data!=-1){
		NODE *temp =current->left_link;
		current->left_link = current->right_link;
		current->right_link = temp;
		swap(current->left_link);
		swap(current->right_link);
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
	swap(first);
	preorder(first);
	printf("\n");
	inorder(first);
} 
