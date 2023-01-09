//F74109016 葉惟欣 finished in 2021/10/19 Homework#8 
#include<stdio.h>
#include<stdlib.h>
typedef int bool;  
enum { false, true };  
int num=0;
struct node
{
   char data;				  
   struct node *right_link;		  
   struct node *left_link;
   struct node *back;
};
typedef struct node NODE;
void confirm(NODE * current){
	char temp;
	if(current==NULL){
		return;
	}
	if(current->left_link!=NULL){
		confirm(current->left_link);
	}
	if(current->right_link!=NULL){
		if((current->right_link->data )<(current->data)){
			temp = current->data;
			current->data = current->right_link->data;
			current->right_link->data= temp;
		}
		if(current->right_link->right_link!=NULL){
			if((current->right_link->right_link->data)<(current->data)){
				temp = current->data;
				current->data = current->right_link->data;
				current->right_link->data= temp;
			}
			if((current->right_link->right_link->data)<(current->right_link->data)){
				temp = current->right_link->data;
				current->right_link->data = current->right_link->data;
				current->right_link->data= temp;
			}
		}
	}
	return;
}
void display(NODE * current,char * A){
	if(current==NULL){ 
		return;
	}
	*(A+num) = current->data;
	num++;
	display(current->left_link,A);
	display(current->right_link,A);
}
NODE* read(char *arr){
	NODE *first,*new_NODE;
	NODE *current =(NODE *)malloc(sizeof(NODE));
	int i=0;
	while(*(arr+i)!='\0'){
		new_NODE= (NODE *)malloc(sizeof(NODE));
		new_NODE->left_link = NULL;
		new_NODE->right_link = NULL;
		new_NODE->back= NULL; 
		if(i==0){
			new_NODE->data = arr[i+1];
			new_NODE->back = current;
			current->left_link = new_NODE;
			current = new_NODE;
			first = current;
		}
		if(i!=0&&arr[i]=='('){
			new_NODE->data = arr[i+1];
			new_NODE->back = current;
			current->left_link = new_NODE;
			current = new_NODE;
		}
		else if(arr[i]==','){
			new_NODE->data = arr[i+1];
			new_NODE->back = current;
			current->right_link = new_NODE;	
			if(arr[i+2]=='('||arr[i+2]==','){
				current = new_NODE;
			}
		}
		else if(arr[i]==')'){
			current = current->back;
		}
		i++;
	}
	return first;
}
bool isSameTree(NODE* root1,NODE* root2){
	NODE * current1 = root1;
	NODE * current2 = root2;
	if(root1 == NULL && root2 == NULL){
		return true;
	} 
	if((root1 == NULL && root2 != NULL)||(root1 != NULL && root2 == NULL)){
		return false;
	}
	if(current1->data == current2->data){
		return (isSameTree(current1->right_link,current2->right_link)&&isSameTree(current1->left_link,current2->left_link));
	}
	else{
		return false;
	}
} 
NODE * copy(NODE * origin_node){
	NODE * current1 = origin_node;              //原始的 
	NODE * new_node = (NODE *)malloc(sizeof(NODE)); //新的 
	new_node->right_link = NULL;
	new_node->left_link = NULL;
	new_node->back = NULL;
	if(current1!=NULL){
		new_node->data = current1->data;
		if(current1->left_link!= NULL){
			new_node->left_link = copy(current1->left_link);
		}
		if(current1->right_link!= NULL){
			new_node->right_link = copy(current1->right_link);
		} 
	}
	return new_node;
}
int main(){
	int line,i,temp,tree_id[3];
	char string[50],first_id_string,second_id_string; 
	NODE * tree[3];
	char arr[3][50],alphat[3][50];
	int tree_node_num[3]={0,0,0};
	scanf("%d",&line);
	for(i=0;i<line;i++){
		scanf("%s",string);
		if(strcmp(string,"read")==0){
			int tree_num;
			scanf("%d",&tree_num);
			scanf("%s",arr[tree_num]);
			tree[tree_num]=read(arr[tree_num]);
			confirm(tree[tree_num]);
			printf("readed\n");
			int j=0;
			tree_node_num[tree_num] = 0;
			while(arr[tree_num][j]!='\0'){
				if((arr[tree_num][j]!='(')&&(arr[tree_num][j]!=')')&&(arr[tree_num][j]!=',')){
					tree_node_num[tree_num]+=1;
				}
				j++;
			}
		}
		else if(strcmp(string,"isequal")==0){
			int first_tree,second_tree;
			scanf("%d %d",&first_tree,&second_tree);
			if(isSameTree(tree[first_tree],tree[second_tree])){
				printf("true\n");
			}
			else{
				printf("false\n");
			}
		}
		else if(strcmp(string,"write")==0){
			scanf("%d",&temp);
			int j=0;
			char  count[tree_node_num[temp]];
			char  * A = count;
			num = 0;
			display(tree[temp],A);
			num = 0;
			while(arr[temp][j]!='\0'){
				if(arr[temp][j]=='('||arr[temp][j]==')'||arr[temp][j]==','){
					printf("%c",arr[temp][j]);
				}
				else{
					printf("%c",*(A+num));
					num++;
				}
				j++;
			}
			printf("\n");
		}
		else if(strcmp(string,"copy")==0){
			int origin_tree,copy_tree;
			scanf("%d %d",&origin_tree,&copy_tree);
			tree[copy_tree] = copy(tree[origin_tree]);
			int j=0;
			while(arr[origin_tree][j] != '\0'){
				arr[copy_tree][j] = arr[origin_tree][j];
				j++;
			}
			printf("copied\n");
			
		} 
		else if(strcmp(string,"clear")==0){
			scanf("%d",&temp);
			free(tree[temp]);
			printf("cleared\n");
		}
	}
}
