#include<stdio.h>
#include<stdlib.h>
typedef int bool;  
enum { false, true };  
typedef struct PatriciaTrieNode NODE;
struct PatriciaTrieNode{
	int number;
	char* data;
	NODE* leftChild,*rightChild; 
};
static NODE* root;
static int MaxBits = 20;
bool isEmpty(){	
	if(root == NULL){
		return true;
	}
	else{
		return false;
	}
}
void makeEmpty(){ root = NULL;}
bool bit(char* k,int i){
	if(k[i-1]=='1'){
		return true;
	}
	return false;
}
NODE* search2(NODE* t,char* k){
	NODE *currentNode,*nextNode;
	if(t ==  NULL){
		return NULL;
	}
	printf("search2 : %s",*k);
	nextNode = t->leftChild;
	currentNode = t;
	while(nextNode->number > currentNode->number){
		currentNode = nextNode;
		nextNode = (bit(k,nextNode->number))?nextNode->rightChild:nextNode->leftChild;
	}
	return nextNode;
}
bool search1(char* k){
	NODE* searchNode = search2(root,k);
	if(searchNode != NULL){
		printf("searchNode->data = %s",searchNode->data);
		if(strcmp(*(searchNode->data),*(k)==0)){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
NODE* insert(NODE* t,const char [] element){
	NODE *current = NULL,*parent,*lastNode,*newNode;
	int i;
	if(t==NULL){
		t = (NODE*) malloc(sizeof(NODE));
		t->number = 0;
		t->data = element;
		t->leftChild = t;
		t->rightChild = NULL;
		printf("insert : %s",element);
		return t;
	}
	lastNode = search2(t,element);
	if(element == lastNode->data){
		printf("Key already Present");
		return t;
	}
	for(i = 1;bit(element,i) == bit(lastNode->data,i);i++){
		current = t->leftChild;
	}
	parent = t;
	while(current->number > parent->number && current->number <i){
		parent = current;
		current = (bit(element,current->number))?current->rightChild:current->leftChild;
	}
	newNode = (NODE*) malloc(sizeof(NODE));
	newNode->number = i;
	newNode->data = element;
	newNode->leftChild = bit(element,i)? current: newNode;
	newNode->rightChild = bit(element,i)? newNode: current;
	if(current == parent->leftChild){
		parent->leftChild = newNode;
	}
	else{
		parent->rightChild = newNode;	
	}
	return t;
}
int main(){
	int number_of_bits,num;
	char s[10000];
	NODE* tree = NULL;
	scanf("%d",&number_of_bits);
	do{
		scanf("%s",s);
		if(strcmp(s,"insert")==0){
			scanf("%s",s);
			tree = insert(tree,s);
		}
		else if(strcmp(s,"search")==0){
			scanf("%s",s);
			if(search1(s)){
				printf("search -> %s\n",s);
			}
			else{
				printf("search -> not found\n");
			}
		}
	}while(strcmp(s,"quit")!=0);
}
