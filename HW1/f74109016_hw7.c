//F74109016 葉惟欣 finished in 2021/10/17 Homework7 
//輸出最後不是.2f 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
   int coef;
   int expon;				  
   struct node *link;		  
};
typedef struct node NODE;	  
NODE *createList(int *arr, int len)
{
   int i;
   NODE *first,*current,*previous;
   for(i=1;i<=len;i+=2)    
   {
      current=(NODE *) malloc(sizeof(NODE));
      current->coef=arr[i];	  
      current->expon=arr[i+1];
      if(i==1)				  
         first=current;
      else
         previous->link=current;  
      current->link=NULL;		  
      previous=current;   		  
   }
   return first;
}
void insertNode(NODE *node,int coefficient,int exponation){
	NODE * newnode = (NODE *)malloc(sizeof(NODE));
	newnode ->coef = coefficient;
	newnode ->expon = exponation;
	newnode ->link = node->link;
	node -> link = newnode;
}
NODE* searchNode(NODE * first,int exponation){
	NODE * node =first;
	while(node!=NULL){
		if(node->expon == exponation){
			return node;
		}
		else{
			node = node->link;
		}
	}
	return NULL;
}
void pwrite(NODE * first){
	NODE * node =first;
	if(first == NULL){
		printf("List is empty!\n");
	}
	else{
		while(node!=NULL){
			if(node->link!=NULL&&(node->link)->coef>0){
				printf("%dx^%d+",node->coef,node->expon);
			}
			else{
				printf("%dx^%d",node->coef,node->expon);
			}
			node = node->link;
		}
		printf("\n");
	}
}
NODE* padd(NODE* first,NODE* second){
	printf("added\n");
	NODE *result = NULL,*prev = NULL;
	NODE *current_n1 = first;
	NODE *current_n2 = second;
	while(current_n1 != NULL||current_n2 != NULL){
		NODE *ptr = (NODE *)malloc(sizeof(NODE));
		ptr->link = NULL;
		if(current_n1->expon>current_n2->expon){
			ptr ->coef = current_n1->coef;
			ptr ->expon = current_n1->expon; 
			current_n1 = current_n1->link;
		}
		else if(current_n1->expon<current_n2->expon){
			ptr ->coef = current_n2->coef;
			ptr ->expon = current_n2->expon; 
			current_n2 = current_n2->link;
		}
		else{
			ptr->coef = current_n1->coef + current_n2->coef;
			ptr->expon = current_n1->expon;
			current_n1 = current_n1->link;
			current_n2 = current_n2->link;
		}
		if(ptr ->coef !=0){
			if(result == NULL) result = ptr;
			else{
				prev->link = ptr;
			}
			prev = ptr;
		} 
	}
	return result;
}
NODE* psubstracted(NODE* first,NODE* second){
	printf("substracted\n");
	NODE *result = NULL,*prev = NULL;
	NODE *current_n1 = first;
	NODE *current_n2 = second;
	while(current_n1 != NULL||current_n2 != NULL){
		NODE *ptr = (NODE *)malloc(sizeof(NODE));
		ptr->link = NULL;
		if(current_n1->expon>current_n2->expon){
			ptr ->coef = current_n1->coef;
			ptr ->expon = current_n1->expon; 
			current_n1 = current_n1->link;
		}
		else if(current_n1->expon<current_n2->expon){
			ptr ->coef = current_n2->coef;
			ptr ->expon = current_n2->expon; 
			current_n2 = current_n2->link;
		}
		else{
			ptr->coef = current_n1->coef - current_n2->coef;
			ptr->expon = current_n1->expon;
			current_n1 = current_n1->link;
			current_n2 = current_n2->link;
		}
		if(ptr ->coef !=0){
			if(result == NULL) result = ptr;
			else{
				prev->link = ptr;
			}
			prev = ptr;
		} 
	}
	return result;
}
NODE* pmultiplied(NODE* first,NODE* second){
	printf("multiplied\n");
	NODE *result = NULL,*prev = NULL;
	NODE *current_n1 = first;
	NODE *current_n2 = second;
	while(current_n1){
		current_n2 = second;
		while(current_n2){
			NODE *ptr = (NODE *)malloc(sizeof(NODE));
			ptr->link = NULL;
			ptr->coef = current_n1->coef*current_n2->coef;
			ptr->expon = current_n1->expon+current_n2->expon; 
			if(ptr ->coef !=0){
				if(result == NULL){                                    
					result = ptr;
					prev = ptr;
				}                     
				else{                                                  
					NODE * temp =searchNode(result,ptr->expon);
					if(temp!=NULL){             
						temp->coef = temp->coef+ptr->coef;
					} 
					else{                                                 
						prev->link = ptr;
						prev = ptr;
					}
				}
			}
			current_n2 = current_n2->link;
		}
		current_n1 = current_n1->link;
	}
	return result;
}
void perase(NODE * beerased){
	NODE * temp;
	while(beerased!= NULL){
		temp = beerased;
		beerased = beerased->link;
		free(temp);
	}
	printf("erased\n");
}
float calculate(NODE * expression,float x){
	int i;
	float sum = 0,temp;
	NODE * current = expression;
	while(current != NULL){
		temp=1;
		for(i=0;i<current->expon;i++){
			temp *= x;
		}
		sum += current->coef *temp;
		current = current->link;
	}
	return sum;
}
int main(){
	NODE *first,*node,*second;
	NODE *result = (NODE *)malloc(sizeof(NODE));
	int len,i,j;
	float x;
	char string [50];
	int arr1[5];
	int arr2[5];
	int arr3[5];
	scanf("%d",&len);
	for(i =0 ;i<len;i++){
		scanf("%s",string);
		if(strcmp(string,"pread")==0){
			scanf("%s",string);
			if(strcmp(string,"expressionA")==0){
				for(j=0;j<5;j++){
					scanf("%d",&arr1[j]);
				}
				first = createList(arr1,arr1[0]*2);
			}
			else if(strcmp(string,"expressionB")==0){
				for(j=0;j<5;j++){
					scanf("%d",&arr2[j]);
				}
				second = createList(arr2,arr2[0]*2);
			}
			printf("ok\n");
		}
		else if(strcmp(string,"pwrite")==0){
			scanf("%s",string);
			if(strcmp(string,"expressionA")==0){
				pwrite(first);
			}
			else if(strcmp(string,"expressionB")==0){
				pwrite(second);
			}
			else if(strcmp(string,"resultC")==0){
				pwrite(result);
			}
		}
		else if(strcmp(string,"padd")==0){
			scanf("%s",string);
			if(strcmp(string,"resultC")==0){
				scanf("%s",string);
				if(strcmp(string,"expressionA")==0){
					scanf("%s",string);
					if(strcmp(string,"expressionB")==0){
						result = padd(first,second);
					}
				}
			}
		}
		else if(strcmp(string,"perase")==0){
			scanf("%s",string);
			if(strcmp(string,"resultC")==0){
				perase(result);
			}
		}
		else if(strcmp(string,"pmult")==0){
			scanf("%s",string);
			if(strcmp(string,"resultC")==0){
				scanf("%s",string);
				if(strcmp(string,"expressionA")==0){
					scanf("%s",string);
					if(strcmp(string,"expressionB")==0){
						result =pmultiplied(first,second);
					}
				}
			}
		}
		else if(strcmp(string,"eval")==0){
			scanf("%s",string);
			scanf("%f",&x);
			if(strcmp(string,"resultC")==0){
				float answer = calculate(result,x);
				printf("%.2f",answer);
			}
			else if(strcmp(string,"expressionA")==0){
				float answer = calculate(first,x);
				printf("%.2f",answer);
			}
			else if(strcmp(string,"expressionB")==0){
				float answer = calculate(second,x);
				printf("%.2f",answer);
			}
		}
		else if(strcmp(string,"psub")==0){
			scanf("%s",string);
			if(strcmp(string,"resultC")==0){
				scanf("%s",string);
				if(strcmp(string,"expressionA")==0){
					scanf("%s",string);
					if(strcmp(string,"expressionB")==0){
						result =psubstracted(first,second);
					}
				}
			}
		}
	}	
}
