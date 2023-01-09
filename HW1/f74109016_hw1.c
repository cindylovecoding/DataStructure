//F74109016 葉惟欣 finished in 2021/10/18 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int iterative(int n){  //傳入最後要印iterative第幾項
	int f0 =0,f1 =1,f2,i;
	if(n==0||n==1){
		return n;
	}
	else{
		for(i=1;i<n;i++){  
			f2 = f0+f1;
			f0 = f1;
			f1 = f2;
		}
		return f2;
	}
}
int recursive(int i){   //傳入最後要印recursive第幾項
	if(i==0){
		return 0;
	}
	else if(i==1){
		return 1;
	}
	else{
		return recursive(i-1)+recursive(i-2);
	} 	
}
int main(){
	int len,num;  //len represents the amount of questions.
	              //num represents the amont of number
	scanf("%d",&len); 
	int i;
	char string [20];
	int answer[len];
	for(i=0;i<len;i++){
		scanf("%s",string);
		scanf("%d",&num);
		if(strcmp(string,"recursive")==0){
			answer[i] = recursive(num);
		}
		else if(strcmp(string,"iterative")==0){
			answer[i] = iterative(num);
		}
	}
	printf("\n");
	for(i=0;i<len;i++){
		printf("%d\n",answer[i]);
	}
	return 0;
}


