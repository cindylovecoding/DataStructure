//f74109016_hw24
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define HEIGHT(node) ((node == NULL) ? 0:(((AVL_NODE *)(node))->height))
#define MAX(a,b) ((a)>(b)?(a):(b))
/*************************************AVLtree*******************************************/
/*************************************AVLtree*******************************************/
/*************************************AVLtree*******************************************/
/*************************************AVLtree*******************************************/
typedef int elementType;
typedef struct avl_node AVL_NODE;
struct avl_node{
	elementType key;
	AVL_NODE * left;
	AVL_NODE * right;
	int height;
};

AVL_NODE * avl_tree = NULL;

static int getNode_height(AVL_NODE * node){ //獲取當前節點的深度 
	return HEIGHT(node);
}
static int bf(AVL_NODE *n);
static AVL_NODE *create_node(elementType key,AVL_NODE *left,AVL_NODE *right);

static AVL_NODE * maximun_node(AVL_NODE * tree); //求樹中最大節點 

static AVL_NODE * minimun_node(AVL_NODE * tree);

static AVL_NODE * avltree_insertNode(AVL_NODE * tree,elementType key);  //向樹中插入節點

static AVL_NODE * avltree_deleteNode(AVL_NODE * tree,elementType key);  //刪除節點

static AVL_NODE * search_node(AVL_NODE * tree,elementType key); //根據key的值搜尋節點

static AVL_NODE * maximun_node(AVL_NODE * tree){
	while(tree->right!=NULL){
		tree = tree->right;
	}
	return tree;
}

static AVL_NODE * minimun_node(AVL_NODE * tree){
	while(tree->left!=NULL){
		tree = tree->left;
	}
	return tree;
}
static AVL_NODE * create_node(elementType key,AVL_NODE * left,AVL_NODE * right){
	AVL_NODE * node = (AVL_NODE *) malloc(sizeof(AVL_NODE));
	node->key = key;
	node->left = left;
	node->right = right;
	node->height = 0; //初始化高度為0
	return node;	
}

static AVL_NODE * LL_rotation(AVL_NODE * tree){
	AVL_NODE *k2 = tree->left;
	tree->left = k2->right;
	k2->right = tree;
	tree->height = MAX(getNode_height(tree->left),getNode_height(tree->right)) +1;
	k2->height = MAX(getNode_height(tree->left),getNode_height(tree->right)) +1;
	return k2;
}
static AVL_NODE * RR_rotation(AVL_NODE * tree){
	AVL_NODE *k3 = tree->right;
	tree->right = k3->left;
	k3->left = tree;
	tree->height = MAX(getNode_height(tree->left),getNode_height(tree->right)) +1;
	k3->height = MAX(getNode_height(tree->left),getNode_height(tree->right)) +1;
	return k3;
}
static AVL_NODE * LR_rotation(AVL_NODE * tree){
	tree->left = RR_rotation(tree->left);
	tree = LL_rotation(tree);
	return tree;
}
static AVL_NODE * RL_rotation(AVL_NODE * tree){
	tree->right = LL_rotation(tree->right);
	tree = RR_rotation(tree);
	return tree;
}

static AVL_NODE * avltree_insertNode(AVL_NODE * tree,elementType key){
	if(tree == NULL){
		AVL_NODE *node = create_node(key,NULL,NULL);
		tree = node;
	}
	else if(key < tree->key){
		tree->left = avltree_insertNode(tree->left,key); //遞迴找插入的節點 
		//插入節點後可能引起二叉樹的不平衡， 所以要再進行判斷
		if(getNode_height(tree->left)-getNode_height(tree->right)==2){
			//判斷是LL還是LR 
			if(key < tree->left->key){
				//LL旋轉
				tree = LL_rotation(tree); 
			}
			else{
				//LR旋轉
				tree = LR_rotation(tree); 
			}
		} 
	}
	else if(key > tree->key){
		tree->right = avltree_insertNode(tree->right,key);
		if(getNode_height(tree->right)-getNode_height(tree->left)==2){
			//判斷是RR還是RL
			if(key > tree->right->key){
				tree = RR_rotation(tree);
			} 
			else{
				tree = RL_rotation(tree);
			}
		}
	}
	//重新調整二元數的高度
	tree->height = MAX(getNode_height(tree->left),getNode_height(tree->right)) +1;
	return tree;
}

static AVL_NODE * search_node(AVL_NODE * tree,elementType key){
	AVL_NODE* n = tree;
	while(n!= NULL){
		if(n->key == key){
			return n;
		}
		else if(key < n->key){
			n = n->left;
		} 
		else{
			n = n->right;
		}
	} 
	return n;
}
static AVL_NODE * delete_node(AVL_NODE * tree,AVL_NODE *z){
	if(tree == NULL || z==NULL){
		free(tree);
		return NULL;
	}
	if(tree->left == NULL && tree->right == NULL){
		return tree;
	}
	if(z->key < tree->key){
		tree->left = delete_node(tree->left,z);
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2){
			AVL_NODE *r = tree->right;
			if(HEIGHT(r->left) > HEIGHT(r->right)){
				tree = RL_rotation(tree);
			}
			else{
				tree = RR_rotation(tree);
			}
		}
	}
	else if(z->key > tree->key){
		tree->right = delete_node(tree->right,z);
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2){
			AVL_NODE *l = tree->left;
			if(HEIGHT(l->right) > HEIGHT(l->left)){
				tree = LR_rotation(tree);
			}
			else{
				tree = LL_rotation(tree);
			}
		}
	}
	else{
		//左右小孩都非空 
		if((tree->left) && (tree->right)){
			if(HEIGHT(tree->left)>HEIGHT(tree->right)){
				AVL_NODE * max = maximun_node(tree->left);
				tree->key = max->key;
				tree->left = delete_node(tree->left,max);
			} 
			else{
				AVL_NODE * min = minimun_node(tree->right);
				tree->key = min->key;
				tree->right = delete_node(tree->right,min);
			}
		} 
		else{
			AVL_NODE *tmp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(tmp);
		}
	}
	return tree;
}
static AVL_NODE * avltree_delete(AVL_NODE * tree, elementType key){
    AVL_NODE * z; 

    if ((z = search_node(tree, key)) != NULL)
        tree = delete_node(tree, z);
    return tree;
}
/*************************************AVLtree*******************************************/
/*************************************AVLtree*******************************************/
/*************************************AVLtree*******************************************/
/*************************************AVLtree*******************************************/
/*************************************RBtree*******************************************/
/*************************************RBtree*******************************************/
/*************************************RBtree*******************************************/
/*************************************RBtree*******************************************/
enum rbtree_node_color{RED,BLACK};
typedef enum rbtree_node_color color;
typedef struct rb_node RB_NODE;
struct rb_node{
	int key;
	RB_NODE * left;
	RB_NODE * right;
	RB_NODE * parent;
	enum rbtree_node_color color; 
};

static RB_NODE* RB_tree = NULL;

static RB_NODE* new_node(int key, color node_color, RB_NODE* left, RB_NODE* right);
static void rbtree_insert(int key);
static void insert_case1(RB_NODE* n);
static void insert_case2(RB_NODE* n);
static void insert_case3(RB_NODE* n);
static void insert_case4(RB_NODE* n);
static void insert_case5(RB_NODE* n);

static color node_color(RB_NODE* n);

static void rotate_left(RB_NODE* n);
static void rotate_right(RB_NODE* n);
static void replace_node(RB_NODE* oldn, RB_NODE* newn);
static RB_NODE* maximum_node(RB_NODE* root);
static void delete_case1(RB_NODE* n);
static void delete_case2(RB_NODE* n);
static void delete_case3(RB_NODE* n);
static void delete_case4(RB_NODE* n);
static void delete_case5(RB_NODE* n);
static void delete_case6(RB_NODE* n);
static RB_NODE* lookup_node(int key);
static int compare(int left,int right){
	if(left<right){
		return -1;
	}
	else if(right<left){
		return 1;
	}
	else{
		return 0;
	}
}
static RB_NODE* grandparent(RB_NODE* n) {
    if(((n != NULL)&&(n->parent != NULL))&&(n->parent->parent != NULL))
    return n->parent->parent;
}

static RB_NODE* sibling(RB_NODE* n) {
    if(n!=NULL&&n->parent != NULL){
    	if (n == n->parent->left)
        	return n->parent->right;
    	else
        	return n->parent->left;
    }
    else{
    	return NULL;
	}
}

static RB_NODE* uncle(RB_NODE* n) {
    if(((n != NULL) &&(n->parent != NULL))&&(n->parent->parent != NULL)){ 
    	return sibling(n->parent);
    } 
}

static RB_NODE* new_node(int key , color node_color, RB_NODE* _left, RB_NODE* _right) {
    RB_NODE * result = (RB_NODE *)malloc(sizeof(RB_NODE));
    result->key = key;
    result->color = node_color;
    result->left = _left;
    result->right = _right;
    if (_left  != NULL) _left->parent = result;
    if (_right != NULL) _right->parent = result;
    result->parent = NULL;
    return result;
}

static void rbtree_insert(int key) {
    RB_NODE* inserted_node = new_node(key, RED, NULL, NULL);
    if (RB_tree == NULL) {
        RB_tree = inserted_node;
    } 
	else {
        RB_NODE* n = RB_tree;
        while (1) {
            int comp_result = compare(key, n->key);
            if (comp_result == 0) {
                free (inserted_node);
                return;
            } 
			else if (comp_result < 0) {
                if (n->left == NULL) {
                    n->left = inserted_node;
                    break;
                } 
				else { n = n->left; }
            } 
			else {
                if (n->right == NULL) {
                    n->right = inserted_node;
                    break;
                } 
				else { n = n->right; }
            }
        }
        inserted_node->parent = n;
    }
    insert_case1(inserted_node);
}

static color node_color(RB_NODE* n) {
    return n == NULL ? BLACK : n->color;
}


static void insert_case1(RB_NODE* n) {
    if (n->parent == NULL)
        n->color = BLACK;
    else insert_case2(n);
}
static void insert_case2(RB_NODE* n) {
    if (node_color(n->parent) == BLACK)
        return;
    else insert_case3(n);
}
static void insert_case3(RB_NODE* n) {
    if (node_color(uncle(n)) == RED) {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_case1(grandparent(n));
    } 
	else  insert_case4(n); //uncle是黑色的 
}
static void insert_case4(RB_NODE* n) {
    if (n == n->parent->right && n->parent == grandparent(n)->left) { //在grandparent的左右 
        rotate_left(n->parent);
        n = n->left;
    } 
	else if (n == n->parent->left && n->parent == grandparent(n)->right) { //在grandparent的右左 
        rotate_right(n->parent);
        n = n->right;
    }
    //右右或左左 
    insert_case5(n);
}
static void insert_case5(RB_NODE* n) {
    n->parent->color = BLACK;
    grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == grandparent(n)->left) { //左左 
        rotate_right(grandparent(n));
    } 
	else if(n == n->parent->right && n->parent == grandparent(n)->right){ //右右 
        rotate_left(grandparent(n));
    }
}

static void rotate_left(RB_NODE* n) { ////在grandparent的左右 左轉 
    RB_NODE* r = n->right;
    replace_node(n, r); //
    n->right = r->left;
    if (r->left != NULL) {
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
}

static void rotate_right(RB_NODE* n) {
    RB_NODE* L = n->left;
    replace_node(n, L);
    n->left = L->right;
    if (L->right != NULL) {
        L->right->parent = n;
    }
    L->right = n;
    n->parent = L;
}

static void replace_node(RB_NODE* oldn, RB_NODE* newn) {
    if (oldn->parent == NULL) {
        RB_tree = newn;
    } 
	else {
        if (oldn == oldn->parent->left)
            oldn->parent->left = newn;
        else
            oldn->parent->right = newn;
    }
    if (newn != NULL) {
        newn->parent = oldn->parent;
    }
}
static void rbtree_delete(int key) {
    RB_NODE* child;
    int comp_result = compare(key, RB_tree->key);
    RB_NODE* n = lookup_node(key);
    if (n != NULL){
    	if (n->left != NULL && n->right != NULL) {
        	RB_NODE* pred = maximum_node(n->left);
        	n->key  = pred->key;
        	n = pred;
    	}
    	if((n->left == NULL || n->right == NULL)){
    		child = n->right == NULL ? n->left  : n->right;
    		if (node_color(n) == BLACK) {
      		  	n->color = node_color(child);
       		 	delete_case1(n);
    		}
    		replace_node(n, child);
    		if (n->parent == NULL && child != NULL)
        		child->color = BLACK;
    		free(n);
    	}
    }
}

static RB_NODE* maximum_node(RB_NODE* n) {
    if(n != NULL){
    	while (n->right != NULL) {
        	n = n->right;
    	}
    	return n;
    }
}
static void delete_case1(RB_NODE* n) {
    if (n->parent == NULL)
        return;
    else
        delete_case2(n);
}

static void delete_case2(RB_NODE* n) {
    if (node_color(sibling(n)) == RED) {
        n->parent->color = RED;
        sibling(n)->color = BLACK;
        if (n == n->parent->left)
            rotate_left(n->parent);
        else
            rotate_right(n->parent);
    }
    delete_case3(n);
}

static void delete_case3(RB_NODE* n) {
    if (node_color(n->parent) == BLACK &&
        node_color(sibling(n)) == BLACK &&
        node_color(sibling(n)->left) == BLACK &&
        node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        delete_case1(n->parent);
    }
    else
        delete_case4(n);
}

static void delete_case4(RB_NODE* n) {
    if (node_color(n->parent) == RED &&
        node_color(sibling(n)) == BLACK &&
        node_color(sibling(n)->left) == BLACK &&
        node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(n);
}

static void delete_case5(RB_NODE* n) {
    if (n == n->parent->left &&
        node_color(sibling(n)) == BLACK &&
        node_color(sibling(n)->left) == RED &&
        node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->left->color = BLACK;
        rotate_right(sibling(n));
    }
    else if (n == n->parent->right &&
             node_color(sibling(n)) == BLACK &&
             node_color(sibling(n)->right) == RED &&
             node_color(sibling(n)->left) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->right->color = BLACK;
        rotate_left(sibling(n));
    }
    delete_case6(n);
}

static void delete_case6(RB_NODE* n) {
    sibling(n)->color = node_color(n->parent);
    n->parent->color = BLACK;
    if (n == n->parent->left) {
        if(node_color(sibling(n)->right) == RED){
        	sibling(n)->right->color = BLACK;
        	rotate_left(n->parent);
        }
    }
    else
    {
        if(node_color(sibling(n)->left) == RED){
        	sibling(n)->left->color = BLACK;
        	rotate_right(n->parent);
        }
    }
}
static RB_NODE* lookup_node(int key) {
    RB_NODE* n = RB_tree;
    while (n != NULL) {
        int comp_result = compare(key, n->key);
        if (comp_result == 0) {
            return n;
        } 
		else if (comp_result < 0) {
            n = n->left;
        } 
		else {
            n = n->right;
        }
    }
    return n;
}

static void search(int key){
	RB_NODE* n = RB_tree;
    while (n != NULL) {
        int comp_result = compare(key, n->key);
        if (comp_result == 0) {
            if(n->color == 0){
            	//printf("red\n");
			}
			else{
				//printf("black\n");
			}
			break;
        } 
		else if (comp_result < 0) {
            n = n->left;
        } 
		else {
            n = n->right;
        }
    }
    if(n==NULL){
    	//printf("Not found\n");
	}
}
/*************************************RBtree*******************************************/
/*************************************RBtree*******************************************/
/*************************************RBtree*******************************************/
/*************************************RBtree*******************************************/

int main(){
	long int n,m,i;

    printf("Please input the number of nodes:");
    scanf("%d",&n);
    printf("Please input the time of operations: ");
	scanf("%d",&m);
	srand(time(NULL));
	
    int array[n];
    int arraytest[n];
    int operation[m];
    
    for(i=0;i<n;i++){
    	do{ 
    		array[i] = rand()%n+1;
    	}while(arraytest[array[i]]>0); 
	}
    for(i=0;i<m;i++){
    	int temp = rand()%2;
    	if(temp==0){
    		operation[i] = 0; //insert
		}
		else{
			temp = rand()%2;
			if(temp == 0){
				operation[i] = 1; //search
			}
			else{
				operation[i] = 2; //delete
			}
		}
	}
	clock_t start2 = clock();	//計時開始
	for(i=0;i<n;i++){
		rbtree_insert(array[i]);
	}
	for(i=0;i<m;i++){
		if(operation[i]==0){
			search(rand()%10000+1);
		}
		else if(operation[i]==1){
			rbtree_delete(rand()%10000+1);
		}
		else if(operation[i]==2){
			rbtree_insert(rand()%10000+1);
		}
    }
    double elapsedTime2 = (double) (clock() -start2)/CLOCKS_PER_SEC;
	printf("RedBlackTREE elapsedTime : %.20f\n",elapsedTime2);
	clock_t start1 = clock();
    /**AVL**/
    for(i=0;i<n;i++){
    	avl_tree = avltree_insertNode(avl_tree,array[i]);
	}
	for(i=0;i<m;i++){
		if(operation[i]==0){
			AVL_NODE * found =search_node(avl_tree,rand()%10000+1);
		}
		else if(operation[i]==1){
			if(avl_tree !=NULL){ 
				avl_tree = avltree_delete(avl_tree,rand()%10000+1);
			} 
		}
		else if(operation[i]==2){
			avl_tree = avltree_insertNode(avl_tree,rand()%10000+1);
		}
    }
    double elapsedTime1 = (double) (clock() -start1)/CLOCKS_PER_SEC;
	printf("AVLTREE elapsedTime : %.20f\n",elapsedTime1);
    
}

