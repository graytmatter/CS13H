#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 20
// #include <nodes.h>

char*getWord(char*buffer){
  printf("\n%s\n", "input word: ");
  return fgets(buffer, BUF_SIZE, stdin);
}

typedef struct node NODE;
struct node{
  char word[BUF_SIZE];
  int count;
  NODE *next;
  NODE *prev;
};

NODE* makeNode(char*str){
  NODE* result = (NODE*)malloc(sizeof(NODE));
  strcpy(result->word,str);
  result->count = 1;
  result->next = NULL;
  result->prev = NULL;
  return result;
}

void printList(NODE*list){
  printf("%s\n","printing list" );
  if(list == NULL){
    printf("%s\n", "(NULL)");
  }
  while(list != NULL){
    printf("word:%s count: %i \n", list->word,list->count);
    list = list->next;
  }
}

int insertBasic(NODE *list, char *word) {
  int cmpCount = 0;
  NODE* foundnode = list;
  while(foundnode != NULL && strcmp(foundnode->word,word)!=0){
    cmpCount ++;
    foundnode = foundnode->next;
  }
  if(foundnode != NULL){
    foundnode->count ++;
  }else{
    NODE* newList = makeNode(word);
    newList->next = list;
    list->prev = newList;
    list = newList;
  }
  return cmpCount;
}

int insertMTFR(NODE *list, char *word) {
  int cmpCount = 0;
  NODE* foundnode = list;
  while(foundnode != NULL && strcmp(foundnode->word,word)!=0){
    cmpCount ++;
    foundnode = foundnode->next;
  }
  if(foundnode != NULL){
    NODE* newList = foundnode;
    if(newList->next){
      newList->next->prev = newList->prev;
    }
    if(newList->prev){
      newList->prev->next = newList->next;
      newList->next = list;
      list->prev = newList;
      list = newList;
      printf("%s\n","moved to front" );
    }
    newList->count ++;
  }else{
    NODE* newList = makeNode(word);
    newList->next = list;
    list->prev = newList;
    list = newList;
  }
  return cmpCount;
}



int main(int argc, char const *argv[])
{
  printf( "Lower case of A is %c\n", tolower('A'));
  static char buffer[BUF_SIZE];
  if(getWord(buffer) != NULL){
    NODE* basicList = makeNode(buffer);
    int basicCmpCount = 0;
    NODE* MTFRList = makeNode(buffer);
    int MTFRCmpCount = 0;
    while(getWord(buffer) != NULL){
      // basicCmpCount = insertBasic(basicList,buffer);
      // if(basicList->prev != NULL){
      //   basicList = basicList->prev;
      // }
      MTFRCmpCount = insertMTFR(MTFRList,buffer);
      if(MTFRList->prev != NULL){
        MTFRList = MTFRList->prev;
      }
      // basicList = basic->list;
      // basicList = makeNode(buffer);
      // printf("%s\n", "basicList");
      // printList(basicList);
      printf("%s\n", "MTFRList");
      printList(MTFRList);
    }
  printList(basicList);

  }
  return 0;
}