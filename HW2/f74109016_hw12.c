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
	if(temp->weight<heap[i/2].weight&&i!=1){ //����`�I�٤p 
		while((temp->weight < heap[i/2].weight)&&i!=1){ //����`�I�٤p 
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
				if((heap[i/2+1].weight>heap[i/2].weight)&&(i*2+1<=*(n))){ //�k�p�Ħb�`�I�� �����case:1.�k�`�I>���`�I case:2���`�I>�k�`�I 
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
		printf("\n�п�J�n�إߪ��`�I��: ");
		scanf("%d",&node_number);      //��J�n�غc���`�I�� 
	}while(!(node_number>0));
	for(i=1;i<=node_number;i++){
		printf("\n Node %d ��weight: ",i);
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
	printf("\nminimum node ==>level order�p�U:\n");
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
				printf("�Х��إ�min heap\n");
			}
			scanf("%d",&operation);
		}while(operation!=1);
		create(top); //���إ�heap 
	}while(HEAP_EMPTY(top));
	display(top);
	do{
		printf("�п�J�U�i�檺�ާ@: (�p�G�n����ާ@�п�J-1)\n");
		scanf("%d",&operation);
		
		switch(operation){
			case 1:{
				for(i=1;i<=*top;i++){
					heap[i].weight = -1;
					heap[i].id = -1;
				}
				current_num = 1;
				create(top); //���إ�heap 
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
					printf("�п�J�A�Q���ܪ� NODE id:");
					scanf("%d",&num);
					exist = check(num,top); //�`�I�s�b�N�^��true 
					if(!exist){
						printf("�`�I���s�b\n");
					}
				}while(!exist);
				printf("�п�J NODE %d �N�ܦ��h���v��: ",num);
				scanf("%d",&bechange);
				change(num,bechange,top);
				break;
			}
			case 4:{
				int new_id,new_weight;
				bool exist;
				do{
					exist = false;
					printf("�п�J�A�Q�n���J��NODE id: ");
					scanf("%d",&new_id);
					exist = check(new_id,top);
					if(exist == true){
						printf("NODE %d �w�g�s�b�F�A�ФŦA�����J\n",new_id);
					}
				}while(exist==true);
				
				printf("�п�J�Q�n���J�� NODE %d �`�I���v��: ",new_id);
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
