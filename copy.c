#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int helper();

int main(){
  int f = fork();
  int status;
  wait(&status);
  helper();
  return 0;
}

int helper(){
  int h = 1;
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
  execvp(ans[0], ans);
  if(h){
    helper();
  }
  return 1;
}
