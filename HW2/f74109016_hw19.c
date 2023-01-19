#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
typedef struct node NODE;
struct node{
	int data;
	NODE * next;
	NODE * back;
};
typedef int bool;  
enum { false, true }; 


int main(){
	int vertex_number,i,j;
	scanf("%d",&vertex_number);
	int d[vertex_number+1];
	int p[vertex_number+1];
	for(i=1;i<vertex_number+1;i++){  
		d[i]=-1;
		p[i]=-1;
	}
	int array[vertex_number+1][vertex_number+1];
	for(i=0;i<vertex_number+1;i++){
		for(j=0;j<vertex_number+1;j++){
			array[i][j]=-1; //沒有權重 
		}
	}

	
	for(i=0;i<vertex_number-1;i++){
		int vertex1,vertex2,weight;
		scanf("%d %d %d",&vertex1,&vertex2,&weight);
		array[vertex1][vertex2]=weight;
		array[vertex2][vertex1]=weight;		
	}
	int root_id;
	scanf("%d",&root_id);
	p[root_id]=root_id;
	d[root_id]=0;

	NODE* current =(NODE*) malloc(sizeof(NODE));
	NODE* root =  (NODE*) malloc(sizeof(NODE));	//會變
	root->data = root_id;
	current = root;
	
	NODE* queue= (NODE*) malloc(sizeof(NODE)); //一個queue
		
	queue->data = root->data;
	queue->next = NULL;
	queue->back = NULL;
	current = queue;
	for(i=1;i<vertex_number+1;i++){

		bool first = true;
		for(j=1;j<vertex_number+1;j++){ 
			if(array[queue->data][j]!=-1&&j!=queue->data&&d[j]<0){
				
				NODE* NEWNODE = (NODE*) malloc(sizeof(NODE));
				NEWNODE->data =j;
				NEWNODE->back = current;
				current->next = NEWNODE;
				
				current = current->next; 
						
				if(d[queue->data]==0){
					d[j]=array[queue->data][j];
					p[j]=queue->data;
				}
				else{
					d[j]=d[queue->data]+array[queue->data][j];
					p[j]=queue->data;
				}
			}	 
		}
		if(queue->next!=NULL){
			queue = queue->next;
		}
		else{
			break;
		}
	}
	
	
	for(i=1;i<vertex_number+1;i++){
		printf("%d %d\n",i,d[i]);
	}
} 

