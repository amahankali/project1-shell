#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>

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
        /*char *dir = calloc(PATH_MAX + 1, 1);
        char buff[PATH_MAX + 1];
        dir = getcwd(buff, PATH_MAX);
        *(dir + strlen(dir)) = '/';
        char *newdir = strcat(dir, ans[1]);*/
        printf("%s\n", ans[1]);
        chdir(ans[1]);
        return 1;
    }/*if(ans[1] == NULL)
      {
        //printf("clearing\n");
        int fd = open("auxfile.txt", O_CREAT | O_TRUNC, 0644);
        close(fd);
        kill(getpid(), SIGTERM);
      }
      else
      {
        int fd = open("auxfile.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
        write(fd, ans[1], strlen(ans[1]));
        close(fd);
        kill(getpid(), SIGTERM);
      }*/
  	if(strcmp(ans[0], "exit") == 0)
  	{
        exit(0);
  	}    
    int f = fork();
    int status;
    if(f == 0) {
        int ret = execvp(ans[0], ans);
  	    if(ret) printf("-bash: %s: command not found\n", ans[0]);
        exit(0); 
    }else{
        int reply = wait(&status);
    }
//maybe we should use the exit function here as well
                                                            //otherwise, the forked version could be the one continuing
    //should exit from forked version in case execvp did not work
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