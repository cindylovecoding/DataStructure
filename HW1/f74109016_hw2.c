//F74109016 葉惟欣 finished in 2021/10/18 Homework#2 
#include<stdio.h>
#include<stdlib.h>
int counter =1;
void Hanoi(int,int,int,int);
int main(){
	int n;
	scanf("%d",&n);
	Hanoi(n,1,2,3); //最上面數字越大 
} 
void Hanoi(int disk_num,int movefrom,int temp,int moveto){
	if(disk_num>0){ 
		Hanoi(disk_num-1,movefrom,moveto,temp);
		printf("%d%2d%2d\n",disk_num,movefrom,moveto);
		Hanoi(disk_num-1,temp,movefrom,moveto);
	}
}
