#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int helper();

int main(){
  int f = fork();
  int status;
  wait(&status);
  helper();
  return 0;
}

int helper(){
  printf("What would you like to do? ");
  char *a = calloc(1, 256);
  fgets(a, 255, stdin);
  //printf("%s", a);
  char *s;
  char *ans[20];
  *(strchr(a, '\n')) = 0;
  int i = 0;
  while(a != NULL){
    s = strsep(&a, " ");
    ans[i] = s;
    //printf("%s %s\n", s, ans[i]);
    i++;
  }
  ans[i] = 0;

  char* realArgs[i + 1];
  int j = 0;
  for(;j <= i; j++)
  {
    realArgs[j] = ans[j];
    //printf("%s\n", realArgs[j]);
  }

  int ret = execvp(realArgs[0], realArgs);
  if(ret) printf("-bash: %s: command not found\n", realArgs[0]);

  return 1;
}
