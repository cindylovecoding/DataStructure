//F74109016 ¸­±©ªY finished in 2021/10/18 Homework#4 
#include<stdio.h>
#include<string.h>
typedef int bool;  
enum { false, true };  
void find_path(int,int,int []);
int main(){
	srand(time(NULL));
	int position[2];
	char problem [20];
	do{
		scanf("%s",problem);
		int row,col,little_problem;
		if(strcmp(problem ,"a")==0){
			scanf("%d %d",&row,&col);
			position[0] = rand()%row;
			position[1] = rand()%col;
			find_path(row,col,position);
		}
		else if(strcmp(problem ,"b")==0){
			scanf("%d",&little_problem);
			if(little_problem == 1){
				row = 15;
				col = 15;
				position[0] = 10;
				position[1] = 10;
			}
			else if(little_problem == 2){
				row = 39;
				col = 19;
				position[0] = 1;
				position[1] = 1;
			}
			find_path(row,col,position);
		}
	}while(strcmp(problem ,"q")!=0);
} 
void find_path(int row,int col,int position[2]){
	int imove [] ={-1,0,1,1,1,0,-1,-1};
	int jmove [] ={1,1,1,-1,0,-1,-1,0};
	int room [row+2][col+2];
	int i,j;
	srand(time());
	for(i=0;i<row+2;i++){
		for(j=0;j<col+2;j++){
			room[i][j] = 0;
		}
	}
	position[0]++;
	position[1]++;
	room[position[0]][position[1]]+=1;
	bool full = true;
	int counter =1 ;
	int randnum,row_test,col_test;
	do{
		full = true;
		do{
			randnum = rand()%8; 
			row_test = position[0]+imove[randnum];
			col_test = position[1]+jmove[randnum];
		}while((0==row_test)||(row+1==row_test)||(0==col_test)||(col+1==col_test));
		position[0] = position[0]+imove[randnum];
		position[1] = position[1]+jmove[randnum];
		counter++;
		if(counter==50000){
			full = true;
			break;
		}
		room[position[0]][position[1]]++; 
		for(i=1;i<row+1;i++){
			for(j=1;j<col+1;j++){
				if(room[i][j]==0){
					full = false;
				}
			}
		}
	}while(full == false);
	printf("%d\n",counter);
	for(i=1;i<row+1;i++){
		for(j=1;j<col+1;j++){
			printf("%4d ",room[i][j]);
		}
		printf("\n");
	}
}
