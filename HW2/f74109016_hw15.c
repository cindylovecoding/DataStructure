//finished in 2021/10/30
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node NODE;
struct node{
	int data;
	int inorder_index;
	NODE* right_link;
	NODE* left_link;
	NODE* parent_link;
};
int find_inorder_index(int *inorder,int goal,int element){
	int i;
	for(i=0;i<element;i++){
		if(goal == *(inorder+i)){
			return i;
		}
	}
}
void find_parent(NODE *root,int goal_data,int *inorder,int element,NODE * current){
	while(1){
		if(find_inorder_index(inorder,root->data,element)<find_inorder_index(inorder,current->data,element)){
			if(root->right_link!=NULL){
				root = root->right_link;
			}
			else{
				current->parent_link = root;
				root->right_link = current;
				break;
			}
		}
		else{
			if(root->left_link!=NULL){
				root = root->left_link; 
			}
			else{
				current->parent_link = root;
				root->left_link = current;
				break;
			}
		}
	}
}
NODE * create_tree(int *preorder,int *inorder,int element){
	NODE* root = (NODE *)malloc(sizeof(NODE));
	
	root->data = *preorder;
	root->right_link = NULL;
	root->left_link = NULL;
	root->parent_link = NULL;
	root->inorder_index = find_inorder_index(inorder,root->data,element);
	
	int current_index = 0;
	
	while(current_index++<element-1){
		NODE* current = (NODE *)malloc(sizeof(NODE));
		current->data = *(preorder+current_index);
		current->inorder_index = find_inorder_index(inorder,current->data,element);
		current->right_link = NULL;
		current->left_link = NULL;
		find_parent(root,current->data,inorder,element,current);
	}
	return root;
}
void traversal_postorder(NODE * root){
	if(root->left_link!=NULL){
		traversal_postorder(root->left_link);
	}
	if(root->right_link!=NULL){
		traversal_postorder(root->right_link);
	}
	if(root!=NULL){
		printf("%d ",root->data);
	}
}
void traversal_preorder(NODE * root){
	if(root!=NULL){
		printf("%d ",root->data);
	}
	if(root->left_link!=NULL){
		traversal_preorder(root->left_link);
	}
	if(root->right_link!=NULL){
		traversal_preorder(root->right_link);
	}
}
NODE* create_tree2(int *postorder,int *inorder,int element){
	NODE* root = (NODE *)malloc(sizeof(NODE));
	
	root->data = *(postorder+element-1);
	root->right_link = NULL;
	root->left_link = NULL;
	root->parent_link = NULL;
	root->inorder_index = find_inorder_index(inorder,root->data,element);
	
	int current_index = element-1;
	
	while(--current_index>=0){
		NODE* current = (NODE *)malloc(sizeof(NODE));
		current->data = *(postorder+current_index);
		current->inorder_index = find_inorder_index(inorder,current->data,element);
		current->right_link = NULL;
		current->left_link = NULL;
		find_parent(root,current->data,inorder,element,current);
	}
	return root;
}
int main(){
	int m,i,element,j;
	char string[20];
	scanf("%d",&m);
	NODE* root = (NODE *)malloc(sizeof(NODE));
	for(i=0;i<m;i++){
		scanf("%s",string);
		if(strcmp("preorder-inorder",string)==0){
			scanf("%d",&element);
			int preorder [element];
			for(j=0;j<element;j++){
				scanf("%d",&preorder[j]);
			}
			int inorder [element];
			for(j=0;j<element;j++){
				scanf("%d",&inorder[j]);
			}
			root = create_tree(preorder,inorder,element);
			traversal_postorder(root);
		}
		if(strcmp("postorder-inorder",string)==0){
			scanf("%d",&element);
			int postorder [element];
			for(j=0;j<element;j++){
				scanf("%d",&postorder[j]);
			}
			int inorder [element];
			for(j=0;j<element;j++){
				scanf("%d",&inorder[j]);
			}
			root = create_tree2(postorder,inorder,element);
			traversal_preorder(root);
		}
		printf("\n");
	}
	return 0;
} 
