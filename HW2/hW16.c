//F74109016 葉惟欣 finished in 2021/11/1 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FALSE 0
#define TRUE 1
#define MAX_ELEMENTS 200
#define HEAP_FULL(n)(n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef enum { false, true }bool;
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

void dfs(int *array,int * ptr,int t,int* number,int vertice_num){
	printf("%d ",t);
	int i,min;
	bool find;
	do{ 
		find = false;
		for(i=0;i<vertice_num;i++){
			if(i!=t && *(ptr+vertice_num*t+i)==1 &&!(find_root(array,t)==find_root(array,i))){ //i不能等於t，且i與t不在同個集合 
				if(find == false){
					min = i;
				}
				else{
					if(i<min){
						min = i;
					}
				}
				find = true;
			}
		} 
		if(find == true){
			union_oper(array,t,min,vertice_num);
			if((*number)!=0){
				(*number)--; 
				dfs(array,ptr,min,number,vertice_num);
			}
		}
	}while(*number!=0&&find==true);
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
		dfs(array,ptr,t,number,vertice_num);
		printf("\n");
	}
} 
