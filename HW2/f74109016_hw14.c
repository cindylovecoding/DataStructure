//f74109016_葉惟欣 finished in 2021/11/1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//height union
typedef struct node NODE;
struct node{
	int parent;
	int height;
};
void create1(NODE *array1,int element){
	int i;
	for(i=0;i<element;i++){
		(array1+i)->parent=-1;
		(array1+i)->height=1;
	}
}
void create(int *array,int element){
	int i;
	for(i=0;i<element;i++){
		*(array+i)=-1;
	}
}
int find_root1(NODE *array1,int tree1){
	while((array1+tree1)->parent>-1){
		tree1 = (array1+tree1)->parent;
	}
	return tree1;
}
int find_root(int *array,int tree1){
	while(*(array+tree1)>-1){
		tree1 = *(array+tree1);
	}
	return tree1;
}
int find_height(NODE *array1,int root,int element){
	int i,height=1,max =0;
	for(i=0;i<element;i++){
		if((array1+i)->parent==root){
			int height_temp = (array1+i)->height;
			if(height_temp>max){
				max=height_temp;
			}
		}
	}
	return max+1;
}

void same1(NODE *array1,int tree1,int tree2){
	int root_tree1 = find_root1(array1,tree1);
	int root_tree2 = find_root1(array1,tree2);
	if(root_tree1==root_tree2){
		printf("true\n");
	}
	else{
		printf("false\n");
	}
}
void height_union(NODE *array1,int tree1,int tree2,int element){
	int root_tree1 = find_root1(array1,tree1);
	int root_tree2 = find_root1(array1,tree2);
	if(root_tree1!=root_tree2){
		if((array1+root_tree1)->height < (array1+root_tree2)->height){
			(array1+root_tree1)->parent = root_tree2;
		}
		else if((array1+root_tree1)->height > (array1+root_tree2)->height){
			(array1+root_tree2)->parent = root_tree1;
		}
		else{
			(array1+root_tree2)->parent = root_tree1;
			(array1+root_tree1)->height+=1;
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
//weight union
void weight_union(int *array,int tree1,int tree2){
	/*union the sets with roots i and j, i!=j,using the weighting rule. paretn[i] = -count[i] and paretn[j] = -count[j]*/
	int root_tree1 = find_root(array,tree1);
	int root_tree2 = find_root(array,tree2);
	if(root_tree1!=root_tree2){
		int temp = *(array+root_tree1) + *(array+root_tree2);
	
		if(*(array+root_tree1) > *(array+root_tree2)){
			*(array+root_tree1) = root_tree2;
			*(array+root_tree2) =temp;
		}
		else{
			*(array+root_tree2) = root_tree1;
			*(array+root_tree1) = temp;
		}
	}
}
int collapsingFind1(NODE * array1,int tree1,int element){
	int root = find_root1(array1,tree1);
	while((array1+tree1)->parent>-1){
		int temp = (array1+tree1)->parent;
		(array1+tree1)->parent = root;
		(array1+tree1)->height = 1;
		tree1 = temp;		
	}
	(array1+tree1)->height = find_height(array1,tree1,element);
	(array1+root)->height = find_height(array1,root,element);
	return root;
}
int collapsingFind(int * array,int i){
	//find the root of the tree containing element i. Use the collapsing rule to collasing all nodes from i to root
	int root,trail,lead;
	for(root = i;*(array+root)>=0;root = *(array+root)){
		
	}
	for(trail = i; trail != root;trail = lead){
		lead = *(array+trail);
		*(array+trail) = root;
	}
	return root;
}
int main(){
	int round,i,j,k,element,operation_time;
	char string[5];
	int *ptr ;
	scanf("%d",&round);
	clock_t start1 = clock();
	for(i=0;i<round;i++){
		scanf("%d %d",&element,&operation_time);
		int array[element];
		NODE array1[element];
		int mode=0;
		for(j=0;j<operation_time;j++){
			scanf("%s",string);
			if(strcmp(string,"height_union")==0){
				int tree1,tree2;
				mode = 0;
				if(j==0){
					create1(array1,element);
				}
				scanf("%d %d",&tree1,&tree2);
				height_union(array1,tree1,tree2,element);
			}
			else if(strcmp(string,"weight_union")==0){
				int tree1,tree2;
				mode = 1;
				if(j==0){
					create(array,element);
				}
				scanf("%d %d",&tree1,&tree2);
				weight_union(array,tree1,tree2);
			}
			else if(strcmp(string,"find")==0){
				int goal;
				scanf("%d",&goal);
				if(mode==0){
					printf("%d\n",collapsingFind1(array1,goal,element));
				}
				else{
					printf("%d\n",collapsingFind(array,goal));
				}
			}
			else if(strcmp(string,"same")==0){ //在同一個集合 
				int tree1,tree2;
				scanf("%d %d",&tree1,&tree2);
				if(mode==0){
					same1(array1,tree1,tree2);
				}
				else{
					same(array,tree1,tree2);
				}
			}
		}
	}
	clock_t end = clock();
	double elapsedTime1 = (double) (clock() -start1)/CLOCKS_PER_SEC;
	printf("weight_union elapsedTime : %.20f\n",elapsedTime1);
	return 0;
} 
