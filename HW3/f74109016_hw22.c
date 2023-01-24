//f74109016_hw22_OK
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int bool;  
enum { false, true }; 
static struct node {
    int v;
    int k;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* r_sibling;
    struct node* l_sibling;
}NODE;

static struct node* deg_arr [10]; 
static struct node* CREATE_NODE(int,int);
static struct node* F_HEAP_UNION(struct node*, struct node*);
static struct node* F_HEAP_INSERT(struct node*, struct node*);
static struct node* F_HEAP_MERGE(struct node*, struct node*);
static struct node* F_HEAP_EXTRACT_MIN(struct node*,bool);
static struct node* ADJUST(struct node*);
static struct node* FIND_NODE(struct node*, int);
static struct node* F_HEAP_DECREASE_KEY(struct node*, int, int);
static struct node* F_HEAP_DELETE(struct node*, int);
   
static struct node * H = NULL;
  
static struct node* CREATE_NODE(int key,int value) {              //新增一個節點 
    struct node* p;//new node;
    p = (struct node*) malloc(sizeof(struct node));
    p->v = value;
    p->k = key;
    return p;
}
 
static struct node* F_HEAP_UNION(struct node* H1, struct node* H2) { //將兩個heap結合 
    struct node* x = H1;
    struct node* y = H2;
    struct node* H = NULL; //先建一個空的heap這是作為合併後的heap 
    y->r_sibling = x->r_sibling;
    y->l_sibling = x;
	x->r_sibling->l_sibling = y;
	x->r_sibling = y;
	if(x->l_sibling == x){
		x->l_sibling = y;
	}
    H =x;
    return H;
}
 
static struct node* F_HEAP_INSERT(struct node* H, struct node* x) {
    struct node* H1 = NULL;
    x->parent = NULL;
    x->child = NULL;
    x->r_sibling = x;
    x->l_sibling = x;
    x->degree = 0;
    H1 = x;
    if(H!= NULL){
    	H = F_HEAP_UNION(H, H1);
    }
    else{
    	H= H1;
	}
    return H;
}
 
static struct node* F_HEAP_MERGE(struct node* H1, struct node* H2) {
    struct node* H = NULL;
    struct node* y;
    if(H1==NULL&&H2==NULL){
    	return NULL;
	}
	else if(H2==NULL){
		return H1;
	}
	else if(H1==NULL){
		return H2;
	}
	else{
    	H = F_HEAP_UNION(H1,H2);
    	do{
    		ADJUST(H);
		}while(deg_arr[y->degree]!=y);
    	return H;
    }
}

static struct node* ADJUST(struct node* H){
	int temp;
	if(deg_arr[H->degree]==NULL){
    	deg_arr[H->degree]=H;	
    }
    else{
		if(deg_arr[H->degree]->k < H->k){
   			temp = deg_arr[H->degree]->degree;
    		if(deg_arr[H->degree]->child == NULL){
    			deg_arr[H->degree]->child = H;
    			H = deg_arr[H->degree];
			} 
			else{
				H = F_HEAP_UNION(deg_arr[H->degree]->child,H);
			}
    		deg_arr[temp] = NULL; 
		}
		else{
			temp = H->degree;
    		if(H->child == NULL){
    			H->child = deg_arr[H->degree];
			} 
			else{
				F_HEAP_UNION(H->child,deg_arr[H->degree]);
			}
    		deg_arr[temp] = NULL; 
    	}
    	H->degree++;
    	ADJUST(H);
	}
	H=H->r_sibling;
	return H;
}
 
static struct node* F_HEAP_EXTRACT_MIN(struct node* H1,bool is_delete) {
    int min=2000;
    struct node* t = NULL;
    struct node* p = H1;
    do{
        if (p->k < min) {
            min = p->k;
            t = p;
        }
        p = p->r_sibling;
    }while(p->k != H1->k);
    
    t->r_sibling->l_sibling = t->l_sibling;
    t->l_sibling->r_sibling = t->r_sibling;
    
    if(t->child!=NULL){
    	t->child->parent = NULL;
    	H1 = H1->r_sibling;
    	H1 = F_HEAP_MERGE(t->child,H1);
    }
    else{
    	if(H1->r_sibling!=H1){
    		H1 = H1->r_sibling;
    	}
    	else{
    		H1 = NULL;
		}
	}
    t->r_sibling = NULL;
    t->l_sibling = NULL;
    if(is_delete == false)
	printf("(%d)%d\n",t->k,t->v);
    free(t);
    return H1;
}
 
static struct node* FIND_NODE(struct node* H, int y) {
    struct node* x = H;
    struct node* p = NULL;
    if (x->k == y) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = FIND_NODE(x->child, y);
    }
    if (x->r_sibling != NULL && p == NULL) {
        p = FIND_NODE(x->r_sibling, y);
    }
    return p;
}
 
static struct node* F_HEAP_DECREASE_KEY(struct node* H, int key, int y) {
    int temp;
    struct node* p;
    struct node* current = H;
    p = FIND_NODE(H, key);
    p->k -= y;
	if(p->parent != NULL){
		p->parent->child = NULL;
		H = F_HEAP_UNION(H,p);
	}
    return H;
}
 
static struct node* F_HEAP_DELETE(struct node* H, int k) {
    struct node* np;
    H = F_HEAP_DECREASE_KEY(H, k, 2000);
    return F_HEAP_EXTRACT_MIN(H,true);
} 
int main() {
    int val, key,y;
    struct node* p;
    char ch[50];
    do{
    	scanf("%s",ch);
    	if(strcmp(ch,"insert")==0){
            scanf("%d %d", &key,&val);
            p = CREATE_NODE(key,val);
            H = F_HEAP_INSERT(H, p);
        }
        else if(strcmp(ch,"extract")==0){
        	if(H!=NULL){ 
            	H = F_HEAP_EXTRACT_MIN(H,false);
            } 
    	}
        else if(strcmp(ch,"decrease")==0){
        	scanf("%d %d %d",&key,&val,&y);
            H =F_HEAP_DECREASE_KEY(H, key, y);
		}
        else if(strcmp(ch,"delete")==0){
            scanf("%d %d", &key,&val);
            H = F_HEAP_DELETE(H, key);
		}
    }while(strcmp(ch,"quit")!=0);
}
