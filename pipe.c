#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>

#define MAXCOMMANDS 50

void print(char* a[], int length)
{
  int i = 0;
  for(; i < length; i++) printf("a[%d]: %s; ", i, a[i]);
  printf("\n");
}

int piper(char *a);

int run(char* a) {
	char *ans[50];
	char *n = calloc(1, strlen(a));
	int i=0;
	int j=0;
	while(*(a+i)){
 		if ((*(a + i) == ' ' && j == 0) ||
			(i!=0 && *(a + i - 1) == ' ' && *(a + i) == ' ')){
      		i++;
      		continue;
    	}
    	else{
      		*(n+j) = *(a+i);
      		i++;
      		j++;
    	}
  	}

  	if(j > 0 && *(n+j - 1)  == ' '){
    	//printf("s");
    	*(n+j-1) = 0;
  	}
  	i=0;
    while(*(n+i)){
        if(*(n+i) == '|'){
            return piper(n);
        }
        i++;
    }
    i = 0;
  	while(n){ 
    	char *s;
    	s = strsep(&n, " ");
    	ans[i] = s;
    	//printf("%s %s\n", s, ans[i]);
    	i++;
  	}
  
  	ans[i] = 0;

  	if(strcmp(ans[0], "cd") == 0)
  	{
        printf("%s\n", ans[1]);
        chdir(ans[1]);
        return 1;
    }
  	if(strcmp(ans[0], "exit") == 0)
  	{
        exit(0);
  	}

    ///////////////////////////Do redirection///////////////////////////
    int f = fork();
    int status;
    if(f == 0)
    {
      char* buffer[MAXCOMMANDS];
      int j = 0;
      int bufferLen = 0;

      for(; j < i;)
      {
        char* token = ans[j];
        if(strcmp(token, ">") == 0)
        {
          char* outFile = ans[j + 1];
          int newFD = open(outFile, O_TRUNC | O_WRONLY | O_RDONLY);
          dup2(newFD, 1);
          j += 2;
        }
        else if(strcmp(token, "<") == 0)
        {
          char* inFile = ans[j + 1];
          int newFD = open(inFile, O_RDONLY);
          dup2(newFD, 0);
          j += 2;
        }
        else
        {
          buffer[bufferLen] = ans[j];
          bufferLen++;
          j++;
        }
      }
      buffer[bufferLen] = 0;

      int ret = execvp(buffer[0], buffer);
      if(ret) printf("-bash: %s: command not found\n", buffer[0]);
      exit(0);
    }
    else {int reply = wait(&status);}
    ////////////////////////////////////////////////////////////////////

    return 1;


}

int piper(char *a){
    char *second = (char *)malloc(256);
    second = strsep(&a, "|");
    int arr[2];
    pipe(arr);
    //int out = dup(STDOUT_FILENO);
    int in = dup(STDIN_FILENO);
    int status;
    int f = fork();
    if (f == 0){
        dup2(arr[1], STDOUT_FILENO); 
        run(second);
        exit(0);
    } 
    else{
        wait(&status);
        dup2(arr[0], STDIN_FILENO);
        close(arr[1]);
        run(a);
        dup2(in, STDIN_FILENO);
    }
  //free(line2);
    return 1;
}