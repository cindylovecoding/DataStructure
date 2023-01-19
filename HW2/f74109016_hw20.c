//Finished 
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000
#define HEAP_FULL(n)(n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)



/*********** leftist************/

typedef struct leftist Tree;

struct leftist{
	Tree * leftChild;
	int data;
	Tree * rightChild;
	int shortest;
	int id;
};
typedef struct node NODE;

typedef int bool;  
enum { false, true };  
struct node{
	int id;
	int data;
	NODE * next;
};
void SWAP(Tree *a,Tree *b,Tree* temp){
	*temp = *a;
	*a = *b;
	*b = *temp;
} 
Tree* minUnion(Tree *a,Tree *b){
	/*recursivelu combine two nonempty min leftist trees */
	Tree* temp =(Tree *) malloc(sizeof(Tree));
	/* set a to be the tree with smaller root*/

	if(a->data > b->data){
		SWAP(a,b,temp); //右子樹的數自比較多，先調整 
	}
	if(a->rightChild==NULL){           //如果沒有又子樹的話，就將b直接當作a的左子樹 
		a->rightChild = b; 
	} 
	else{

		minUnion(a -> rightChild,b); //遞迴呼叫 
	}
	//滿足leftchild的特性 
	if(a->leftChild==NULL){          //沒有左小孩 ，將右小孩作為左小孩。
		a->leftChild = a->rightChild;
		a->rightChild = NULL;
	}
	else if(a->leftChild->shortest < a->rightChild->shortest){ //左小孩的數量比右小孩小 
		SWAP(a->leftChild,a->rightChild,temp);
	}
	a->shortest = (!a->rightChild) ? 1: a->rightChild->shortest +1;
	return a;
}
void minMeld(Tree *a,Tree *b){
	if(a==NULL) *a = *b;
	else if(b!=NULL) minUnion(a,b);
	b = NULL;
}
int delete_min(Tree *a){
	Tree * b  = (Tree *) malloc(sizeof(Tree));
	int _id = a->id;
	if(a->rightChild!=NULL){ 
		*b = *(a->rightChild);
		*a = *(a->leftChild);
		minMeld(a,b);
	}
	else{ 
	*a = *(a->leftChild);
	}
	return _id;
} 
void traversal_inorder(Tree *a){
	if(a!=NULL){
		if(a->leftChild!=NULL){
			traversal_inorder(a->leftChild);
		}
		printf("| %d %d",a->id,a->shortest);
		if(a->rightChild!=NULL){
			traversal_inorder(a->rightChild);
		}
	}
}
void traversal_preorder(Tree *a){
	if(a!=NULL){
		printf("| %d %d",a->id,a->shortest);
		if(a->leftChild!=NULL){
			traversal_preorder(a->leftChild);
		}
		if(a->rightChild!=NULL){
			traversal_preorder(a->rightChild);
		}
	}
}
NODE* search(int _id,NODE* header){
	NODE* current= (NODE *)malloc(sizeof(NODE));
	current= header;
	while(current!=NULL){
		if(current->id == _id){
			return current;
		}
		current = current->next;
	}
	return NULL;
}
bool search_exist(int _id,NODE* header){
	NODE* current= (NODE *)malloc(sizeof(NODE));
	current= header;
	while(current!=NULL){
		if(current->id == _id){
			return true;
		}
		current = current->next;
	}
	return false;
}
void delete_list(int _id,NODE *header){
	NODE *current= (NODE *)malloc(sizeof(NODE));
	current= header;
	if(_id == header->id){
		header = header->next;
	}
	else{
		while(current->next!=NULL){
			if(_id == current->next->id){
				current->next = current->next->next;
				break;
			}
			else{
				current= current->next;
			}
		}
	}
}
/*********** leftist************/
/**************************************************min_heap******************/
typedef struct{
	int weight;
	int id;
}element_heap;
typedef element_heap ELEMENT;
ELEMENT heap[MAX_ELEMENTS];
void push(ELEMENT *item,int *n){ //insert item into a maz heap of current size *n
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
ELEMENT pop(int *n){
	int parent,child;
	ELEMENT item,temp;
	
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

void create(int *top){
	int node_number,temp,i;
	temp = rand()%100;
	heap[1].weight = temp;
	heap[1].id = 1;
}
void display(int *n){
	int i;
	printf("minimum node ==>level order如下:");
	for(i=1;i<=*n;i++){
		printf("%d ",heap[i].id);
	}
	printf("\n");
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
/**************************************************min_heap******************/
int main(){
	int node_number,i,operation_number;
	printf("Please input the number of nodes:");
	scanf("%d",&node_number);
	printf("Please input the time of operations: ");
	scanf("%d",&operation_number);
	
	srand(time(NULL));
	NODE *header = (NODE *)malloc(sizeof(NODE));
	NODE *current= (NODE *)malloc(sizeof(NODE));
	for(i=1;i<node_number+1;i++){
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		temp->id = i;
		temp->data = (rand()%100)+1;
		temp->next = NULL;
		
		if(i == 1){
			header = temp;
			current = header;
		}
		else{
			current->next = temp;
			current = current->next;
		}
	}
	Tree *a = (Tree *) malloc(sizeof(Tree));
	Tree *b;
	a->shortest = 1;
	a->leftChild = NULL;
	a->rightChild = NULL;
	
	int insert_times =0 ; //operation :0
 	int delete_times =0;  //operation :1
 	
 	int operation[operation_number];
 	for(i=0;i<operation_number;i++){
 		int temp = rand()%2;
 		if(temp == 0){
 			insert_times++;
 			operation[i] = 0;
		}
		else if(temp ==1){
			if(insert_times > delete_times+1){
				delete_times++;
				operation[i] = 1;
			}
			else{
				insert_times++;
 				operation[i] = 0;
			}
		}	
	}
	/*****
 	for(i=0;i<operation_number;i++){
 		printf("%d",operation[i]);
	}
	printf("\n");
	******/
	/*******************************************************leftist************************************/
	int start1 = clock(); 
	NODE *header_tree = (NODE *)malloc(sizeof(NODE));
	NODE *current_tree= (NODE *)malloc(sizeof(NODE));
	for(i=0;i<operation_number;i++){
		if(operation[i] == 0){
			int id;
			NODE* find = (NODE *)malloc(sizeof(NODE));
			NODE* exist = NULL;
			//printf("insert\n");
			
			
			if(i==0){
				do{
					id = (rand()%node_number)+1;
					find = search(id,header);
				}while(find == NULL);
				
				
				NODE *temp = (NODE *)malloc(sizeof(NODE));
				temp->id = find->id;
				temp->data = find->data;
				temp->next = NULL;
				header_tree = temp;
				current_tree = header_tree;
				
				a->data = find->data;	
				a->id = find->id;	
			}
			else{
				b  = (Tree *) malloc(sizeof(Tree));
				b->shortest = 1;
				b->leftChild = NULL;
				b->rightChild = NULL;
				bool exist = false;
				do{
					id = (rand()%node_number)+1;
					find = search(id,header);
					exist = search_exist(id,header_tree);
				}while(find == NULL&&exist==true);
				
				NODE *temp = (NODE *)malloc(sizeof(NODE));
				temp->id = find->id;
				temp->data = find->data;
				temp->next = NULL;
				current_tree->next = temp;
				current_tree = current_tree->next;
				
				b->data = find->data;
				b->id = find->id;
				a =minUnion(a,b);
			}
		}
		else if(operation[i] == 1){
			int _id = delete_min(a);
			//printf("delete\n");
			delete_list(_id,header_tree);
		}

		//traversal_inorder(a);
		//printf("\n");
		//traversal_preorder(a);
		//printf("\n\n");
	}
	double elapsedTime1 = (double) (clock() -start1)/CLOCKS_PER_SEC;
	printf("elapsedTime (leftist min heap): %.8f\n",elapsedTime1);
	/*******************************************************leftist************************************/
	
	/*******************************************************minheap************************************/
	int start2 = clock(); 
	int current_num=1;
	int *top = &current_num;
	//printf("operation_number %d\n",operation_number);
	for(i=0;i<operation_number;i++){
		if(operation[i] == 0){
			int id;
			//printf("insert\n");
			NODE* find = (NODE *)malloc(sizeof(NODE));
			if(i==0){
				create(top);
			}
			else{
				bool exist = false;
				int new_id;
				do{
					new_id = (rand()%node_number)+1;
					find = search(new_id,header);
					int j;
					for(j=1;j<=*top;j++){
						if(heap[j].id == new_id){
							exist = true;
							break;
						}
					}
				}while(find == NULL&&exist==true);
				
				ELEMENT *temp = (ELEMENT *)malloc(sizeof(ELEMENT));
				temp->id = new_id;
				temp->weight = rand()%100;
				push(temp,top);
			}
		}
		else if(operation[i] == 1){
			//printf("delete\n");
			pop(top);
		}
		//display(top);
	}
	double elapsedTime2 = (double) (clock() -start2)/CLOCKS_PER_SEC;
	printf("elapsedTime  (min heap): %.8f\n",elapsedTime2);
	/*******************************************************minheap************************************/
	return 0;
} 
