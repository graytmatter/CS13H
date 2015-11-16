#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define SIZE 799999
#define BUF_SIZE 500
#define HASH_SIZE 163
# define SETBIT(A, k) { A[k >> 3] |= (01 << (k & 07)); }
# define CLRBIT(A, k) { A[k >> 3] &= ~(01 << (k & 07)); }
# define GETBIT(A, k) ( A[k >> 3] >> (k & 07) & 01 )

typedef struct bloom BLOOM;
struct bloom{
  unsigned char bytes[SIZE/8 +1];
};

typedef struct word WORD;
struct word{
  char oldspeak[80];
  char newspeak[80];
  WORD *next;
};

typedef struct hash HASH;
struct hash{
  WORD words[HASH_SIZE];
};

// void removeln(char**word){

// }
// void printList(WORD*list){
//   printf("%s\n","printing nodes" );
//   if(list == NULL){
//     printf("%s\n", "(NULL)");
//   }
//   while(list != NULL){
//     printf("word:%s count: %i \n", list->word,list->count);
//     list = list->next;
//   }
// }

int addletters (char* word, int primeIndex){
  int primes[5] = {10729, 10303, 10427};
  int length = strlen(word);
  int r = 0;
  int power = 1;
  for (int i = 0; i < length; ++i)
  {
    int ascii = (int) word[i];
    if(ascii != 10){
      power = power%primes[primeIndex-1] *128;
      r+= ascii*power;
    }
  }
  return r;
}
int hashcols= 0;
void addtohash (char*key, char*value, WORD*words){
  int i= addletters(key,1)%HASH_SIZE;
  WORD*node = &words[i];
  while(node->next != NULL){
    node = node->next;
    hashcols++;
  }
  strcpy(node->oldspeak,key);
  // printf("i:%lu char:%c ascii:%i\n", strlen(node->oldspeak)-1,node->oldspeak[strlen(node->oldspeak)-1], (int) node->oldspeak[strlen(node->oldspeak)-1]);
  node->oldspeak[strlen(node->oldspeak)-1]=0; //these delete the line break on the end of vals and keys
  strcpy(node->newspeak,value);
  node->newspeak[strlen(node->newspeak)-1]=0;
}

char* getnewspeak(char*key, WORD*words){
  int i= addletters(key,1)%HASH_SIZE;
  WORD*node = &words[i];
  while(strcmp(node->oldspeak,key)!=0){
    // printf("node:%s key:%s val:%s strcmp: %i\n",node->oldspeak,key,node->newspeak,strcmp(node->oldspeak,key));
    node = node->next;
    if(node == NULL){
      return "";
    }
  }
  return node->newspeak;
}



FILE *fr;

int main(int argc, char const *argv[])
{
  static char buffer[BUF_SIZE];

  float A = -1+(sqrt(5)+1)/2;
  BLOOM* bloom1 = (BLOOM*)calloc(1,sizeof(BLOOM));
  BLOOM* bloom2 = (BLOOM*)calloc(1,sizeof(BLOOM));
  BLOOM* bloom3 = (BLOOM*)calloc(1,sizeof(BLOOM));

  char line[80];
  fr = fopen ("words.txt", "r");
  // int cols = 0;
  while(fgets(line, 80, fr) != NULL)
  {
    // if(GETBIT(bloom1->bytes,addletters(line,1)%SIZE) && GETBIT(bloom2->bytes,addletters(line,2)%SIZE) && GETBIT(bloom3->bytes,addletters(line,3)%SIZE)){
    //   cols += 1;
    // };
    SETBIT(bloom1->bytes,addletters(line,1)%SIZE);
    SETBIT(bloom2->bytes,addletters(line,2)%SIZE);
    SETBIT(bloom3->bytes,addletters(line,3)%SIZE);
  }
  // printf("cols:%i\n",cols); //This prints out the number of collision that happened making the english bloom filter
  fclose(fr);  // close the file. We now have our bloom filter

  fr = fopen ("newspeak.txt", "r");
  HASH* newshash = (HASH*)calloc(1,sizeof(HASH));

  char key[80];
  char value[80];
  while(fgets(key, 80, fr) != NULL)
  {
    fgets(value, 80, fr);
    addtohash(key,value,newshash->words);
  }
  fclose(fr);  // close the file. We now have our bloom filter
  // printf("hcols:%i\n", hashcols);
  char word[80];
  int thing = 1;
  int thoughtcrimes = 0;
  printf("%s\n", "input text, hit enter, when done make new line and EOF:");
  while(thing>0)
  {
    thing = scanf("%s",word);
    if((!GETBIT(bloom1->bytes,addletters(word,1)%SIZE) || !GETBIT(bloom2->bytes,addletters(word,2)%SIZE) || !GETBIT(bloom3->bytes,addletters(word,3)%SIZE)) && thing ==1){
      thoughtcrimes++;
    }
    // printf("newspeak: %s\n", getnewspeak(word,newshash->words));
    if(strcmp(getnewspeak(word,newshash->words),"")!=0){
      printf("Miniluv recomends using %s instead of %s.\n", getnewspeak(word,newshash->words),word);
    }

    // if(())
    // printf("thing:%i\n", thing);
    // printf("word:%s\n",word);
    // printf("bit:%i\n", GETBIT(bloom1->bytes,addletters(word,1)%SIZE));
  }
  if(thoughtcrimes == 1){
    printf("You have commited 1 thoughtcrime. This is very ungood, very ungood indeed. Do not do this again. \n"  );
  }else if(thoughtcrimes == 0){
    printf("You have commited no thoughtcrimes, Miniluv has good bellyfeel about you.\n");
  }else{
    printf("You have commited %i thoughtcrimes. Doubleplus ungood. Off to joycamp!!\n", thoughtcrimes);
  }
  // printf("%i\n",addletters("hello")%SIZE);
  // printf("%i\n",GETBIT(bloom1->bytes,addletters("hello")%SIZE));
  // return 0;
}
