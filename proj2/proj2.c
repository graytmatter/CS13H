#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define BUF_SIZE 20
// #include <nodes.h>

char*getWord(char*buffer){
  printf("\n%s\n", "input word: ");
  // fgets(buffer, BUF_SIZE, stdin);
  // printf("%s\n",fgets(buffer, BUF_SIZE, stdin));
  // if(buffer != NULL){
  //   for(int i = 0; buffer[i]; i++){
  //     buffer[i] = tolower(buffer[i]);
  //   }
  // }
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
  int cmpCount = 1;
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
  int cmpCount = 1;
  NODE* foundnode = list;
  while(foundnode != NULL && strcmp(foundnode->word,word)!=0){
    cmpCount ++;
    foundnode = foundnode->next;
  }
  if(foundnode != NULL){
    NODE* newList = foundnode;
    if(newList->prev != NULL){ //if it's already at front I don't need to do anything.
      if(newList->next != NULL){ //if it's at the back we don't need to change the NULLS prev pointer
        newList->next->prev = newList->prev; //if it's in the middle switch the next's prev pointer
      }
      newList->prev->next = newList->next; //if it isn't in the front switch the prev's next pointer
      newList->next = list; //put rest after our new first
      list->prev = newList; //put first before new rest
      newList->prev = NULL;
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

int clearList(NODE* list){
  int count = 1;
  while(list->next != NULL){
    count++;
    list = list->next;
    free(list->prev);
  }
  free(list);
  return count;
}



int main(int argc, char const *argv[])
{
  static char buffer[BUF_SIZE];
  if(getWord(buffer) != NULL){
    NODE* basicList = makeNode(buffer);
    int basicCmpCount = 0;
    NODE* MTFRList = makeNode(buffer);
    int MTFRCmpCount = 0;
    while(getWord(buffer) != NULL){
      basicCmpCount += insertBasic(basicList,buffer);
      if(basicList->prev != NULL){
        basicList = basicList->prev;
      }
      MTFRCmpCount += insertMTFR(MTFRList,buffer);
      if(MTFRList->prev != NULL){
        MTFRList = MTFRList->prev;
      }
    }

    //When reading the assignment I saw that it didn't ask me to print the frequency of the words, that's why I structured my end prints this way. I think this is the right format though I'm not sure.
      printf("basicListInsert took %i steps and had %i unique words\n",basicCmpCount,clearList(basicList));
      printf("MTFRListInsert took %i steps and had %i unique words \n",MTFRCmpCount,clearList(MTFRList));
  }
  return 0;
}