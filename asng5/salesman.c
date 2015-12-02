#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define SIZE 799999
#define HASH_SIZE 13
#define NAME_SIZE 10
// #define PATH_SIZE


typedef struct route ROUTE;
struct route{
  char name[NAME_SIZE];
  int weight;
  ROUTE *next;
};

typedef struct city CITY;
struct city{
  char name[NAME_SIZE];
  ROUTE *route;
  CITY *next;
  int visited;
};

typedef struct hash HASH;
struct hash{
  CITY cities[HASH_SIZE];
};

char* choplast(char*word){
  word[strlen(word)-1]=0;
  return word;
}

char* chopfirst(char*word){
  word++;
  return word;
}

void printhash(HASH*hash){
  printf("\n\n\nPRINT HASH:\n");
  for (int i = 0; i < HASH_SIZE; ++i)
  {
    CITY * city = &hash->cities[i];
    ROUTE * route = city->route;
    if(strcmp(city->name,"")!=0){
      printf("name:%s next:%p\n",city->name,city->next);
      printf(" route: from:%s to:%s weight:%i\n",city->name,route->name,route->weight);
      // printf("    start:%s end:%s weight:%i\n",city->name,route->name,route->weight);
      while(route->next != NULL){
        route = route->next;
        printf(" route: from:%s to:%s weight:%i\n",city->name,route->name,route->weight);
      }
      while(city->next != NULL){
        city = city->next;
        route = city->route;
        printf("  name:%s next:%p\n",city->name,city->next);
        printf("   route: from:%s to:%s weight:%i\n",city->name,route->name,route->weight);
        // printf("  name:%s next:%p\n",city->name,city->next);
        while(route->next != NULL){
          // printf("next:%p\n", route->next);
          route = route->next;
          printf("   route: from:%s to:%s weight:%i\n",city->name,route->name,route->weight);
        }
      }
    }
  }
  printf(":HASH PRINTED\n");
}

int addletters (char* word, int primeIndex){
  //shitty hashing function
  int primes[5] = {10729, 10303, 10427};
  int weight = strlen(word);
  int r = 0;
  int power = 1;
  for (int i = 0; i < weight; ++i)
  {
    int ascii = (int) word[i];
    if(ascii != 10){
      power = power%primes[primeIndex-1] *128;
      r+= ascii*power;
    }
  }
  return r;
}

int numOfCities;

CITY * findCity(char*name, HASH*hash){
  int i= addletters(name,1)%HASH_SIZE;
  CITY*city = &hash->cities[i];
  // printf("name:%s city->name:%s\n",name,city->name);
  // printf("cmp:%i\n",strcmp(city->name,name));
  if(strcmp(city->name,name)==0){
    return city;
  }else{
    while(city->next != NULL){ //go through the linked list of cities
      if(strcmp(city->name,name)==0){
        return city;
      }
      city = city->next;
    }
  }
  return NULL;
}

void addtohash (char*name, HASH*hash){
  // printf("Open function:  ");
  int i= addletters(name,1)%HASH_SIZE;
  // printf("i:%i  ",i );
  CITY*city = &hash->cities[i];
  // printf("city->name:%s name:%s cmp:%i\n",city->name,name,strcmp(city->name,name));
  if(strcmp(city->name,name)==0){
    return; //return out if you've already added the city
  }else if(strcmp(city->name,"")==0){ //if the hash slot doesn't have anything in it
    strcpy(city->name,name); //put the city there
    numOfCities++;
  }else{ //if the hash slot did have a city there that isn't the city we want
    while(city->next != NULL){ //go through the linked list of cities
      // printf("  city->name:%s name:%s cmp:%i next:%p\n",city->name,name,strcmp(city->name,name),city->next);
      if(strcmp(city->name,name)==0){
        return; //return out if you've already added the city
      }
      city = city->next;
    }
    //if you get to the end then add the city to the end the linked list
    numOfCities++;
    CITY *newcity = (CITY*)malloc(sizeof(CITY));
    city->next = newcity;
    city = city->next;
    city->next = NULL;
    city->route = NULL;
    city->visited = 0;
    strcpy(newcity->name,name);
  }
  // printf("   city->name:%s name:%s cmp:%i next:%p\n",city->name,name,strcmp(city->name,name),city->next);
}

void addroute(char*start, char*end, int weight, HASH*hash){
  // printf("\naddroute start:%s end:%s weight:%i\n",start,end,weight);
  // printf("start:%s end:%s weight:%i\n",start,end,weight);
  int i= addletters(start,1)%HASH_SIZE;
  CITY*city = &hash->cities[i];
  while(city->next != NULL && strcmp(city->name,start)!=0){
    city = city->next;
    // printf("  city->name:%s, i:%i\n",city->name,i);
  }
  // printf("  city->name:%s\n",city->name);
  // printf(" end:%s i:%i\n",end,i);
  ROUTE *newroute = (ROUTE*)malloc(sizeof(ROUTE));
  newroute->weight = weight;
  strcpy(newroute->name,end);
  newroute->next=city->route;
  city->route = newroute;
}

char* bestRoute;
int bestDistance=10000000;

char * makePassPath(char*current){
  printf("makePassPath\n");
  char *path;
  int pathsize=numOfCities*NAME_SIZE+numOfCities;
  path = (char*)calloc(pathsize,sizeof(char));
  if(strcmp(current,"")==0){
    for (int i = 0; i < pathsize; ++i)
    {
      if(i%(NAME_SIZE+1) == 0){
        path[i]=':';
      }else{
        path[i] = ' ';
      }
    }
    path[pathsize]=0;
    return path;
  }else{
    strcpy(path,current);
    return path;
  }
}

void findHamiltonian(char*start, char*end, HASH*hash, int distance, char *path, int citiesVisited,int tabs){
  char tabsArr[tabs+1];
  for (int i = 0; i < tabs; ++i)
  {
    tabsArr[i] = ' ';
  }
  tabsArr[tabs]=0;
  printf("%sstart:%s end:%s distance:%i visited:%i\n",tabsArr,start,end,distance,citiesVisited);
  printf("%spath:%s\n",tabsArr,path);
  CITY*city = findCity(start,hash);
  printf("%sstart:%s distance:%i\n",tabsArr,city->name,distance);
  if(city->visited){
    return; //if you've already been to this city return empty
  }else if(distance>=bestDistance){
    return;//if you've found a route that's faster than current distance
  }else if(citiesVisited==numOfCities){ //if you've visited every city
    ROUTE*route = city->route;
    while(route !=NULL){//look through all exiting edges
      if(strcmp(route->name,end)==0){//if that edge leads home
        printf("%s****FOUND HAMILTONIAN***** distance:%i\n",tabsArr,distance);
        if(distance+route->weight < bestDistance){
          int j=0;
          int k = (NAME_SIZE+1)*(citiesVisited-1)+1;
          while(start[j]!=0){
            path[k]=start[j];
            j++;
            k++;
          }
        int pathsize=numOfCities*NAME_SIZE+numOfCities;
        bestRoute=malloc(pathsize*sizeof(char));
        strcpy(bestRoute,path);
        bestDistance=distance+route->weight;
        }
      }
      route = route->next;
    }
  }else{
    int j=0;
    int k = (NAME_SIZE+1)*(citiesVisited-1)+1;
    while(start[j]!=0){
      path[k]=start[j];
      j++;
      k++;
    }
    printf("%sstart:%s path:%s\n",tabsArr,start,path);
    ROUTE*route = city->route;
    if(route == NULL){
      return ; //if there are no routes out of this return empty
    }else{
      city->visited = 1;
      while(route->next != NULL){
        char* passPath = makePassPath(path);
        findHamiltonian(route->name,end,hash,distance+route->weight,passPath,citiesVisited+1,tabs+1);
        route = route->next;
        free(passPath);
      }
      city->visited = 0;
    }


    printf("%sstarting:%s path:%s\n",tabsArr,city->name,path);
  }
}




FILE *fr;
char buffer[NAME_SIZE];
int main(int argc, char const *argv[])
{
  printf("PATH_SIZE%i\n",numOfCities*NAME_SIZE+numOfCities);
  HASH* newhash = (HASH*)calloc(1,sizeof(HASH));

  char name1[NAME_SIZE];
  char name2[NAME_SIZE];
  int weight;

  char line[80];
  fr = fopen ("map.txt", "r");
  while(fgets(line, 80, fr) != NULL)
  {
    strcpy(name1,choplast(strtok(line,":")));
    strcpy(name2,chopfirst(choplast(strtok(NULL,":"))));
    weight=atoi(strtok(NULL,":"));
    addtohash(name1,newhash);
    addtohash(name2,newhash);
    addroute(name1,name2,weight,newhash);
    addroute(name2,name1,weight,newhash);
  }
  fclose(fr);  // close the file. We now have our Map hash
  // printhash(newhash);
  // printf("numOfCities: %i\n",numOfCities );
  printf("%s\n", "input starting city: ");
  fgets(buffer, 10, stdin);
  char* start =choplast(buffer); //this removes the \n at the end of the input
  char *path = makePassPath("");
  findHamiltonian(start, start, newhash, 0, path, 1,0);
  // path[0]='a';
  // path[20]='c';
  printf("best route:%s is %i miles\n",bestRoute,bestDistance);
}


