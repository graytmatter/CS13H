
  #define BUF_SIZE 20
  typedef struct node NODE;
  struct node{
    char *s;
    int count;
    NODE *next;
  };
  static char buffer[BUF_SIZE];


  int makenode(){

  }
  // int getfirst(){
  //   printf("%s\n", "input word: ");
  //   char * word = fgets(buffer, BUF_SIZE, stdin);
  //   if(word != NULL){
  //     NODE first;
  //     first.count = 1;
  //     first.s = word;
  //     return first;
  //   }
  // }