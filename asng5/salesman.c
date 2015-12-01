#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define SIZE 799999
#define BUF_SIZE 500
#define HASH_SIZE 3


typedef struct route ROUTE;
struct route{
  char name[10];
  int length;
  ROUTE *next;
};

typedef struct city CITY;
struct city{
  char name[10];
  ROUTE *route;
  CITY *next;
};

typedef struct hash HASH;
struct hash{
  CITY cities[HASH_SIZE];
};


void printhash(HASH*hash){
  printf("\n\n\nPRINT HASH:\n");
  for (int i = 0; i < HASH_SIZE; ++i)
  {
    CITY * city = &hash->cities[i];
    ROUTE * route = city->route;
    if(strcmp(city->name,"")!=0){
      printf("name:%s next:%p\n",city->name,city->next);
      printf("    start:%s end:%s length:%i\n",city->name,route->name,route->length);
      while(route->next != NULL){
        printf("next:%p\n", route->next);
        route = route->next;
        printf("    start:%s end:%s length:%i\n",city->name,route->name,route->length);
        printf("next:%p\n", route->next);
      }
      while(city->next != NULL){
        city = city->next;
        printf("  name:%s next:%p\n",city->name,city->next);
      }
    }
    // do{
    //   city = city->next;
    // }while(city->next != NULL);
  }
  printf(":HASH PRINTED\n");
}

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

void addtohash (char*name, HASH*hash){
  // printf("Open function:  ");
  int i= addletters(name,1)%HASH_SIZE;
  // printf("i:%i  ",i );
  CITY*city = &hash->cities[i];
  // printf("city->name:%s name:%s cmp:%i\n",city->name,name,strcmp(city->name,name));
  if(strcmp(city->name,"")==0 ||strcmp(city->name,name)==0){ //if the hash slot doesn't have anything in it or is the city
    strcpy(city->name,name); //put the city there
  }else{ //if the hash slot did have a city there
    while(city->next != NULL){ //go to the last city in the linked list
      // printf("  city->name:%s name:%s cmp:%i next:%p\n",city->name,name,strcmp(city->name,name),city->next);
      if(strcmp(city->name,name)==0){
        // printf("   return exit\n");
        return; //return out if you've already added the city
      }
      city = city->next;
    }
    CITY *newcity = (CITY*)malloc(sizeof(CITY));
    city->next = newcity;
    city = city->next;
    city->next = NULL;
    city->route = NULL;
    strcpy(newcity->name,name);
    //add the city to the end of the linked list
  }
  // printf("   city->name:%s name:%s cmp:%i next:%p\n",city->name,name,strcmp(city->name,name),city->next);
}

void addroute(char*start, char*end, int weight, HASH*hash){
  printf("\naddroute start:%s end:%s weight:%i\n",start,end,weight);
  // printf("start:%s end:%s weight:%i\n",start,end,weight);
  int i= addletters(end,1)%HASH_SIZE;
  CITY*city = &hash->cities[i];
  while(city->next != NULL && strcmp(city->name,start)!=0){
    city = city->next;
    printf("  city->name:%s\n",city->name);
  }
  printf("  city->name:%s\n",city->name);
  printf(" end:%s i:%i\n",end,i);
  ROUTE *newroute = (ROUTE*)malloc(sizeof(ROUTE));
  newroute->length = weight;
  strcpy(newroute->name,end);
  newroute->next=city->route;
  city->route = newroute;
}


char* choplast(char*word){
  word[strlen(word)-1]=NULL;
  return word;
}

char* chopfirst(char*word){
  word++;
  return word;
}

// char* getnewspeak(char*key, CITY*cities){
//   int i= addletters(key,1)%HASH_SIZE;
//   CITY*node = &cities[i];
//   while(strcmp(node->name,key)!=0){
//     node = node->next;
//     if(node == NULL){
//       return "";
//     }
//   }
//   return node->newspeak;
// }



FILE *fr;

int main(int argc, char const *argv[])
{
  // printf("1\n");
  // float A = -1+(sqrt(5)+1)/2;
  // BLOOM* bloom1 = (BLOOM*)calloc(1,sizeof(BLOOM));
  // BLOOM* bloom2 = (BLOOM*)calloc(1,sizeof(BLOOM));
  // BLOOM* bloom3 = (BLOOM*)calloc(1,sizeof(BLOOM));

  // char line[80];
  // fr = fopen ("cities.txt", "r"); //this section fills the bloomfilters with the eglish dictionary
  // // int cols = 0; //this and the section below are used to determine the number of colisions
  // while(fgets(line, 80, fr) != NULL)
  // {
  //   // if(GETBIT(bloom1->bytes,addletters(line,1)%SIZE) && GETBIT(bloom2->bytes,addletters(line,2)%SIZE) && GETBIT(bloom3->bytes,addletters(line,3)%SIZE)){
  //   //   cols += 1;
  //   // };
  //   SETBIT(bloom1->bytes,addletters(line,1)%SIZE);
  //   SETBIT(bloom2->bytes,addletters(line,2)%SIZE);
  //   SETBIT(bloom3->bytes,addletters(line,3)%SIZE);
  // }
  // // printf("cols:%i\n",cols); //This prints out the number of collision that happened making the english bloom filter

  // fclose(fr);  // close the file. We now have our bloom filter
  HASH* newhash = (HASH*)calloc(1,sizeof(HASH));

  char name1[10];
  char name2[10];
  int weight;

  char line[80];
  fr = fopen ("map.txt", "r");
  while(fgets(line, 80, fr) != NULL)
  {
    strcpy(name1,choplast(strtok(line,":")));
    strcpy(name2,chopfirst(choplast(strtok(NULL,":"))));
    weight = strtok(NULL,":")[1]-48;
    addtohash(name1,newhash);
    addroute(name1,name2,weight,newhash);
    addtohash(name2,newhash);
    addroute(name2,name1,weight,newhash);
  }
  printhash(newhash);
  // printf("name1:%s\n",newhash[]);
}







// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <math.h>
// #define HASH_SIZE 163
// typedef struct route ROUTE;
// struct route{
//   char name[10];
//   int length;
//   ROUTE *next;
// };

// typedef struct city CITY;
// struct city{
//   char name[10];
//   CITY *next;
//   ROUTE *route;
// };



// typedef struct hash HASH;
// struct hash{
//   CITY *cities[HASH_SIZE];
// };

// int addletters (char* word, int primeIndex){
//   int primes[5] = {10729, 10303, 10427};
//   int length = strlen(word);
//   int r = 0;
//   int power = 1;
//   for (int i = 0; i < length; ++i)
//   {
//     int ascii = (int) word[i];
//     if(ascii != 10){
//       power = power%primes[primeIndex-1] *128;
//       r+= ascii*power;
//     }
//   }
//   return r;
// }

// FILE *fr;
// int main(int argc, char const *argv[])
// {
//   HASH hashmap;
//   char line[80];
//   fr = fopen ("map.txt", "r"); //this section fills the bloomfilters with the eglish dictionary
//   // int cols = 0; //this and the section below are used to determine the number of colisions
//   while(fgets(line, 80, fr) != NULL)
//   {
//     // int i = 0;

//     char * city1name;
//     char * city2name;
//     printf("1\n");
//     CITY * city3;
//     printf("%s\n",city3->name );
//     int length;
//     city1name = choplast(strtok(line,":"));
//     city2name = chopfirst(choplast(strtok(NULL,":")));
//     length = strtok(NULL,":")[1]-48;
//     printf("city1num:%i\n",addletters(city1name,0)%HASH_SIZE);
//     int i1 = addletters(city1name,0)%HASH_SIZE;
//     CITY * city1 = hashmap.cities[i1];
//     // CITY * city2 = hashmap.cities[addletters(city2name,0)%HASH_SIZE];
//     // strcpy(city3->name,city1name);
//     printf("i:%i ->:%s name:%s\n",i1,city3->name,city1name);

//     printf("1:%s 2:%s l:%i\n",city1name,city2name,length);
//     // }
//   }
//   fclose(fr);  // close the file. We now have our bloom filter
// }