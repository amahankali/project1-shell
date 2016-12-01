#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#define MAXCOMMANDS 50
int reply = 0;

int singleCommand(char* command);

int main () {

	while(1) //inside of while loop reads one-line instruction, splits it by ';', and gives the pieces to singleCommand function
	{
	        if(reply == -1){return 0;}
		printf("What would you like to do? ");
		char *a = (char *) calloc(1, 256);
		fgets(a, 255, stdin);

		char* ans[MAXCOMMANDS];
		*(strchr(a, '\n')) = 0;

		int i = 0;
		while(a)
		{
			char *s = strsep(&a, ";");
			ans[i] = s;
			i++;
		}
    free(a);

		int n = 0;
		for(; n < i; n++)
		{
			int f = fork();
			int status;
			if(reply == -1){ exit(1); return 0;}
			reply = wait(&status);
			if(f == 0) {
			  singleCommand(ans[n]);
			}
      if(WIFSIGNALED(status))
      {

        //printf("cd signal sent successfully\n");
        char* dir = (char *) calloc(1, 50);
        int fd = open("auxfile.txt", O_RDONLY);
        read(fd, dir, 49);
        close(fd);

        //have to deal with special case of dir being empty string
        chdir(dir);
        free(dir);
      }
		}


	}

	return 0;

}

int singleCommand(char* a) {

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
      //printf("%s\n", ans[1]);

      //prints ans[1] to an auxiliary file. 
      //then uses exit(3) and WIFEXITED to inform parent process that cd was used
      //finally, parent uses aux file to use chdir
      if(ans[1] == NULL)
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
      }
  	}
  	if(strcmp(ans[0], "exit") == 0)
  	{
	  kill(getppid(), SIGUSR1);
	  exit(0);
  	}

  	int ret = execvp(ans[0], ans);
  	if(ret) printf("-bash: %s: command not found\n", ans[0]); //maybe we should use the exit function here as well
                                                            //otherwise, the forked version could be the one continuing
  	exit(0); //should exit from forked version in case execvp did not work
  	return 1;

}
