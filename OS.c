#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include  <stdio.h>
#include  <sys/types.h>
int    myHelp(char *args);
int    myExit();
int    myRecord();
//int    myReplay(char *args);
int myPid(char *args,char *id);

/****history(record)******************/
char RECODR[16];
struct node{
    char* str;
    struct node* next; 
};
typedef struct node NODE;
NODE * tail =  NULL;
NODE * head = NULL;
NODE * prev = NULL;
int exist = 0;
/****history(record)******************/

char *commandMyself[] = {"help","record","replay","mypid"};
int myNumBuiltins(){
    return sizeof(commandMyself) /sizeof(char *);
}
int count = 0;
int redirectIn(char *fileName){
    int in = open(fileName,O_RDONLY);
    dup2(in,0);
    close(in);
    return 1;
}

int redirectOut2(char *command,char *commandP, char *fileName)
{
  int in, out;
  // open input and output files
  out = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  // replace standard output with output file

  dup2(out, 1);

  close(out);

  // execute grep
  for(int i = 0 ;i < myNumBuiltins();i++){
                    if (strcmp(commandMyself[i], command) == 0) {
                        switch (i){
                            case 0:return myHelp( command); break;
                            case 1: return myRecord(); break;
                            case 2: return myReplay(command[1]); break;
                            case 3: return myPid(command[1],command[2]); break;
                        }
                    }
                }
  execvp(command, commandP);
}

int redirectOut(char *fileName){
    int out = open(fileName,O_WRONLY | O_TRUNC | O_CREAT,0600);
    dup2(out,1);
    close(out);
    return 1;
}

void  parse(char *line, char **argv){
    count = 0;
    while (*line != '\0') {       /* if not the end of line ....... */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0    */
        *argv++ = line;          /* save the argument position     */
        count++;
        while (*line != '\0' && *line != ' ' && 
            *line != '\t' && *line != '\n') 
        line++;             /* skip the argument until ...    */
    }
    *argv = '\0';                 /* mark the end of argument list  */
}

char  line[1024];             
char  *argv[64];              
int execute(){
    parse(line, argv);       

    char ***commands = (char***) calloc(20,sizeof(char**));
    for(int k = 0; k < 20;k++){
        commands[k] = (char**) calloc(20, sizeof(char*)); 
        for (int i = 0; i < 20; i++ ){       
            commands[k][i] = (char*) calloc(20, sizeof(char));
        }
    }

    int numOfCommand = 0,numOfParameter = 0;
    int counter = 0;
   
    while(count--){
        
        if((strcmp(argv[counter],"<")==0 )|| (strcmp(argv[counter],">")==0)){
            commands[numOfCommand][numOfParameter] = NULL;
            numOfCommand++;
            commands[numOfCommand][0] = argv[counter];
            commands[numOfCommand][1] = NULL;
            numOfCommand++;
            numOfParameter = 0;
        }
        else{
            if(strcmp(argv[counter],"|")!=0){
                commands[numOfCommand][numOfParameter] = argv[counter];
                commands[numOfCommand][numOfParameter+1] = NULL;
                numOfParameter++;
            }
            else{
                commands[numOfCommand][numOfParameter] = NULL;
                numOfCommand++;
                numOfParameter = 0;
            }
        
        }
        counter++;
    }
    numOfCommand++;
    if(strcmp(commands[0][0],"exit")==0){
        myExit();
        return 0;
    }
    /*************************************************************/
    /************pipeline*****************************************/
    /*************************************************************/
    int prev_pipe, pfds[2];
    prev_pipe = STDIN_FILENO;
         
    pid_t  pid;
    int    status;
    
    if ((pid = fork()) < 0) {     /* fork a child process           */
    printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0) {          /* for the child process:         */
        for (counter = 0; counter < numOfCommand-1 ; counter++) {
            int tmp = counter;
            
            if(counter+1 < numOfCommand && (strcmp(">", commands[counter+1][0]) == 0 || strcmp("<", commands[counter+1][0]) == 0)){
                counter += 2;
            }
            if(strcmp(">", commands[counter][0]) == 0){
                counter += 1;
            }
            pipe(pfds);
            pid_t cpid = fork();
            if (cpid == 0) {
                // Redirect previous pipe to stdin
                if (prev_pipe != STDIN_FILENO) {
                    dup2(prev_pipe, STDIN_FILENO);
                    close(prev_pipe);
                }
                
                 /****************execute****************************************************/
                if((tmp+1 < numOfCommand)){
                    if(strcmp(">", commands[tmp+1][0]) == 0){
                        
                        int out = open(commands[tmp+2][0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                        dup2(out, 1);
                        close(out);
                        for(int i = 0 ;i < myNumBuiltins();i++){
                            if (strcmp(commandMyself[i], commands[tmp][0]) == 0) {
                                switch (i){
                                    case 0: myHelp( commands[tmp][1]);exit(0);
                                    case 1: myRecord(); exit(0);
                                    case 2: myReplay(commands[tmp][1]); exit(0);
                                    case 3: myPid(commands[tmp][1],commands[tmp][2]); exit(0);
                                }
                            }
                        }
                        execvp(commands[tmp][0], commands[tmp]);
                        exit(1);
                    }
                    if(strcmp("<", commands[tmp+1][0]) == 0){
                        int in = open(commands[tmp+2][0],O_RDONLY);
                        dup2(in,0);
                        close(in);
                        for(int i = 0 ;i < myNumBuiltins();i++){
                            if (strcmp(commandMyself[i], commands[tmp][0]) == 0) {
                                switch (i){
                                    case 0: myHelp( commands[tmp][1]); exit(0);
                                    case 1: myRecord(); exit(0);
                                    case 2: myReplay(commands[tmp][1]); exit(0);
                                    case 3: myPid(commands[tmp][1],commands[tmp][2]); exit(0);
                                }
                            }
                        }
                        execvp(commands[tmp][0], commands[tmp]);
                        exit(1);
                    }
                    else if(strcmp(">", commands[tmp][0]) == 0){
                        int in = open(commands[tmp-1][0],O_RDONLY);
                        int out = open(commands[tmp+1][0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                        char *args[] = {"cat", NULL};
                        dup2(in,0);
                        dup2(out,1);
                        //close(in);
                        //close(out);
                        
                        char ch;
                        while((ch = getc(in)) != EOF)
                            fprintf(stdout, "%c", ch);
                        fclose(in);
                        fclose(out);
                        exit(1);
                    }
                }
           
                // Redirect stdout to current pipe
                dup2(pfds[1], STDOUT_FILENO);
                close(pfds[1]);
                
                for(int i = 0 ;i < myNumBuiltins();i++){
                    if (strcmp(commandMyself[i], commands[tmp][0]) == 0) {
                        switch (i){
                            case 0: myHelp( commands[tmp][1]); exit(0);
                            case 1: myRecord(); exit(0);
                            case 2: myReplay(commands[tmp][1]); exit(0);
                            case 3: myPid(commands[tmp][1],commands[tmp][2]); exit(0);
                        }
                    }
                }
                 
                execvp(commands[tmp][0], commands[tmp]);
                /****************execute****************************************************/
                perror("6execvp failed");
                exit(1);
                
            }
            //dup2(prev_pipe, STDOUT_FILENO);
            // Close read end of previous pipe (not needed in the parent)
            close(prev_pipe);
            // Close write end of current pipe (not needed in the parent)
            close(pfds[1]);
            
            // Save read end of current pipe to use in next iteration
            prev_pipe = pfds[0];
            while (wait(&status) != cpid);
            
        }
        
        if (prev_pipe != STDIN_FILENO) {
            dup2(prev_pipe, STDIN_FILENO);
            close(prev_pipe);
        }
        if(counter < numOfCommand){
        
        for(int i = 0 ;i < myNumBuiltins();i++){
            if (strcmp(commandMyself[i], commands[counter][0]) == 0) {
                switch (i){
                    case 0:return myHelp( commands[counter][1]); exit(0);
                    case 1: return myRecord();exit(0);
                    case 2: return myReplay(commands[counter][1]); exit(0);
                    case 3: return myPid(commands[counter][1],commands[counter][2]); exit(0);
                }
            }
        }
        printf("%s",commands[counter][0]);
        execvp(commands[counter][0], commands[counter]);
        }
        error("3execvp failed");
        exit(1);
        
    }
    else {                                  /* for the parent:      */
        while (wait(&status) != pid);       /* wait for completion  */
    }
}
int main(void){
    while (1) {                   
        printf(">>> ");     
        gets(line);  
        /**************************************/ 
        char *tmp = malloc(sizeof(char) * 128);   
        for(int j = 0;j < strlen(line) + 1;j++){
            tmp[j] = line[j];
        } 
        inserttail(tmp);
        /**************************************/ 
        if(execute() == 0){
            exit(0);
            break;
        }
    }
}
/****************************replay**************************************/

int myReplay(char *args){
    if (args == NULL) {
        fprintf(stderr, "expected argument\n");
    }
    else {
        char str[10];
        strcpy(str,args);
        char *ptr;
        int index = strtoumax(str,&ptr,10);
        if(!(index >= 1 && index <=16)){
            printf("replay: wrong args");
            return 0;
        }
        NODE* current = head;
        int status;
        char **args;
        int bufsize = 128;
        char *commandline = malloc(sizeof(char) * bufsize);
        char *buffer = malloc(sizeof(char) * bufsize);
        for(int i=1;i<= exist;i++){
            if(index == i){
                for(int j = 0;j < strlen((*current).str) + 1;j++){
                    commandline[j] = (*current).str[j];
                    buffer[j] = (*current).str[j];
                }
                //(*prev).str = buffer;
                inserttail(commandline);
                strcpy(line,buffer);
                execute();
                free(args);
            }
            else{
                current = (*current).next;
            }
        }
    }
    return 1;
}
/****************************replay**************************************/
int myHelp(char *args){
    int i;
    printf("WeiHsinYeh's Shell\n");
    printf("The following are built in:\n");
    for (i = 0; i < myNumBuiltins(); i++) {
        printf("  %s\n", commandMyself[i]);
    }
    printf("Use the man command for information on other programs.\n");
    return 1;
}
int myPid(char *args,char *id){

    if(args[1] == 'i'){
        int pid_self = getpid();
        printf("%d\n",pid_self);
    }
    else if(args[1] == 'p'){
        
        char destination[128] = "/proc/";
        
        strcat(destination, id);
        strcat(destination,"/status");
        
        FILE *fp = fopen(destination,"r");
        if(fp == NULL){
            printf("Process id not exist\n");
            return 1;
        }
        char str[10];
        for(int i = 0;i < 7;i++){
            fgets(str,128,fp);
        }
        const char* d = "PPid:\t";
        char *p;
        p = strtok(str,d);
        while(p != NULL){
            printf("%s",p);
            p = strtok(NULL,d);
        }
        fclose(fp);
    }

    //cat /proc/8/task/8/children
    else if(args[1] == 'c'){ //proc pid task pid
        char child[128] = "/proc/";      //cat /proc/800/task/800/children
        strcat(child, id); //會接到要看的pid, 再去看他的小孩是誰
        strcat(child, "/task/");
        strcat(child, id);
        strcat(child, "/children");   //小孩的路徑是這個   cat /proc/8/task/8/children
        //printf("進去的路徑是%s\n", child);
        FILE *fp = fopen(child, "r" );
        if (fp == NULL) {
            printf("Process id not exist\n");
            return 1;
        }
        char str[128] = "No child";
        fgets(str, 128, fp); //小孩在第一行
        printf("%s\n", str);
        fclose(fp);
    }
    return 1;
}
/****************************record**************************************/
void inserttail(char *newcommand){
    if(newcommand[0]=='r'&&newcommand[1]=='e') return;
    NODE * newNode = (NODE*) malloc (sizeof(NODE));
    (*newNode).next = NULL;
    (*newNode).str = newcommand;
    prev = tail;
    if(exist == 0){
        head = newNode;
        exist++;
    }
    else if(exist != 16){
        (*tail).next = newNode;
        exist++;
    }
    else{
        head = (*head).next;
        (*tail).next = newNode;
    }
    tail = newNode;
}

void edittail(char *newcommand){
    (*tail).str = newcommand;
}

int myRecord(){
    NODE* current = head;
    printf("history cmd:\n");
    for(int i=0;i<exist;i++){
        printf("%2d: %s\n",i+1 ,(*current).str);
        current = (*current).next;
    }
    return 1;
}
/****************************record**************************************/
int myExit(){
    printf("\nSee you next time\n");
    return 0;
}
