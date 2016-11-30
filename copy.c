#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int helper();


int main(){
  
  int f = fork();
  int status;
  int ans = wait(&status);
  if(ans == -1) return 0;
  helper();
  return 0;
}

int helper(){
  printf("What would you like to do? ");
  char *a = calloc(1, 256);
  fgets(a, 255, stdin);
  //printf("%s", a);
  char *ans[50];
  *(strchr(a, '\n')) = 0;
  char *n = calloc(1, strlen(a));
  int i = 0;
  int j = 0;
  while(*(a+i)){
    if ((*(a + i) == ' ' && j == 0) ||
	(i!=0 && *(a + i - 1) == ' ' && *(a + i) == ' ')){
      i++;
      printf("s");
      continue;
    }
    *(n+j) = *(a+i);
    i++;
    j++;
  }
  i=0;
  while(n != NULL){ 
    char *s;
    s = strsep(&n, " ");
    ans[i] = s;
    //printf("%s %s\n", s, ans[i]);
    i++;
  }
  
  ans[i] = 0;
    
  if(strcmp(ans[0], "exit") == 0)
    {
      exit(1);
    }

  int ret = execvp(ans[0], ans);
  if(ret) printf("-bash: %s: command not found\n", ans[0]);
  return 1;
}
