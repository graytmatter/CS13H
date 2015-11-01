#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int compares[5];
int moves[5];

int *makeRandomList(int length){
  int *list = malloc(length*sizeof(int));
  for (int i = 0; i < length; ++i)
  {
    list[i] = arc4random();
  }
  return list;
}

int* makeSortedList(int length){
  int *list = malloc(length*sizeof(int));
  for (int i = 0; i < length; ++i)
  {
    list[i] = i;
  }
  return list;
}

void copylist(int inList[], int outList[], int length){
  for (int i = 0; i < length; ++i)
  {
    // printf("%i\n", inList[i]);
    outList[i] = inList[i];
  }
}

void printlist(int list[],int length){
  printf("\n");
  for (int i = 0; i < length; ++i)
  {
    printf("%i\n", list[i]);
  }
}

int checkSortedLow(int list[],int length){
  for (int i = 0; i < length-1; ++i)
  {
    if(list[i]> list[i+1]){
      printf("Not Sorted\n");
      return 0;
    }
  }
  printf("Sorted\n");
  return 1;
}

void SWAP(int *a,int *b){
  int store1 = *a;
  int store2 = *b;
  *a = store2;
  *b = store1;
}
//Stole Minsort from Darrell. I modified a few things to make it more readable.
// minIndex: find the index of the least element.
int minIndex(int a[], int first, int last){
  int min = first;
  for (int i = first; i < last; i += 1) {
    if(a[i] < a[min]){
      min = i;
    }
    compares[0] += 1;
  }
  return min;
}

// minSort: sort by repeatedly finding the least element.
// moves and compares stored at 0
void minSort(int a[], int length){
  for (int i = 0; i < length - 1; i += 1) {
    int min = minIndex(a, i, length);
    if (min != i) {
      SWAP(&a[min], &a[i]);
      moves[0] += 3;
    }
  }
  return;
}

//bubbleSort: sort by repeatedly bubbling up the largest elem.
// moves and compares stored at 1
void bubbleSort(int a[], int length){
  for (int i = 0; i < length; ++i)
  {
    int count = 0;
    for (int j = 0; j < length-1; ++j)
    {
      if(a[j] > a[j+1]){
        // printf("a:%i j+1:%i \n",a[j], a[j+1]);
        SWAP(&a[j],&a[j+1]);
        moves[1] += 3;
        count += 1;
      }
      compares[1] += 1;
    }
    if(count == 0){
      return;
    }
  }
}


//insertionSort: sort by repeatedly inserting into the already sorted list
// moves and compares stored at 2
void insertionSort(int a[], int length){
  for (int i = 1; i < length; ++i)
  {
    int j = i;
    while(j > 0 && a[j] < a[j-1]){
      SWAP(&a[j],&a[j-1]);
      moves[2] += 3;
      compares[2] += 1;
      --j;
    }
    compares[2] += 1;
  }
}



void shellSort(int a[], int length){
  for (int gap = length/2; gap >0; gap = gap/2)
  {
    for (int i = gap; i <= length-gap; ++i)
    {
      int j = i;
      while(j >= gap && a[j] < a[j-gap]){
        SWAP(&a[j],&a[j-gap]);
        moves[3] += 3;
        compares[3] += 1;
        j=j-gap;
      }
      compares[3] += 1;
    }
  }
}

// typedef struct node NODE;
// struct node{
//   int num;
//   int count;
//   NODE *next;
//   NODE *prev;
// };

// NODE* makeNode(int num){
//   NODE* result = (NODE*)malloc(sizeof(NODE));
//   result->num =num;
//   result->count = 1;
//   result->next = NULL;
//   result->prev = NULL;
//   return result;
// }
// NODE* makeRandomLList(int a[], int length){
//   NODE *list = makeNode(a[0]);
//   NODE *last =list;
//   NODE* this;
//   for (int i = 1; i < length; ++i)
//   {
//     this = makeNode(a[i]);
//     this->prev = last;
//     last->next = this;
//     last = this;
//   }
//   return list;
// }

// NODE* insert(NODE*a,NODE*b){
//   NODE* list = a;
//   if(a == NULL){
//     return b;
//   }else if(b == NULL){
//     return a;
//   }else{
//     while(a->next){
//       a = a->next;
//       if(a == a->next){
//         a->next = NULL;
//         printf("%s\n", "points at self");
//       }
//     }
//   }
//   a->next = b;
//   b->prev = a;
//   return list;
// }

// NODE* concat(NODE* a, NODE* b){
//   if(a == NULL){
//     return b;
//   }else if(b == NULL){
//     return a;
//   }else{
//     printf("p%s\n", "1");
//     NODE* list= a;
//     while(a->next != NULL){
//       printf("p%s  %i\n", "4", a->next->num);
//       a = a->next;
//       if(a == a->next){
//         a->next = NULL;
//       }
//     }
//     a->next = b;
//     b->prev = a;
//     return list;
//   }
// }

// void printLList(NODE*list){
//   printf("%s\n","printing list" );
//   if(list == NULL){
//     printf("%s\n", "(NULL)");
//   }
//   while(list != NULL){
//     printf("%i\n", list->num);
//     list = list->next;
//   }
// }


// void quickSort(NODE*list, int length){
//   int pivot = list->num;
//   NODE *left;
//   NODE *right;
//   NODE *mid = list;
//   NODE *this = list->next;
//   NODE *next;
//   mid->next = NULL;
//   while(this->next != NULL){
//     //disconect this elem and store the next elem for later use
//     next = this->next;
//     this->next->prev = NULL;
//     this->next = NULL;
//     // printf("%i\n", mid->num);
//     // printf("%i\n", this->prev->num);

//     if(this->prev){ //you only have to diconent this from prev if it has a prev
//       mid->next = NULL;
//       this->prev = NULL;
//     }
//     if(this->num == pivot){
//       mid = insert(mid, this);
//     }else if(this->num > pivot){
//       right = insert(right, this);
//     }else if(this->num < pivot){
//       left = insert(left, this);
//     }
//     // printf("%i\n",next->num);
//     this = next;
//   }
//   // printf("%s\n","mid");
//   // printLList(mid);
//   // printf("%s\n","left");
//   // printLList(left);
//   // printf("%s\n","right");
//   // printLList(right);
//   // mid->next = NULL;
//   printLList(mid);

// //   int pivot = a[0];
// //   int *pivotPoint = a;
// //   // int *left = &a;
// //   // int leftLength = 0;
// //   // int *right = &a;
// //   // int rightLength = 0;
// //   for (int i = 0; i < length; ++i)
// //   {
// //     // printf("%i\n",*pivotPoint);
// //     pivotPoint++;
// //   }

//   // if(length == 1){
//   //   return pivot;
//   // }
//   // for (int i = 1; i < length; ++i)
//   // {

//   // left = []
//   // mid = []
//   // right = []
//   // pivot = peek(A)
//   // foreach x in A (while A not empty dequeue)
//   //   if x == pivot
//   //     mid = concat(mid, x)
//   //   else if x ≤ pivot
//   //     left = concat(left, x)
//   //   else
//   //     right = concat(right, x)

// }
void printHeap(int a[],int length){
  int j = 1;
  int level = 1;
  for (int i = 0; i < length; ++i)
  {
    printf("%i ",a[i]);
    j++;
    if(j==2*level){
      printf("\n");
      level*=2;
    }
  }
  // printf("\n\n");
}

void makeHeap(int a[],int length){
  int change;
  do{
    change = 0;
    for (int i = 1; i*2 < length+1; ++i)
    {
      int elem = a[i-1];
      int left = a[i*2-1];
      int right= a[i*2];
      // printf("i: %i\n", i);
      // printf("elem:%i, left:%i, right:%i \n\n",elem,left,right);
      // printHeap(a,length);
      compares[4] +=3;
      if(elem > left || (elem > right && i*2 != length)){
        if(right <left && i*2 != length){
          // printf("right is lowest\n");
          SWAP(&a[i-1],&a[i*2]);
          moves[4]+=3;
          change = 1;
        }else{
          // printf("left is lowest\n");
          SWAP(&a[i-1],&a[i*2-1]);
          moves[4]+=3;
          change = 1;
        }
      }
      // printf("\n\n");
    }
  }while(change != 0);
  // printHeap(a,length);
}

void fixheap(int heap[],int length){
  for(int i = 1; i*2 < length+1; ++i)
  {
    int elem = heap[i-1];
    int left = heap[i*2-1];
    int right= heap[i*2];
    compares[4] +=3;
    if(elem > left || (elem > right && i*2 != length)){
      if(right <left && i*2 != length){
        SWAP(&heap[i-1],&heap[i*2]);
        moves[4]+=3;
      }else{
        SWAP(&heap[i-1],&heap[i*2-1]);
        moves[4]+=3;
      }
    }
  }
}

void heapSort(int heap[],int length){
  for (int i = length-1; i>0; --i)
  {
    printf("%i\n", i);
    SWAP(&heap[0],&heap[i]);
    fixheap(heap,length-1);
  }
}

//void (*functions[5]) = {minSort,bubbleSort,insertionSort};


int main(int argc, char const *argv[])
{
  int i;
  printf ("Enter size of list: ");
  scanf ("%d",&i);
  int *inputList = makeRandomList(i);
  int sortingList[i];
  int* sortedList = makeSortedList(i);
  int a[5] = {1,3,4,6,9};
  //minSort
  copylist(inputList,sortingList,i);
    minSort(sortingList,i);
      checkSortedLow(sortingList,i);
      printf("Minsort did %i comparisons and %i moves\n", compares[0], moves[0]);
    moves[0] = 0; compares[0]=0;
    minSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Minsort did %i comparisons and %i moves\n", compares[0], moves[0]);

  //bubbleSort
  copylist(inputList,sortingList,i);
    bubbleSort(sortingList,i);
      checkSortedLow(sortingList,i);
      printf("Bubblesort did %i comparisons and %i moves\n", compares[1], moves[1]);
    moves[1]=0; compares[1]=0;
    bubbleSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Bubblesort did %i comparisons and %i moves\n", compares[1], moves[1]);

  //insertionSort
  copylist(inputList,sortingList,i);
    insertionSort(sortingList,i);
      checkSortedLow(sortingList,i);
      printf("Insertionsort did %i comparisons and %i moves\n", compares[2], moves[2]);
    moves[2] = 0; compares[2]=0;
    insertionSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Insertionsort did %i comparisons and %i moves\n", compares[2], moves[2]);

  //shellSort
  copylist(inputList,sortingList,i);
    shellSort(sortingList,i);
      checkSortedLow(sortingList,i);
      printf("Shellsort did %i comparisons and %i moves\n", compares[3], moves[3]);
    moves[3] = 0; compares[3]=0;
    shellSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Shellsort did %i comparisons and %i moves\n", compares[3], moves[3]);

  //heapSort
  copylist(inputList,sortingList,i);
    makeHeap(sortingList,i);
    heapSort(sortingList,i);
    checkSortedLow(sortingList,i);
    // printlist(sortingList,i);
      // printf("Heapsort did %i comparisons and %i moves\n", compares[3], moves[3]);
    // quickSort(makeRandomLList(sortingList,i),i);
      // printLList(makeRandomList(sortingList,i));
  // makeHeap(sortingList,i);
  return 0;
}








