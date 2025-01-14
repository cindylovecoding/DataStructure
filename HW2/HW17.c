//F74109016 葉惟欣 finished in 2021/11/01 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FALSE 0
#define TRUE 1
#define MAX_ELEMENTS 200
#define HEAP_FULL(n)(n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef enum { false, true }bool;
struct node
{
   int data;				  	  
   struct node *link;
};
typedef struct node NODE;
void create(int *array,int element){
	int i;
	for(i=0;i<element;i++){
		*(array+i)=-1;
	}
}
int find_root(int *array,int tree1){
	while(array[tree1]>-1){
		tree1 = array[tree1];
	}
	return tree1;
}
void union_oper(int *array,int tree1,int tree2,int element){
	int root_tree1 = find_root(array,tree1);
	int root_tree2 = find_root(array,tree2);
	if(root_tree1!=root_tree2){
		if(*(array+root_tree1)<*(array+root_tree2)){
			*(array+root_tree2) = root_tree1;
		}
		else if(*(array+root_tree1)>*(array+root_tree2)){
			*(array+root_tree1) = root_tree2;
		} 
		else{
			*(array+root_tree2) = root_tree1;
			*(array+root_tree1) -=1;
		}
	}		
}
void bfs(int *array,int * ptr,int* number,int vertice_num,NODE* root){
	NODE* current = root;
	int i;
	bool find= false;
	while(root!=NULL){
		for(i=0;i<vertice_num;i++){
			if(i!=root->data && *(ptr+vertice_num*root->data+i)==1 &&!(find_root(array,root->data)==find_root(array,i))){ //i不能等於t，且i與t不在同個集合 
					NODE * new_node = (NODE *)malloc(sizeof(NODE));
					new_node->data = i;
					new_node->link = NULL;
					current->link = new_node;
					current = current->link;
					printf("%d ",current->data);
					union_oper(array,root->data,i,vertice_num);
			}
		}
		root = root->link;
	}
}
int main(){
	int i,j,k,n,m,t;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d %d",&m,&t); // m represents the number of vertices in the given graph;
		                      // t is a vertex index, it represents the entrypoint of the dfs traversal.
		int vertice_num = m;
		int table[m][m];
		int *ptr = table;
		for(j=0;j<m;j++){
			for(k=0;k<m;k++){
				scanf("%d",&table[j][k]); 
			}
		}
		int array[m];
		int * number = &m;
		create(array,m); //將每個節點都設為一個集合 
		NODE * root = (NODE *)malloc(sizeof(NODE));
		root->link = NULL;
		root->data = t;
		printf("%d ",root->data);
		bfs(array,ptr,number,vertice_num,root);
		printf("\n");
	}
} 
