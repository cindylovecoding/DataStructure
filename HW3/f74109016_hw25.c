//f74109016_hw25_OK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DEGREE 3
#define ORDER (DEGREE * 2)
typedef struct node* node_t;
struct node{
	int keys[ORDER - 1];
	node_t childs[ORDER];
	int n;
	bool leaf;
};

node_t node_new(bool);
void tree_delete(node_t);
node_t search(node_t, int);
int search_index(node_t, int, int*);

void node_insert(int);
void insert_nonfull(node_t, int);
void split_child(node_t, int, node_t);

bool node_remove(node_t, int);
void remove_nonleaf(node_t, int);
void merge(node_t, int);
void borrow_prev(node_t, int);
void borrow_next(node_t, int);


node_t root = NULL;
node_t node_new(bool leaf){
	node_t node = malloc(sizeof(struct node));
	int i;
	for(i = 0; i < ORDER; i++)
		node->childs[i] = NULL;
	node->n = 0;
	node->leaf = leaf;

	return node;
}

void tree_delete(node_t node){
	int i;
	if (node == NULL)
		return;

	if(!node->leaf)
		for (i = 0; i <= node->n; i++)
			tree_delete(node->childs[i]);

	free(node);
}

node_t search(node_t node, int key){
	int i;
	for (i = 0; i < node->n && node->keys[i] < key; i++);

	if (node->keys[i] == key)
		return node;

	if (node->leaf)
		return NULL;

	return search(node->childs[i], key);
}

int search_index(node_t node, int index, int* count){
	if (!node->leaf){
		int temp = search_index(node->childs[0], index, count);
		if (*count == -1)
			return temp;
		int i;
		for (i = 0; i < node->n; i++){
			if (index == *count){
				*count = -1;
				return node->keys[i];
			}
			(*count)++;
			int temp = search_index(node->childs[i + 1], index, count);
			if (*count == -1)
				return temp;
		}
	}
	else{
		if (node->n > index - *count){
			index -= *count;
			*count = -1;
			return node->keys[index];
		}
		else
			*count += node->n;
	}
	return 0;
}

void node_insert(int key){
	if (root == NULL){
		root = node_new(true);
		root->keys[0] = key;
		root->n = 1;
		return;
	}
	if (root->n == ORDER - 1){
		node_t node = node_new(false);
		node->childs[0] = root;

		split_child(node, 0, root);

		int i = 0;
		if (node->keys[0] < key)
			i++;
		insert_nonfull(node->childs[i], key);

		root = node;
	}
	else
		insert_nonfull(root, key);
}

void insert_nonfull(node_t node, int key){
	int i;
	if (node->leaf)	{
		for (i = node->n - 1; i >= 0 && node->keys[i] > key; i--)
			node->keys[i + 1] = node->keys[i];

		node->keys[i + 1] = key;
		node->n++;
	}
	else{
		for (i = node->n - 1; i >= 0 && node->keys[i] > key; i--);

		if (node->childs[i + 1]->n == ORDER - 1){
			split_child(node, i + 1, node->childs[i + 1]);
			if (node->keys[i + 1] < key)
				i++;
		}
		insert_nonfull(node->childs[i + 1], key);
	}
}

void split_child(node_t parent, int i, node_t child){
	node_t node = node_new(child->leaf);
	node->n = DEGREE - 1;
	int j;
	for (j = 0; j < DEGREE - 1; j++)
		node->keys[j] = child->keys[j + DEGREE];

	if(!child->leaf)
		for (j = 0; j < DEGREE; j++)
			node->childs[j] = child->childs[j + DEGREE];

	child->n = DEGREE - 1;

	for (j = parent->n; j >= i + 1; j--)
		parent->childs[j + 1] = parent->childs[j];

	parent->childs[i + 1] = node;

	for (j = parent->n - 1; j >= i; j--)
		parent->keys[j + 1] = parent->keys[j];

	parent->keys[i] = child->keys[DEGREE - 1];

	parent->n++;
}

bool node_remove(node_t node, int key){
	int i;
	if (node == NULL)
		return false;

	int index;
	for (index = 0; index < node->n && node->keys[index] < key; index++);

	if (index < node->n && node->keys[index] == key){
		if (node->leaf)	{
			for (i = index + 1; i < node->n; i++)
				node->keys[i - 1] = node->keys[i];
			node->n--;
		}
		else
			remove_nonleaf(node, index);
	}
	else if (!node->leaf){
		bool flag = (index == node->n) ? true : false;

		if (node->childs[index]->n < DEGREE){
			if (index != 0 && node->childs[index - 1]->n >= DEGREE)
				borrow_prev(node, index);
			else if (index != node->n && node->childs[index + 1]->n >= DEGREE)
				borrow_next(node, index);
			else{
				if (index != node->n)
					merge(node, index);
				else
					merge(node, index - 1);
			}
		}

		if (flag && index > node->n)
			return node_remove(node->childs[index - 1], key);
		else
			return node_remove(node->childs[index], key);
	}
	else
		return false;

	return true;
}

void remove_nonleaf(node_t node, int index){
	int k = node->keys[index];

	if (node->childs[index]->n >= DEGREE){
		node_t temp = node->childs[index];

		while (!temp->leaf)
			temp = temp->childs[temp->n];

		node->keys[index] = temp->keys[temp->n - 1];
		node_remove(node->childs[index], temp->keys[temp->n - 1]);
	}

	else if (node->childs[index + 1]->n >= DEGREE){
		node_t temp = node->childs[index + 1];

		while (!temp->leaf)
			temp = temp->childs[0];

		node->keys[index] = temp->keys[0];
		node_remove(node->childs[index + 1], temp->keys[0]);
	}

	else{
		merge(node, index);
		node_remove(node->childs[index], k);
	}
}

void merge(node_t node, int index){
	node_t child = node->childs[index];
	node_t sibling = node->childs[index + 1];
	int i;
	child->keys[DEGREE - 1] = node->keys[index];

	for (i = 0; i < sibling->n; i++)
		child->keys[i + DEGREE] = sibling->keys[i];

	if (!child->leaf)
		for (i = 0; i <= sibling->n; i++)
			child->childs[i + DEGREE] = sibling->childs[i];

	for (i = index + 1; i < node->n; i++)
		node->keys[i - 1] = node->keys[i];

	for (i = index + 2; i <= node->n; i++)
		node->childs[i - 1] = node->childs[i];

	child->n += sibling->n + 1;
	node->n--;

	free(sibling);
}

void borrow_prev(node_t node, int index){
	node_t child = node->childs[index];
	node_t sibling = node->childs[index - 1];
	int i;
	for (i = child->n - 1; i >= 0; i--)
		child->keys[i + 1] = child->keys[i];

	if (!child->leaf)
		for (i = child->n; i >= 0; i--)
			child->childs[i + 1] = child->childs[i];

	child->keys[0] = node->keys[index - 1];

	if (!child->leaf)
		child->childs[0] = sibling->childs[sibling->n];

	node->keys[index - 1] = sibling->keys[sibling->n - 1];

	child->n++;
	sibling->n--;
}

void borrow_next(node_t node, int index){
	node_t child = node->childs[index];
	node_t sibling = node->childs[index + 1];
	int i;
	child->keys[child->n] = node->keys[index];

	if (!child->leaf)
		child->childs[child->n + 1] = sibling->childs[0];

	node->keys[index] = sibling->keys[0];

	for (i = 1; i < sibling->n; i++)
		sibling->keys[i - 1] = sibling->keys[i];

	if (!sibling->leaf)
		for (i = 1; i <= sibling->n; i++)
			sibling->childs[i - 1] = sibling->childs[i];

	child->n++;
	sibling->n--;
}
int main(){
	char s[8];
	int n, x,i;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		scanf("%s", s);
		scanf("%d", &x);
		if (strcmp(s, "add") == 0){
			node_insert(x);
			printf("add(%d) = ok\n", x);
		}
		else if (strcmp(s, "get") == 0){
			node_t temp = search(root, x);
			if (temp == NULL)
				printf("get(%d) = not found\n", x);
			else
				printf("get(%d) = %d\n", x, x);
		}
		else if (strcmp(s, "getk") == 0){
			if (x <= 0)
				printf("getk(%d) = not found\n", x);
			else{
				int count = 1;
				int* count_ptr = &count;
				int key = search_index(root, x, count_ptr);
				if(*count_ptr == -1)
					printf("getk(%d) = %d\n", x, key);
				else
					printf("getk(%d) = not found\n", x);
			}

		}
		else if (strcmp(s, "remove") == 0){
			if(node_remove(root, x))
				printf("remove(%d) = %d\n", x, x);
			else
				printf("remove(%d) = not found\n", x);
		}
		else if (strcmp(s, "removek") == 0){
			if (x <= 0)
				printf("removek(%d) = not found\n", x);
			else{
				int count = 1;
				int* count_ptr = &count;
				int key = search_index(root, x, count_ptr);
				if (*count_ptr == -1 && node_remove(root, key))
					printf("removek(%d) = %d\n", x, key);
				else
					printf("removek(%d) = not found\n", x);
			}
		}
		else{
			printf("Wrong Instruction\n");
		}
	}
	tree_delete(root);
	return 0;
}
