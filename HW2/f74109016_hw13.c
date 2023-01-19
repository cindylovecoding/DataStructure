//F74109016 葉惟欣 Homework#13 finished in 2021/10/30 
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
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
		if(*(array+root_tree1) > *(array+root_tree2)){
			*(array+root_tree1) = root_tree2;
		}
		else if(*(array+root_tree1) < *(array+root_tree2)){
			*(array+root_tree2) = root_tree1;
		}
		else{
			*(array+root_tree2) = root_tree1;
			*(array+root_tree1)-=1;
		}
	}		
}
void same(int *array,int tree1,int tree2){
	int root_tree1 = find_root(array,tree1);
	int root_tree2 = find_root(array,tree2);
	if(root_tree1==root_tree2){
		printf("true\n");
	}
	else{
		printf("false\n");
	}
}
int main(){
	int round,i,j,k,element,operation_time;
	char string[5];
	int *ptr ;
	scanf("%d",&round);
	for(i=0;i<round;i++){
		scanf("%d %d",&element,&operation_time);
		int array[element];
		create(array,element);
		
		for(j=0;j<operation_time;j++){
			scanf("%s",string);
			if(strcmp(string,"union")==0){
				int tree1,tree2;
				scanf("%d %d",&tree1,&tree2);
				union_oper(array,tree1,tree2,element);
			}
			else if(strcmp(string,"find")==0){
				int goal;
				scanf("%d",&goal);
				printf("%d\n",find_root(array,goal));
			}
			else if(strcmp(string,"same")==0){ //在同一個集合 
				int tree1,tree2;
				scanf("%d %d",&tree1,&tree2);
				same(array,tree1,tree2);
			}
		}
	}
	return 0;
} 

