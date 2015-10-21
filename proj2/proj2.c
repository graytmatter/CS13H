#include <stdio.h>
#include <string.h>
#define BUF_SIZE 20
// #include <nodes.h>
typedef struct node NODE;
struct node{
  char word[BUF_SIZE];
  int count;
  NODE *next;
  NODE *prev;
};

NODE makenode(char*str){
  NODE result;
  strcpy(result.word,"str");
  result.count = 1;
  return result;
}
int main(int argc, char const *argv[])
{
  static char buffer[BUF_SIZE];
  printf("%s\n", "input word: ");
  // NODE = f
  while(fgets(buffer, BUF_SIZE, stdin) != NULL){
    NODE list = makenode(buffer);
    printf("%s\n", "p5");
    printf("buffer: %s\n",list.word);

    printf("%s\n", "input word: ");
  }
  return 0;
}
// typedef struct node NODE;
// struct node
// {
//    char  title[50];
//    char  author[50];
//    char  subject[100];
//    int   book_id;
//    NODE *next;
// };

// int main( )
// {
//    BOOK Book1;        /* Declare Book1 of type Book */
//    BOOK Book2;        /* Declare Book2 of type Book */

//    /* book 1 specification */
//    strcpy( Book1.title, "C Programming");
//    strcpy( Book1.author, "Nuha Ali");
//    strcpy( Book1.subject, "C Programming Tutorial");
//    Book1.book_id = 6495407;

//    /* book 2 specification */
//    strcpy( Book2.title, "Telecom Billing");
//    strcpy( Book2.author, "Zara Ali");
//    strcpy( Book2.subject, "Telecom Billing Tutorial");
//    Book2.book_id = 6495700;

//    /* print Book1 info */
//    printf( "Book 1 title : %s\n", Book1.title);
//    printf( "Book 1 author : %s\n", Book1.author);
//    printf( "Book 1 subject : %s\n", Book1.subject);
//    printf( "Book 1 book_id : %d\n", Book1.book_id);

//    /* print Book2 info */
//    printf( "Book 2 title : %s\n", Book2.title);
//    printf( "Book 2 author : %s\n", Book2.author);
//    printf( "Book 2 subject : %s\n", Book2.subject);
//    printf( "Book 2 book_id : %d\n", Book2.book_id);

//    return 0;
// }





// int x;
// x = x+1;
// &x = ....;
// int* y = &x;
// *y == x;

// char* x;
// x = ....;
// *x = firstchar