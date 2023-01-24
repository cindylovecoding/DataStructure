//f74109016_hw21_OK
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
/***********binomial heap*****************/
struct node {
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};

struct node* MAKE_bin_HEAP();
int bin_LINK(struct node*, struct node*);
struct node* CREATE_NODE(int);
struct node* bin_HEAP_UNION(struct node*, struct node*);
struct node* bin_HEAP_INSERT(struct node*, struct node*);
struct node* bin_HEAP_MERGE(struct node*, struct node*);
struct node* bin_HEAP_EXTRACT_MIN(struct node*);
int REVERT_LIST(struct node*);
 
int count = 1;
 
struct node* MAKE_bin_HEAP() {   //做出一個空的heap 
    struct node* np;
    np = NULL;
    return np;
}
 
struct node * H = NULL;
struct node * Hr = NULL;
 
int bin_LINK(struct node* y, struct node* z) {   //有heap的link 
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
 
struct node* CREATE_NODE(int k) {              //新增一個節點 
    struct node* p;//new node;
    p = (struct node*) malloc(sizeof(struct node));
    p->n = k;
    return p;
}
 
struct node* bin_HEAP_UNION(struct node* H1, struct node* H2) { //將兩個heap結合 
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = MAKE_bin_HEAP(); //先建一個空的heap這是作為合併後的heap 
    H = bin_HEAP_MERGE(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL) {           //如果有兄弟節點 
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree)) { 
			//如果x的degree不等於x兄弟的degree，或是x兄弟的兄弟degree等於x的degree。 
            prev_x = x;
            x = next_x;
        } 
		else {
            if (x->n <= next_x->n) { //大小 
                x->sibling = next_x->sibling;
                bin_LINK(next_x, x); //x是父節點，next_x是子節點 
            } 
			else {
                if (prev_x == NULL){ 
                    H = next_x;
                } 
                else{ 
                    prev_x->sibling = next_x;
                } 
                bin_LINK(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}
 
struct node* bin_HEAP_INSERT(struct node* H, struct node* x) {
    struct node* H1 = MAKE_bin_HEAP();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_HEAP_UNION(H, H1);
    return H;
}
 
struct node* bin_HEAP_MERGE(struct node* H1, struct node* H2) {
    struct node* H = MAKE_bin_HEAP();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else if (z != NULL && y->degree > z->degree)
            H = z;
        else //z 為Null 
            H = y;
    } 
	else //y是null 
        H = z;
    while (y != NULL && z != NULL) {
        if (y->degree < z->degree) {
            y = y->sibling;
        } else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}
struct node* bin_HEAP_EXTRACT_MIN(struct node* H1) {
    int min;
    struct node* t = NULL;
    struct node* x = H1;
    struct node *Hr;
    struct node* p;
    Hr = NULL;
    if (x == NULL) {
        return x;
    }
    min=x->n;
    p = x;
    while (p->sibling != NULL) {
        if ((p->sibling)->n < min) {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL) {
        REVERT_LIST(x->child);
        (x->child)->sibling = NULL;
    }
    H = bin_HEAP_UNION(H1, Hr);
    return x;
}
 
int REVERT_LIST(struct node* y) {
    if (y->sibling != NULL) {
        REVERT_LIST(y->sibling);
        (y->sibling)->sibling = y;
    } 
	else {
        Hr = y;
    }
}
/***********binomial heap*****************/
/***********leftist heap*****************/
typedef struct leftist Tree;

struct leftist{
	Tree * leftChild;
	int data;
	Tree * rightChild;
	int shortest;
};

typedef int bool;  
enum { false, true };  
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
void delete_min(Tree *a){
	if(a!=NULL){
		Tree * b  = (Tree *) malloc(sizeof(Tree));
		if(a->rightChild!=NULL){ 
			*b = *(a->rightChild);
			*a = *(a->leftChild);
			minMeld(a,b);
		}
		else{ 
			*a = *(a->leftChild);
		}
	}
} 
/******************leftist heap********************************/
int main() {
    int i, n, m, l,op;
    struct node* p;
    struct node* np;
    char ch;
    srand(time(NULL));
    

    printf("\nEnter the number of elements:");
    scanf("%d",&n);
    

    printf("\nEnter the number of operation:");
    scanf("%d",&op);
    
    int op_array[op];
    for (i = 0; i< op; i++){ 
    	op_array[i] = rand()%2;
	}

	double dqFreq;		//計時器頻率



    int start1 = clock();
    for (i = 1; i <= n; i++) {
        m = rand()%n;
        np = CREATE_NODE(m);
        H = bin_HEAP_INSERT(H, np);
    }
    for (i = 0;i< op;i++){
        switch (op_array[i]){
        	case 0:
        	    m = rand()%n;
        	    p = CREATE_NODE(m);
        	    H = bin_HEAP_INSERT(H, p);
        	    break;
        	case 1:
        	    p = bin_HEAP_EXTRACT_MIN(H);
        	    break;
        }
    }
    double elapsedTime1 = (double) (clock() -start1)/CLOCKS_PER_SEC;
	printf("elapsedTime (binomial heap): %fus  每個operation time %fus\n",elapsedTime1,elapsedTime1/5000);
	Tree *a = (Tree *) malloc(sizeof(Tree));
	Tree *b;
	a->shortest = 1;
	a->leftChild = NULL;
	a->rightChild = NULL;
	
	int start2 = clock();
	for (i = 1; i <= n; i++) {
		b  = (Tree *) malloc(sizeof(Tree));
		b->shortest = 1;
		b->leftChild = NULL;
		b->rightChild = NULL;
		int data = (rand()%n)+1;
		b->data = data;
		a =minUnion(a,b);
    }
    for (i = 0;i< op;i++){
        switch (op_array[i]){
        	case 0:
        	    b  = (Tree *) malloc(sizeof(Tree));
				b->shortest = 1;
				b->leftChild = NULL;
				b->rightChild = NULL;

				int data = (rand()%n)+1;				
				b->data = data;
				a =minUnion(a,b);
        	    break;
        	case 1:
        	    delete_min(a);
        	    break;
        }
    }
    double elapsedTime2 = (double) (clock() -start2)/CLOCKS_PER_SEC;
	printf("elapsedTime (leftist heap): %fus  每個operation time %fus\n",elapsedTime2,elapsedTime2/5000);
}
