//F74109016 ¸­±©ªY finished in 2021/10/20 Homework#5 
#include<stdio.h>
#include<stdlib.h>
typedef int bool;  
enum { false, true }; 
struct position{
	int row;
	int col;
	struct  position* link;
	struct position* back;
};
typedef struct position POSITION;	
int high,width;


void print(POSITION * path){
	while(path!=NULL){
		printf("%d %d\n",path->row-1,path->col-1);
		path = path->link;
	}

}
int main(){
	int i=0,j=0;
	scanf("%d %d",&high,&width);
	int map[high+2][width+2];
	char string;
	for(i=0;i<high;i++){
		for(j=0;j<width*2;j++){
			scanf("%c",&string);
			if(string!=' '){
				map[i+1][j/2+1]= (int)string-48;
			}
		}
	}
	for(i=0;i<high+2;i++){
		for(j=0;j<width+2;j++){
			if(i==0||i==high+1||j==0||j==width+1){
				map[i][j] = 1;
			}
		}
	}
	int next_row [] = {-1,-1,0,1,1, 1, 0,-1 };
	int next_col [] = { 0, 1,1,1,0,-1,-1,-1 };
	POSITION *start = (POSITION *)malloc(sizeof(POSITION));
	POSITION *current = (POSITION *)malloc(sizeof(POSITION));
	start->row = 1;
	start->col = 1;
	current = start;
	bool move = false;
	bool sol = true;
	while(!((current->row==high)&&(current->col==width))&&sol == true){
		move = false;
		POSITION *new_node = (POSITION *)malloc(sizeof(POSITION));
		new_node->link = NULL;
		for(i=0;i<8;i++){
			if(map[current->row+next_row[i]][current->col+next_col[i]]==0){
				map[current->row+next_row[i]][current->col+next_col[i]]= 2;
				new_node->row = current->row+next_row[i];
				new_node->col = current->col+next_col[i];
				new_node->back = current;
				current->link = new_node;
				current = new_node;
				move = true;
				break;
			}
		}
		if(current->row==high&&current->col==width){
			break;
		}
		if(move == false){
			map[current->row][current->col]=1;
			if(current != start){
				current = current->back;
			}
			else{
				sol = false;
				break;
			}
		}
		
	}
	if(sol == true){
		printf("\n");
		print(start);
	}
	else{
		printf("no answer");
	}
} 	


