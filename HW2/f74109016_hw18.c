//finished in 2021/11/05
#include<stdio.h>
#include<stdlib.h>

typedef struct edge_road ROAD;
struct edge_road{                //存幾條路 
	int cost;      
	int vertice1;
	int vertice2;   
};
typedef int bool;  
enum { false, true };

bool HEAP_EMPTY(n){
	if(!n){
		return true;
	}
	else{
		return false;
	}
}
ROAD* pop_road(int *top,ROAD *heap_pointer){
	int parent,child;
	ROAD* item = (ROAD*) malloc(sizeof(ROAD));
	ROAD* temp = (ROAD*) malloc(sizeof(ROAD));
	
	if(HEAP_EMPTY(*top)==true){
		printf("The heap is empty\n");
		return NULL;
	}
	else{
		item->cost = (heap_pointer+1)->cost;
		item->vertice1 = (heap_pointer+1)->vertice1;
		item->vertice2 = (heap_pointer+1)->vertice2;
		
		int top_temp = (*top);
		temp->cost = (heap_pointer+top_temp)->cost;
		temp->vertice1 = (heap_pointer+top_temp)->vertice1;
		temp->vertice2 = (heap_pointer+top_temp)->vertice2;
		(*top)--;
		parent = 1;
		child =2;
		while(child<=*top){
			//find the smallest key from the heap
			if((child<*top)&&((heap_pointer+child)->cost>(heap_pointer+child+1)->cost)){
				child++;
			}
			if(temp->cost <= (heap_pointer+child)->cost){
				break;
			}
			(heap_pointer+parent)->cost = (heap_pointer+child)->cost;
			(heap_pointer+parent)->vertice1 = (heap_pointer+child)->vertice1;
			(heap_pointer+parent)->vertice2 = (heap_pointer+child)->vertice2;
	
			parent= child;
			child*=2;
		}
		(heap_pointer+parent)->cost = temp->cost;
		(heap_pointer+parent)->vertice1 = temp->vertice1;
		(heap_pointer+parent)->vertice2 = temp->vertice2;
	
		return item;
	}
}
void push_road(ROAD* NEW_ROAD,int* top,ROAD *heap_pointer){ //insert item into a maz heap of current size *n
	int i;
	i = ++(*top);

	if(i==1){
		(heap_pointer+1)->cost = NEW_ROAD->cost;
		(heap_pointer+1)->vertice1 = NEW_ROAD->vertice1;
		(heap_pointer+1)->vertice2 = NEW_ROAD->vertice2;		
	}
	else{
		while((i!=1)&&(NEW_ROAD->cost < (heap_pointer+(i/2))->cost)){
			(heap_pointer+i)->cost = (heap_pointer+(i/2))->cost;
			(heap_pointer+i)->vertice1 = (heap_pointer+(i/2))->vertice1;
			(heap_pointer+i)->vertice2 = (heap_pointer+(i/2))->vertice2;
			i/=2;
		}
		(heap_pointer+i)->cost =NEW_ROAD->cost;
		(heap_pointer+i)->vertice1 = NEW_ROAD->vertice1;
		(heap_pointer+i)->vertice2 = NEW_ROAD->vertice2;
	}
}


/***********************************/ 
void create(int *array,int element){
	int i;
	for(i=0;i<element;i++){
		*(array+i)=-1;
	}
}
int find_height(int *array,int root,int element){
	int i,height=1,max =0;
	for(i=0;i<element;i++){
		if(*(array+i)==root){
			int temp = find_height(array,i,element);
			if(temp>max){
				max=temp;
			}
		}
	}
	return height+max;
}
int find_root(int *array,int tree1){
	while(array[tree1]!=-1){
		tree1 = array[tree1];
	}
	return tree1;
}
void union_oper(int *array,int tree1,int tree2,int element){
	int root_tree1 = find_root(array,tree1);
	int root_tree2 = find_root(array,tree2);
	if(root_tree1!=root_tree2){
		if(find_height(array,root_tree1,element)>=find_height(array,root_tree2,element)){
			*(array+find_root(array,tree2)) = root_tree1;
		}	
		else{
			*(array+find_root(array,tree1)) = root_tree2;
		}
	}	
}
bool same(int *array,int tree1,int tree2){
	int root_tree1 = find_root(array,tree1);
	int root_tree2 = find_root(array,tree2);
	if(root_tree1==root_tree2){
		return true;           //在集合裡面 
	}
	else{
		return false;           //不在集合裡面
	}
}

//Kruskal's algorithm
 
int Kruskal(int *top,int vertice_num,ROAD *heap_pointer){
	int array[vertice_num];
	create(array,vertice_num);
	
	ROAD* root = pop_road(top,heap_pointer);

	
	
	union_oper(array,root->vertice1,root->vertice2,vertice_num);
	int edge_num=1;
	bool find = true;
	int total =root->cost;

	
	while(edge_num!=vertice_num-1&&find == true){
		find = false;
		ROAD* NEW_ROAD = pop_road(top,heap_pointer);	 
		if(NEW_ROAD!=NULL){	
			bool  exist = same(array,NEW_ROAD->vertice1,NEW_ROAD->vertice2); //在集合裡面true
			find = true;																//不在集合裡面false
			if(exist==false){
				edge_num++;
				union_oper(array,NEW_ROAD->vertice1,NEW_ROAD->vertice2,vertice_num);
				//printf("%d %d %d\n",NEW_ROAD->vertice1,NEW_ROAD->vertice2,NEW_ROAD->cost);
				total += NEW_ROAD->cost;
			}
		}
	}
	if(root==NULL||edge_num!=vertice_num-1){
		printf("No spanning tree\n"); 
	}
	return total;
}
int main(){
	int vertice_num,edge_num,i;
	scanf("%d %d",&vertice_num,&edge_num); 

	int current_num=0;
	
	int *top = &current_num;
	int vertice1,vertice2,cost;
	
	ROAD heap [edge_num+1];
	ROAD *heap_pointer;
	heap_pointer = heap;
	for(i=0;i<edge_num;i++){ 
		scanf("%d %d %d",&vertice1,&vertice2,&cost);
		ROAD* NEW_ROAD = (ROAD*) malloc(sizeof(ROAD));
		NEW_ROAD->cost = cost;
		NEW_ROAD->vertice1 = vertice1;
		NEW_ROAD->vertice2 = vertice2;
		push_road(NEW_ROAD,top,heap_pointer);
	}

	
	printf("%d",Kruskal(top,vertice_num,heap_pointer));
	return 0;
}
