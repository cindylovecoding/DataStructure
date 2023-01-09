//F74109016 ¸­±©ªY finished in 2021/10/20 Homework#6 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
   	char data;				  
  	struct node *right_link;		  
   	struct node *left_link;
   	struct node *back;
};
typedef struct node NODE;
NODE* read_prefix(char *arr){
	NODE *first,*new_NODE;
	NODE *current =(NODE *)malloc(sizeof(NODE));
	int i=0;
	while(*(arr+i)!='\0'){
		new_NODE= (NODE *)malloc(sizeof(NODE));
		new_NODE->left_link = NULL;
		new_NODE->right_link = NULL;
		new_NODE->back= NULL; 
		if(i==0){
			new_NODE->data = arr[i];
			current = new_NODE;
			first = current;
			i++;
		}
		else{
			if(current->left_link== NULL){
				new_NODE->data = arr[i];
				new_NODE->back = current;
				current->left_link = new_NODE;
				current = new_NODE;
				i++;
			}
			else if(current->right_link== NULL){
				new_NODE->data = arr[i];
				new_NODE->back = current;
				current->right_link = new_NODE;	
				current = new_NODE;
				i++;
			}
			if(!((arr[i-1]=='+')||(arr[i-1]=='-')||(arr[i-1]=='*')||(arr[i-1]=='/')||(arr[i-1]=='^'))){
				current = current->back;
			}
		}
	}
	return first;
}
NODE* read_postfix(char *arr){
	NODE *first,*new_NODE;
	NODE *current =(NODE *)malloc(sizeof(NODE));
	int i=0;
	while(*(arr+i)!='\0'){
		new_NODE= (NODE *)malloc(sizeof(NODE));
		new_NODE->left_link = NULL;
		new_NODE->right_link = NULL;
		new_NODE->back= NULL; 
		if(i==0){
			new_NODE->data = arr[i];
			current = new_NODE;
			first = current;
			i++;
		}
		else{
			if(current->right_link== NULL){
				new_NODE->data = arr[i];
				new_NODE->back = current;
				current->right_link = new_NODE;
				current = new_NODE;
				i++;
			}
			else if(current->left_link== NULL){
				new_NODE->data = arr[i];
				new_NODE->back = current;
				current->left_link = new_NODE;	
				current = new_NODE;
				i++;
			}
			if(!((arr[i-1]=='+')||(arr[i-1]=='-')||(arr[i-1]=='*')||(arr[i-1]=='/')||(arr[i-1]=='^'))){
				current = current->back;
			}
		}
	}
	return first;
}
int reverse(char *str){
	int i, j;
    char temp;

    j=strlen(str) - 1;
    for(i=0; i<j; i++){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        j--;
    }
    return 0;
} 

void postorder(NODE * current){
	if(current==NULL){ 
		return;
	}
	postorder(current->left_link);
	postorder(current->right_link);
	printf("%c",current->data);
}
void preorder(NODE * current){
	if(current==NULL){ 
		return;
	}
	printf("%c",current->data);
	preorder(current->left_link);
	preorder(current->right_link);
}
int main(){
	char input [50]; 
	int i=0;
	do{
		scanf("%s",input);
		NODE * result;
		if((input[0]=='+')||(input[0]=='-')||(input[0]=='*')||(input[0]=='/')||(input[0]=='^')){
			result =read_prefix(input);
			postorder(result);
			printf("\n");
		}
		else{
			reverse(input);
			result =read_postfix(input);
			preorder(result);
			printf("\n");
		}
		i++;
	}while(i<2);
}
