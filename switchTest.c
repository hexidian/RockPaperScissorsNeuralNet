#include <stdio.h>
#include <string.h>
int main(){
  char thing[1];
  scanf("%s",thing);
  printf("%d\n",strcmp("y",thing));
  if (strcmp("y",thing)==0) {
    printf("yes\n");
  }
}
