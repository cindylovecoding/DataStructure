//finsihed in 2021/11/06 ¸­±©ªY F74109016 
#include<stdio.h>
#include<stdlib.h>
typedef int bool;  
enum { false, true }; 
typedef struct threadedTree *threadedPointer;

struct threadedTree{
	threadedPointer leftChild;
	int data;
	threadedPointer rightChild;
	bool rightThread;
	bool leftThread;
};

threadedPointer insucc(threadedPointer tree){
	threadedPointer temp;
	temp = tree->rightChild;
	if(tree->rightThread==false){
		while(temp->leftThread==false){
			temp = temp->leftChild;
		}
	}
	return temp;
}
threadedPointer inasce(threadedPointer tree){
	threadedPointer temp;
	temp = tree->leftChild;
	if(tree->leftThread==false){
		while(temp->rightThread==false){
			temp = temp->rightChild;
		}
	}
	return temp;
}
void inorder(threadedPointer tree){
	threadedPointer temp = tree;
	for(;;){
		if(temp != NULL){
			printf("%d ",temp->data);
			temp = insucc(temp);
		}
		else{
			break;
		}
	}
}

threadedPointer tinorder(threadedPointer tree,int _id){
	threadedPointer temp = tree;
	for(;;){
		if(temp!= NULL){
			if(temp->data == _id){
				return temp;
			}
			temp = insucc(temp);	
		}
		else{
			return NULL;
		}
	}
}

void insertLeft(threadedPointer s,threadedPointer l){
	threadedPointer temp;
	l->leftChild = s->leftChild;
	l->leftThread = s->leftThread;
	l->rightChild = s;
	l->rightThread = true;
	s->leftChild = l;
	s->leftThread = false;
	if(l->leftThread==false){
		temp = inasce(l);
		temp->rightChild = l;
	} 
}

void insertRight(threadedPointer s,threadedPointer r){
	threadedPointer temp;
	//ª¬ªp¤@ 
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = true;
	s->rightChild = r;
	s->rightThread = false;
	//ª¬ªp¤G 
	if(r->rightThread==false){
		temp = insucc(r);
		temp->leftChild = r;
	}
}
threadedPointer leftMost(threadedPointer n){
	if(n == NULL){
		return NULL;
	}
	while(n->leftChild != NULL){
		n = n->leftChild;
	}
	return n;
}
int main(){
	int n,r;
	
	scanf("%d %d",&n,&r);                          
	//n represents the number of threaded binary tree insertion operation.
	//r represents the node id of the root node.
							                  
	int i,parent_id,direction,new_node_id;         //direction 0:¥ª 1:¥k 
	char string [20];
	int direction_array[n+1];
	int parent_array[n+1];
	int new_node_array[n+1];
	
	threadedPointer root = (threadedPointer) malloc (sizeof(struct threadedTree)); 
	root->leftThread = true;
	root->rightThread = true;
	root->rightChild = NULL;
	root->leftChild = NULL;
	root->data = r;
	
	for(i=1;i<n+1;i++){
		scanf("%d",&parent_array[i]);
		scanf("%s",string);
		if(strcmp(string,"left")==0){
			direction_array[i] = 0; //0:¥ª 
		}
		if(strcmp(string,"right")==0){
			direction_array[i] = 1;
		}
		scanf("%d",&new_node_array[i]);
		 
		threadedPointer leftmost = leftMost(root);
		
		if(direction_array[i]==0){
			threadedPointer l = (threadedPointer) malloc (sizeof(struct threadedTree));
			l->leftThread = false;
			l->rightThread = true;
			l->rightChild = NULL;
			l->leftChild = NULL;
			l->data = new_node_array[i];
			threadedPointer s = tinorder(leftmost,parent_array[i]);
			insertLeft(s,l);
		}
		
		if(direction_array[i]==1){
			threadedPointer r = (threadedPointer) malloc (sizeof(struct threadedTree));
			r->leftThread = true;
			r->rightThread = false;
			r->rightChild = NULL;
			r->leftChild = NULL;
			r->data = new_node_array[i]; 
			threadedPointer s = tinorder(leftmost,parent_array[i]);
			insertRight(s,r);
		}
	}
	threadedPointer leftmost1 = leftMost(root);
	inorder(leftmost1);
}
