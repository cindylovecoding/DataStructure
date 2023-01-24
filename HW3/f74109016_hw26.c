// f74109016_hw26_OK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Default order
#define ORDER 3
#define DEGREE 2
typedef enum { false, true }bool; 

// Node
typedef struct node {
	void **pointers;
	int *keys;
	struct node *parent;
	bool is_leaf;
	int num_keys;
	struct node * next;
} node;

int order = ORDER;
node *queue = NULL;

// Enqueue
static void enqueue(node *new_node);
// Dequeue
static node *dequeue(void);
static int height(node *const root);
static int pathToLeaves(node *const root, node *const child);
static void printLeaves(node *const root);
static void printTree(node *const root);
static void findAndPrint(node *const root, int key);
static void findAndPrintRange(node *const root, int range1, int range2);
static int findRange(node *const root, int key_start, int key_end,int returned_keys[], void *returned_pointers[]);
static node *findLeaf(node *const root, int key);
static node *findLeaf1(node *const root, int key);
static node *find(node *const root, int key, node **const leaf_out);
static int cut(int length);

static node *makeNode(void);
static node *makeLeaf(void);
static int getLeftIndex(node *const parent, node *left);
static node *insertIntoLeaf(node *const leaf, int key,node * node);
static node *insertIntoLeafAfterSplitting(node *const root, node *const leaf, int key,node *const  node);
static node *insertIntoNode(node *const root, node *const parent, int left_index, int key, node *const right);
static node *insertIntoNodeAfterSplitting(node *const root, node *const parent, int left_index, int key, node *const right);
static node *insertIntoParent(node *const root, node *const left, int key, node *const right);
static node *insertIntoNewRoot(node *const left, int key, node *const right);
static node *startNewTree(int key,node *const node);
static node *insert(node *root, int key);
static void btree_delete_nonone(node *root, int target);
static void btree_shift_to_right_child(node *const root, int pos, node *const y, node *const z);
static void btree_shift_to_left_child(node *const root, int pos,node *const y, node *const z);
bool node_remove(node * node, int key);
static void remove_nonleaf(node *const root,int target);
// Enqueue
static void enqueue(node *new_node) {
	node *c;
	if (queue == NULL) {
		queue = new_node;
		queue->next = NULL;
	} 
	else {
		c = queue;
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = new_node;
		new_node->next = NULL;
	}
}

// Dequeue
static node *dequeue(void) {
	node *n = queue;
	queue = queue->next;
	n->next = NULL;
	return n;
}

// Print the leaves
static void printLeaves(node *const root) {
	if (root == NULL) {
		printf("Empty tree.n");
		return;
	}
	int i;
	node *c = root;
	while (!c->is_leaf)
		c = c->pointers[0];
	while (true) {
		for (i = 0; i < c->num_keys; i++) {
			printf("%d ", c->keys[i]);
		}
		if (c->pointers[order - 1] != NULL) {
			printf(" | ");
			c = c->pointers[order - 1];
		} else
			break;
	}
	printf("\n");
}

// Calculate height
static int height(node *const root) {
	int h = 0;
	node *c = root;
	while (!c->is_leaf) {
		c = c->pointers[0];
		h++;
	}
	return h;
}

// Get path to root
static int pathToLeaves(node *const root, node *const child) {
	int length = 0;
	node *c = child;
	while (c != root) {
		c = c->parent;
		length++;
	}
	return length;
}

// Print the tree
static void printTree(node *const root) {
	node *n = NULL;
	int i = 0;
	int rank = 0;
	int new_rank = 0;

	if (root == NULL) {
		return;
	}
	queue = NULL;
	enqueue(root);
	while (queue != NULL) {
		n = dequeue();
		if (n->parent != NULL && n == n->parent->pointers[0]) {
			new_rank = pathToLeaves(root, n);
			if (new_rank != rank) {
				rank = new_rank;
				printf("\n");
			}
		}
		for (i = 0; i < n->num_keys; i++) {
			printf("%d ", n->keys[i]);
		}
		if (!n->is_leaf)
			for (i = 0; i <= n->num_keys; i++){
				//printf("i= %d <%d>",i,n->num_keys);
				enqueue(n->pointers[i]);
			}
		printf("| ");
	}
	printf("\n");
}

// Find and print the range
static void findAndPrintRange(node *const root, int key_start, int key_end) {
	int i;
	int array_size = key_end - key_start + 1;
	int returned_keys[array_size];
	void *returned_pointers[array_size];
	int num_found = findRange(root, key_start, key_end,returned_keys, returned_pointers);
	if (!num_found)
		printf("range [%d,%d) = []\n",key_start,key_end);
	else {
		printf("range [%d,%d) = [",key_start,key_end);
		for (i = 0; i < num_found-1; i++)
			printf("%d,",returned_keys[i]);
		printf("%d]\n",returned_keys[i]);
	}
}
// Find the range
static int findRange(node *const root, int key_start, int key_end,int returned_keys[], void *returned_pointers[]) {
	int i, num_found = 0;
	node *n = findLeaf1(root, key_start);
	if (n == NULL){
		return 0;
	}
	for (i = 0; i < n->num_keys && n->keys[i] < key_start; i++);
	if(n->keys[0]<key_start){ 
		if (i == n->num_keys){
			if(n->keys[i-1]<=key_start){
				i++;
			}
			else{	
				return 0;
			}
		}
		while (n != NULL) {
    		for (; i < n->num_keys && n->keys[i] < key_end; i++) {
     			returned_keys[num_found] = n->keys[i];
      			returned_pointers[num_found] = n->pointers[i];
      			num_found++;
    		}
    		n = n->pointers[order - 1];
    		i = 0;
  		}
	}
	else{
		int k=0;
		while (n != NULL) {
			for (i=0; i < n->num_keys && n->keys[i] < key_end; i++) {
				returned_keys[num_found] = n->keys[i];
				returned_pointers[num_found] = n->pointers[i];
				num_found++;
			}
			n = n->pointers[order - 1];
		}
	}
	return num_found;
}
// Find the leaf
static node *findLeaf1(node *const root, int key) {
	if (root == NULL) {
    return root;
  }
  int i = 0;
  node *c = root;
  node *temp1 = NULL;
  node *temp2 = NULL;
  while (!c->is_leaf) {
    i = 0;
    while (i < c->num_keys) {
      	if (key > c->keys[i]){
        	i++;
    	}
      	else{
        	break;
        }
    }
    c = (node *)c->pointers[i];
  }
  return c;
}
// Find the leaf
static node *findLeaf(node *const root, int key){
  if (root == NULL) {
    return root;
  }
  int i = 0;
  node *c = root;
  node *temp1 = NULL;
  node *temp2 = NULL;
  while (!c->is_leaf) {
    i = 0;
    while (i < c->num_keys) {
      	if (key >= c->keys[i]){
        	i++;
    	}
      	else{
        	break;
        }
    }
    c = (node *)c->pointers[i];
  }
  return c;
}
static node *find(node *const root, int key, node **const leaf_out) {
	if (root == NULL) {
		if (leaf_out != NULL) {
			*leaf_out = NULL;
		}
		return NULL;
	}
	int i = 0;
	node *leaf = NULL;
	leaf = findLeaf(root, key);
	for (i = 0; i < leaf->num_keys; i++)
		if (leaf->keys[i] == key) break;
	if (leaf_out != NULL) *leaf_out = leaf;
	if (i == leaf->num_keys) return NULL;
	else return (node *)leaf->pointers[i];
}

static int cut(int length) {
	if (length % 2 == 0)
		return length / 2;
	else
		return length / 2 + 1;
}

static node *makeNode(void) {
	node *new_node;
	new_node = malloc(sizeof(node));
	new_node->keys = malloc((order - 1) * sizeof(int));
	new_node->pointers = malloc(order * sizeof(void *));
	new_node->is_leaf = false;
	new_node->num_keys = 0;
	new_node->parent = NULL;
	new_node->next = NULL;
	return new_node;
}

static node *makeLeaf(void) {
	node *leaf = makeNode();
	leaf->is_leaf = true;
	return leaf;
}

static int getLeftIndex(node *const parent, node *const left) {
	int left_index = 0;
	while (left_index <= parent->num_keys && parent->pointers[left_index] != left)
		left_index++;
	return left_index;
}

static node *insertIntoLeaf(node *const leaf, int key, node *const pointer) {
	int i, insertion_point = 0;
	while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)
		insertion_point++;
	for (i = leaf->num_keys; i > insertion_point; i--) {
		leaf->keys[i] = leaf->keys[i - 1];
		leaf->pointers[i] = leaf->pointers[i - 1];
	}
	leaf->keys[insertion_point] = key;
	leaf->pointers[insertion_point] = pointer;
	leaf->num_keys++;
	return leaf;
}

static node *insertIntoLeafAfterSplitting(node *const root, node *const leaf, int key, node *const pointer) {
	node *new_leaf;
	int *temp_keys;
	void **temp_pointers;
	int insertion_index, split, new_key, i, j;
	new_leaf = makeLeaf();
	temp_keys = malloc(order * sizeof(int));
	temp_pointers = malloc(order * sizeof(void *));
	insertion_index = 0;
	while (insertion_index < order - 1 && leaf->keys[insertion_index] < key) insertion_index++;
	for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
		if (j == insertion_index)
			j++;
		temp_keys[j] = leaf->keys[i];
		temp_pointers[j] = leaf->pointers[i];
	}

	temp_keys[insertion_index] = key;
	temp_pointers[insertion_index] = pointer;

	leaf->num_keys = 0;

	split = cut(order - 1);

	for (i = 0; i < split; i++) {
		leaf->pointers[i] = temp_pointers[i];
		leaf->keys[i] = temp_keys[i];
		leaf->num_keys++;
	}
	for (i = split, j = 0; i < order; i++, j++) {
		new_leaf->pointers[j] = temp_pointers[i];
		new_leaf->keys[j] = temp_keys[i];
		new_leaf->num_keys++;
	}

	free(temp_pointers);
	free(temp_keys);

	new_leaf->pointers[order - 1] = leaf->pointers[order - 1];
	leaf->pointers[order - 1] = new_leaf;

	for (i = leaf->num_keys; i < order - 1; i++) leaf->pointers[i] = NULL;
	for (i = new_leaf->num_keys; i < order - 1; i++) new_leaf->pointers[i] = NULL;

	new_leaf->parent = leaf->parent;
	new_key = new_leaf->keys[0];

	return insertIntoParent(root, leaf, new_key, new_leaf);
}

static node *insertIntoNode(node *const root, node *const n,int left_index, int key, node *const right) {
	int i;
	for (i = n->num_keys; i > left_index; i--) {
		n->pointers[i + 1] = n->pointers[i];
		n->keys[i] = n->keys[i - 1];
	}
	n->pointers[left_index + 1] = right;
	n->keys[left_index] = key;
	n->num_keys++;
	return root;
}

static node *insertIntoNodeAfterSplitting(node *const root, node *const old_node, int left_index,int key, node *const right) {
	int i, j, split, k_prime;
	node *new_node, *child;
	int *temp_keys;
	node **temp_pointers;

	temp_pointers = malloc((order + 1) * sizeof(node *));
	temp_keys = malloc(order * sizeof(int));
	for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
		if (j == left_index + 1)
			j++;
		temp_pointers[j] = old_node->pointers[i];
	}

	for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
		if (j == left_index)
			j++;
		temp_keys[j] = old_node->keys[i];
	}

	temp_pointers[left_index + 1] = right;
	temp_keys[left_index] = key;

	split = cut(order);
	new_node = makeNode();
	old_node->num_keys = 0;
	for (i = 0; i < split - 1; i++) {
		old_node->pointers[i] = temp_pointers[i];
		old_node->keys[i] = temp_keys[i];
		old_node->num_keys++;
	}
	old_node->pointers[i] = temp_pointers[i];
	k_prime = temp_keys[split - 1];
	for (++i, j = 0; i < order; i++, j++) {
		new_node->pointers[j] = temp_pointers[i];
		new_node->keys[j] = temp_keys[i];
		new_node->num_keys++;
	}
	new_node->pointers[j] = temp_pointers[i];
	free(temp_pointers);
	free(temp_keys);
	new_node->parent = old_node->parent;
	for (i = 0; i <= new_node->num_keys; i++) {
		child = new_node->pointers[i];
		child->parent = new_node;
	}
	return insertIntoParent(root, old_node, k_prime, new_node);
}

static node *insertIntoParent(node *const root, node *const left, int key, node *const right) {
	int left_index;
	node *parent;
	parent = left->parent;
	if (parent == NULL)
		return insertIntoNewRoot(left, key, right);

	left_index = getLeftIndex(parent, left);	
	if (parent->num_keys < order - 1)
		return insertIntoNode(root, parent, left_index, key, right);
		
	return insertIntoNodeAfterSplitting(root, parent, left_index, key, right);
}

static node *insertIntoNewRoot(node *const left, int key,node *const right) {
	node *root = makeNode();
	root->keys[0] = key;
	root->pointers[0] = left;
	root->pointers[1] = right;
	root->num_keys++;
	root->parent = NULL;
	left->parent = root;
	right->parent = root;
	return root;
}

static node *startNewTree(int key, node *const pointer) {
	node *root = makeLeaf();
	root->keys[0] = key;
	root->pointers[0] = pointer;
	root->pointers[order - 1] = NULL;
	root->parent = NULL;
	root->num_keys++;
	return root;
}

static node *insert(node *const root, int key) {
	node *leaf = NULL;
	if (root == NULL)
		return startNewTree(key,NULL);
	leaf = findLeaf(root, key);
	if (leaf->num_keys < order - 1) {
		leaf = insertIntoLeaf(leaf, key,NULL);
		return root;
	}
	return insertIntoLeafAfterSplitting(root, leaf, key,NULL);
}
static void btree_merge_child(node *const root, int pos, node *const y, node *const z){
	int i,j;
	if(true == y->is_leaf) {
		y->num_keys = 2 * DEGREE - 2;
		for(i = DEGREE; i < 2 * DEGREE - 1; i++) {
			y->keys[i-1] = z->keys[i-DEGREE];
		}
	} 
	else {
		y->num_keys= 2 * DEGREE - 1;
		for(i = DEGREE; i < 2 * DEGREE - 1; i++) {
			y->keys[i] = z->keys[i-DEGREE];
		}
		y->keys[DEGREE-1] = root->keys[pos];
		for(i = DEGREE; i < 2 * DEGREE; i++) {
			y->pointers[i] = z->pointers[i-DEGREE];
		}
	}

	for(j = pos + 1; j < root->num_keys; j++) {
		root->keys[j-1] = root->keys[j];
		root->pointers[j] = root->pointers[j+1];
	}

	root->num_keys -= 1;

	// update link
	if(true == y->is_leaf) {
		y->next = z->next;
	}

	free(z);
}
static node* delete_(int target, node *const root){
	if(1 == root->num_keys) {
		node *y = root->pointers[0];
		node *z = root->pointers[1];
		if(NULL != y && NULL != z &&  DEGREE - 1 == y->num_keys && DEGREE - 1 == z->num_keys) {
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			node_remove(root,target); 
			return y;
		} 
		else {
			btree_delete_nonone(root, target);
			node_remove(root,target);
			return root;
		}
	} 
	else {
		btree_delete_nonone(root, target);
		node_remove(root,target);	
		return root;
	}
	
}
bool node_remove(node *const root, int key){
	int i;
	if (root == NULL)
		return false;

	int index;
	for (index = 0; index < root->num_keys && root->keys[index] < key; index++);

	if (index < root->num_keys && root->keys[index] == key){
		if (root->is_leaf)	{
			for (i = index + 1; i < root->num_keys; i++)
				root->keys[i - 1] = root->keys[i];
			root->num_keys--;
		}
		else
			remove_nonleaf(root, index);
	}
	else if (!root->is_leaf){
		bool flag = (index == root->num_keys) ? true : false;
		node* x = root->pointers[index-1];
		node* y = root->pointers[index];
		node* z = root->pointers[index+1];
		if (y->num_keys < DEGREE){
			if (index != 0 && x->num_keys >= DEGREE)
				borrow_prev(root, index);
			else if (index != root->num_keys && z->num_keys >= DEGREE)
				borrow_next(root, index);
			else{
				if (index != root->num_keys)
					merge(root, index);
				else
					merge(root, index - 1);
			}
		}

		if (flag && index > root->num_keys)
			return node_remove(root->pointers[index - 1], key);
		else
			return node_remove(root->pointers[index], key);
	}
	else
		return false;

	return true;
}
static void remove_nonleaf(node *const root,int index){
	int k = root->keys[index];
	if(index>0)
	node * x = root->pointers[index-1];
	node * y = root->pointers[index];
	if(index<root->num_leys)
	node * z = root->pointers[index+1];
	if (y->num_keys >= DEGREE){
		node_t temp = root->pointers[index];

		while (!temp->leaf)
			temp = temp->pointers[temp->num_keys];

		root->keys[index] = temp->keys[temp->num_keys - 1];
		root_remove(root->pointers[index], temp->keys[temp->num_keys - 1]);
	}

	else if (z->num_keys >= DEGREE){
		node_t temp = root->pointers[index + 1];

		while (!temp->leaf)
			temp = temp->pointers[0];

		root->keys[index] = temp->keys[0];
		node_remove(root->pointers[index + 1], temp->keys[0]);
	}

	else{
		merge(root, index);
		node_remove(root->pointers[index], k);
	}
}
void merge(node *const node, int index){
	node * child = node->childs[index];
	node * sibling = node->childs[index + 1];
	int i;
	child->keys[DEGREE - 1] = node->keys[index];

	for (i = 0; i < sibling->n; i++)
		child->keys[i + DEGREE] = sibling->keys[i];

	if (!child->leaf)
		for (i = 0; i <= sibling->n; i++)
			child->childs[i + DEGREE] = sibling->childs[i];

	for (i = index + 1; i < node->num_keys; i++)
		node->keys[i - 1] = node->keys[i];

	for (i = index + 2; i <= node->num_keys; i++)
		node->childs[i - 1] = node->childs[i];

	child->num_keys += sibling->num_keys + 1;
	node->num_keys--;

	free(sibling);
}

static void btree_delete_nonone(node *const root, int target){
	node* goal = NULL;
	if(true == root->is_leaf){
		int i = 0,j;
		while(i < root->num_keys && target > root->keys[i]) i++;
		if(target == root->keys[i]) {
			for(j = i + 1; j < 2 * DEGREE - 1; j++) {
				root->keys[j-1] = root->keys[j];
			}
			root->num_keys -= 1;	
		} 
	} 
	else {
		int i = 0;
		node *y = NULL, *z = NULL;
		while(i < root->num_keys && target > root->keys[i]) i++;
		
		y = root->pointers[i];
		if(i < root->num_keys){
			z = root->pointers[i+1];
		}
		node *p = NULL;
		if(i > 0){
			p = root->pointers[i-1]; //p一定是放root的第二個child的第一個值 
		}

		if(y->num_keys == DEGREE - 1) {
			if(i > 0 && p->num_keys > DEGREE - 1){
				btree_shift_to_right_child(root, i-1, p, y);
			}
			else if(i < root->num_keys && z->num_keys > DEGREE - 1) {
				btree_shift_to_left_child(root, i, y, z);
			} 
			else if(i > 0) {
				btree_merge_child(root, i-1, p, y);
				y = p;
			} 
			else {
				btree_merge_child(root, i, y, z);
			}
			btree_delete_nonone(y, target);
			node_remove(root,taget);
		} 
		else {
			btree_delete_nonone(y, target);
			node_remove(root,taget);
		}
	}
}
static void btree_shift_to_right_child(node *const root, int pos, node *const y, node *const z){
	int i;
	z->num_keys += 1;
	if(false == z->is_leaf) {
		z->keys[0] = root->keys[pos];
		root->keys[pos] = y->keys[y->num_keys-1];
	} 
	else {
		z->keys[0] = y->keys[y->num_keys-1];
		root->keys[pos] = y->keys[y->num_keys-2];
	}
	for(i = z->num_keys -1; i > 0; i--) {
		z->keys[i] = z->keys[i-1];
	}

	if(false == z->is_leaf) {
		for(i = z->num_keys; i > 0; i--) {
			z->pointers[i] = z->pointers[i-1];
		}
		z->pointers[0] = y->pointers[y->num_keys];
	} 

	y->num_keys -= 1;
}
static void btree_shift_to_left_child(node *const root, int pos,node *const y, node *const z){
	int j;
	y->num_keys += 1;
	if(false == z->is_leaf) {
		y->keys[y->num_keys-1] = root->keys[pos];
		root->keys[pos] = z->keys[0];
	} 
	else {
		y->keys[y->num_keys-1] = z->keys[0];
		root->keys[pos] = z->keys[0];
	}

	for(j = 1; j < z->num_keys; j++) {
		z->keys[j-1] = z->keys[j];
	}

	if(false == z->is_leaf) {
		y->pointers[y->num_keys] = z->pointers[0];
		for(j = 1; j <= z->num_keys; j++) {
			z->pointers[j-1] = z->pointers[j];
		}
	} 

	z->num_keys -= 1;
}
int main() {
	node *root = NULL;
	char s[50];
	long long int line;
	int num,start,end;
	scanf("%d",&line);
	int i;
	for(i=0;i<line;i++){
		scanf("%s",s);
		if(strcmp(s,"add")==0){
			scanf("%d",&num);
			root = insert(root,num);
		}
		else if(strcmp(s,"range-search")==0){
			scanf("%d",&start);
			scanf("%d",&end);
			findAndPrintRange(root, start, end);
		}	
		else if(strcmp(s,"remove")==0){
			scanf("%d",&num);
			if(root!=NULL)
			root = delete_(num,root);
		}
		//printf("*************************************************\n");
		printTree(root);
		//printf("*************************************************\n");
	}
}
