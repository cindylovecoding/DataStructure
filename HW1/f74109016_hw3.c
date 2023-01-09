//F74109016 ¸­±©ªY finished in 2021/10/18 Homework#3 
#include<stdio.h>
typedef struct{
    int row;
    int col;
    int val;
}term;
void fastTranspose(term a[],term b[]){
    int nonZeroRow[a[0].col],startingPos[a[0].col];
    int i;
	for(i=0;i<a[0].col;i++){
		nonZeroRow[i] = 0;
		startingPos[i] = 0;
	}
    b[0].col = a[0].row;
    b[0].row = a[0].col;
    b[0].val = a[0].val;
    for(i=1;i<=a[0].val;i++){
        nonZeroRow[a[i].col]++;
    }
    startingPos[0] = 1;
    for(i=1;i<=a[0].col;i++){
        startingPos[i] = startingPos[i-1]+nonZeroRow[i-1];
    }
    for(i=1;i<=a[0].val;i++){
        int j= startingPos[a[i].col];
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].val = a[i].val;
        startingPos[a[i].col]++;
    }
}
int main(){
	int row,col,num;
	scanf("%3d %3d %3d ",&row,&col,&num);
	int i;
	term a[num+1];
	a[0].row = row;
	a[0].col = col;
	a[0].val = num;
	for(i=1;i<a[0].val+1;i++){
		scanf("%3d %3d %3d",&a[i].row,&a[i].col,&a[i].val);
	}
	printf("\n");
    term b[num+1];
    fastTranspose(a,b);
    printf("%d %d %d\n",b[0].row,b[0].col,b[0].val);
    for(i=1;i<a[0].val+1;i++){
        printf("%-2d%-2d%-3d\n",b[i].row,b[i].col,b[i].val);
    }
}



