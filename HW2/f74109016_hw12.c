//finsished
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n)(n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef enum { false, true }bool;  
typedef struct{
	int weight;
	int id;
}element;
typedef element NODE;
NODE heap[MAX_ELEMENTS];
void push(NODE *item,int *n){ //insert item into a maz heap of current size *n
	int i;
	if(HEAP_FULL(*n)){
		printf("The heap is full. \n");
	}
	else{
		i = ++(*n);
		while((i!=1)&&(item->weight < heap[i/2].weight)){
			heap[i].weight = heap[i/2].weight;
			heap[i].id = heap[i/2].id;
			i/=2;
		}
		heap[i].weight = item->weight;
		heap[i].id = item->id;
	}
}
NODE pop(int *n){
	int parent,child;
	NODE item,temp;
	
	if(HEAP_EMPTY(*n)){
		printf("The heap is empty\n");
	}
	else{
		item = heap[1];
		temp = heap[(*n)--];
		parent = 1;
		child =2;
		while(child<=*n){
			//find the smallest key from the heap
			if((child<*n)&&(heap[child].weight>heap[child+1].weight)){
				child++;
			}
			if(temp.weight <= heap[child].weight){
				break;
			}
			heap[parent] = heap[child];
			parent= child;
			
			child*=2;
		}
		heap[parent] = temp;
		return item;
	}
}
void change(int num,int change,int *n){ 
	int i;
	for(i=1;i<=*n;i++){
		if(heap[i].id == num){
			heap[i].weight = change;
			break;
		}
	}
	int change_num = i;
	NODE * temp = (NODE *) malloc(sizeof(NODE));
	temp->weight = heap[i].weight;
	temp->id = heap[i].id;
	if(temp->weight<heap[i/2].weight&&i!=1){ //比父節點還小 
		while((temp->weight < heap[i/2].weight)&&i!=1){ //比父節點還小 
			heap[i].weight = heap[i/2].weight;
			heap[i].id = heap[i/2].id;
			i=i/2;
		}
		heap[i].weight = temp->weight;
		heap[i].id = temp->id;
	}
	else{
		i = change_num ;
		while(((temp->weight>heap[i*2+1].weight)&&i*2+1<=*(n))||((temp->weight>heap[i*2].weight)&&i*2<=*(n))){
			if((temp->weight>heap[i*2+1].weight)&&i*2+1<=*(n)){
				if((heap[i/2+1].weight>heap[i/2].weight)&&(i*2+1<=*(n))){ //右小孩在節點裡 有兩種case:1.右節點>左節點 case:2左節點>右節點 
					heap[i].weight = heap[i*2].weight;
					heap[i].id = heap[i*2].id;
					i = i*2;
				}
				else{
					heap[i].weight = heap[i*2+1].weight;
					heap[i].id = heap[i*2+1].id;
					i = i*2+1;
				}
			}
			else{ 
				heap[i].weight = heap[i*2].weight;
				heap[i].id = heap[i*2].id;
				i = i*2;
			}
		}
		heap[i].weight = temp->weight;
		heap[i].id = temp->id;
	}
}
void create(int *top){
	int node_number,temp,i;
	do{
		printf("\n請輸入要建立的節點數: ");
		scanf("%d",&node_number);      //輸入要建構的節點數 
	}while(!(node_number>0));
	for(i=1;i<=node_number;i++){
		printf("\n Node %d 的weight: ",i);
		scanf("%d",&temp);
		if(i==1){
			heap[i].weight = temp;
			heap[i].id = i;
		}
		else{
			NODE *NEW_NODE = (NODE *) malloc(sizeof(NODE));
			NEW_NODE->weight = temp;
			NEW_NODE->id = i; 
			push(NEW_NODE,top);
		}
	}
}
void display(int *n){
	int i;
	printf("\nminimum node ==>level order如下:\n");
	for(i=1;i<=*n;i++){
		printf("%d ",heap[i].id);
	}
	printf("\n\n");
}
bool check(int temp,int * n){
	int i;
	bool exist = false;
	for(i=1;i<=*n;i++){
		if(heap[i].id==temp){
			exist = true;
			return exist;
		}
	}
	return exist;
}
void main(){
	printf("1.Create a min heap 2.Remove the key with the lowest value 3.Change the priority of an arbitrary element 4.Insert an element into the heap\n");
	int operation=1;
	int current_num=1;
	int *top = &current_num;
	int i;
	do{
		do{
			if(operation!=1){
				printf("請先建立min heap\n");
			}
			scanf("%d",&operation);
		}while(operation!=1);
		create(top); //先建立heap 
	}while(HEAP_EMPTY(top));
	display(top);
	do{
		printf("請輸入下進行的操作: (如果要停止操作請輸入-1)\n");
		scanf("%d",&operation);
		
		switch(operation){
			case 1:{
				for(i=1;i<=*top;i++){
					heap[i].weight = -1;
					heap[i].id = -1;
				}
				current_num = 1;
				create(top); //先建立heap 
				break;	
			}
			case 2:{
				pop(top);
				break;
			}
			case 3:{
				int num,bechange;
				bool exist = false;
				do{
					printf("請輸入你想改變的 NODE id:");
					scanf("%d",&num);
					exist = check(num,top); //節點存在就回傳true 
					if(!exist){
						printf("節點不存在\n");
					}
				}while(!exist);
				printf("請輸入 NODE %d 將變成多少權重: ",num);
				scanf("%d",&bechange);
				change(num,bechange,top);
				break;
			}
			case 4:{
				int new_id,new_weight;
				bool exist;
				do{
					exist = false;
					printf("請輸入你想要插入的NODE id: ");
					scanf("%d",&new_id);
					exist = check(new_id,top);
					if(exist == true){
						printf("NODE %d 已經存在了，請勿再次插入\n",new_id);
					}
				}while(exist==true);
				
				printf("請輸入想要插入的 NODE %d 節點的權重: ",new_id);
				scanf("%d",&new_weight);
				NODE * temp = (NODE *) malloc(sizeof(NODE));
				temp->id = new_id;
				temp->weight = new_weight;
				push(temp,top);
				break;
			}
		}
		display(top);
	}while(operation!=-1);
}
