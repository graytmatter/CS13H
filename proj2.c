#include <stdio.h>

int main(int argc, char const *argv[])
{
  #define BUF_SIZE 100
  static char buffer[BUF_SIZE];
  char* x = fgets(buffer, BUF_SIZE, stdin);
  while(*x != NULL){
    printf("%s, %s \n",buffer,*x);
    char* x = fgets(buffer, BUF_SIZE, stdin);
  }
  return 0;
}


// int x;
// x = x+1;
// &x = ....;
// int* y = &x;
// *y == x;

// char* x;
// x = ....;
// *x = firstchar