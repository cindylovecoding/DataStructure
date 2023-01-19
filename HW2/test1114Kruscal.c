#include<stdio.h>
#include<stdlib.h>
int i,j,k,a,b,u,v,n,ne=1;
int min,mincost =0;
static int parent[1000000];
typedef struct node NODE;
struct node{
	int a,b,c;
}; 
static NODE stack[1000000];
int find(int);
int uni(int,int);
void heap_sort(int top){
	
	NODE temp;
	temp.a = stack[top-1].a;
	temp.b = stack[top-1].b;
	temp.c = stack[top-1].c;
	int cur = top-1;
	/**
	int child =top-1;
	int parent=(top-1)/2;
	while(1){
		if(stack[parent].c>temp.c){
			stack[child] = stack[parent];
			child = parent;
			if(child!=1){
				parent = child/2;
			}
			else{
				stack[child] = temp;
				break;
			}
		}
		else{
			stack[child] = temp;
			break;
		}
	} 
	**/
	while(cur!=1 && temp.c<stack[cur/2].c){
		stack[cur] = stack[cur/2];
		cur/=2;
	}
	stack[cur] =temp;
}
NODE heap_pop(top){
	NODE item = stack[1];
	NODE temp = stack[top-1];
	/**
	stack[1]= stack[top-1];
	top--;
	int parent=1;
	int min;
	while(1){
		int r_child = parent*2+1;
		int l_child = parent*2;
		if(r_child<top-1){ //¦³¥k¤p«Ä 
			if(stack[r_child].c<stack[l_child].c){
				if(stack[parent].c>stack[r_child].c){
					NODE temp1 = stack[parent];
					stack[parent] = stack[r_child];
					stack[r_child] = temp1;
				}
				else{
					break;
				}
			}
			else{
				if(stack[parent].c>stack[l_child].c){
					NODE temp1 = stack[parent];
					stack[parent] = stack[l_child];
					stack[l_child] = temp1;
				}
				else{
					break;
				}
			}
		}
		else if((l_child<top-1)){
			if(stack[parent].c>stack[l_child].c){
				NODE temp1 = stack[parent];
				stack[parent] = stack[l_child];
				stack[l_child] = temp1;
			}
			else{
				break;
			}	
		}
		else{
			break;
		}
	}
	**/
	int parent = 1,	child =2;
	while(child <= top-1){
		if(child < top-1 && (stack[child].c>stack[child+1].c)){
			child++;
		}
		if(temp.c<=stack[child].c){
			break;
		}
		stack[parent] = stack[child];
		parent = child;
		child*=2;
	}
	stack[parent] = temp;
	return item;
} 
int find(int point){
	int set = point;
	while(parent[set]!=0){
		set = parent[set];
	}
	return set;
}
int uni(int a,int b){
	if(a!=b){
		parent[b]=a;
		return 1;
	}
	return 0;
}
int main(){
	int vertice_num,edge_num,i;
	scanf("%d %d",&vertice_num,&edge_num); 

	int top = 1;
	NODE temp;
	for(i=0;i<edge_num;i++){ 
		int vertice1,vertice2,cost;
		scanf("%d %d %d",&vertice1,&vertice2,&cost);
		NODE temp;
		temp.a = vertice1;
		temp.b = vertice2;
		temp.c = cost;
		stack[top++] = temp;
		if(i!=0){ 
			heap_sort(top);
		} 
	}
	printf("HI\n");
	int total_cost=0;
	for(i=0;i<vertice_num-1;i++){
		while(1){
			temp = heap_pop(top);
			top--;
			int set1 = find(temp.a);
			int set2 = find(temp.b);
			if(uni(set1,set2)){
				total_cost+=temp.c; 
				break;
			}
		}
	}
	printf("%d",total_cost); 
}
