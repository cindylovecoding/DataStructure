//f74109016_hw23
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
typedef int bool;  
enum { false, true };
static int array[50];
static int next_index = 1;
static int current; 

static void insert(int x){
	int current,done,gp,lchild_of_gp,rchild_of_gp;
	current = ++next_index;
	if(current % 2 == 1 && x<array[current-1]){
		array[current] = array [current - 1];
		current--;
	}
	done = false;
	while(!done && current >=4){
		gp = current /4;
		lchild_of_gp = 2 * gp;
		rchild_of_gp = lchild_of_gp +1;
		if(x<array[lchild_of_gp]){
			array[current] = array[lchild_of_gp];
			current = lchild_of_gp;
		}
		else if(x>array[rchild_of_gp]){
			array[current] = array[rchild_of_gp];
			current = rchild_of_gp;
		}
		else{
			done = true;
		}
	}
	array[current] = x;
}
static void delete_min(int min_delete){
	int lchild = min_delete*2;
	int si_lchild = (min_delete+1)*2;
	int change;
	bool exist = false;
	if(si_lchild<=next_index){
		if(array[lchild] < array[si_lchild]){
			change = lchild;
		}
		else{
			change = si_lchild;
		}
		exist = true;
	}
	else if(lchild <= next_index){
		change = lchild;
		exist = true;
	}
	else{
		if(array[min_delete]>array[min_delete+1]){
			int temp = array[min_delete];
			array[min_delete] = array[min_delete+1];
			array[min_delete+1] = temp;
		}
	}
	if(exist == true && array[change] < array[min_delete]){
		int temp = array[min_delete];
		array[min_delete] = array[change];
		array[change] = temp;
		delete_min(change);
	}
	if(exist == false&&min_delete+1<=next_index){
		if(array[min_delete]>array[min_delete+1]){
			int temp = array[min_delete];
			array[min_delete] = array[min_delete+1];
			array[min_delete+1] = temp;
		}
	}
	
}
static void delete_max(int max_delete){
	int rchild = max_delete*2+1;
	int si_rchild = (max_delete-1)*2+1;
	int change;
	bool exist = false;
	if(si_rchild<=next_index){
		if(array[rchild] > array[si_rchild]){
			change = rchild;
		}
		else{
			change = si_rchild;
		}
		exist = true;
	}
	else if(rchild <= next_index){
		change = rchild;
		exist = true;
	}
	else{
		if(array[max_delete]<array[max_delete-1]){
			int temp = array[max_delete];
			array[max_delete] = array[max_delete-1];
			array[max_delete-1] = temp;
		}
	}
	if(exist == true && array[change] > array[max_delete]){
		int temp = array[max_delete];
		array[max_delete] = array[change];
		array[change] = temp;
		delete_max(change);
	}
	if(exist == false){
		if(array[max_delete]<array[max_delete-1]){
			int temp = array[max_delete];
			array[max_delete] = array[max_delete-1];
			array[max_delete-1] = temp;
		}
	}
	
}
static void show(){
	int i;
	int k=3;
	printf("NULL\n");
	for(i=0;i<next_index-1;i++){
		if(i+2!=k && i!=next_index-2){
			printf("%d ",array[i+2]);
		}
		else if(i+2!=k && i==next_index-2){
			printf("%d\n",array[i+2]);
		}
		if(i+2==k){
			k = k*2+1;
			printf("%d\n",array[i+2]);
		}
	}
}
int main() {
    int val;
    char ch[50];
    do{
    	scanf("%s",ch);
    	if(strcmp(ch,"insert")==0){
            scanf("%d",&val);
            insert(val);
        }
        else if(strcmp(ch,"delete")==0){
        	scanf("%s",ch);
        	if(strcmp(ch,"min")==0){
            	array[2] = array[next_index];
            	delete_min(2);
            	next_index--;
            } 
            if(strcmp(ch,"max")==0){
            	array[3] = array[next_index];
            	delete_max(3);
            	next_index--;
			}
    	}
        else if(strcmp(ch,"show")==0){
        	show();
		}
    }while(strcmp(ch,"quit")!=0);
}
