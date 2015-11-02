#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int compares[7];
int moves[7];

int *makeRandomList(int length){
  int *list = malloc(length*sizeof(int));
  for (int i = 0; i < length; ++i)
  {
    list[i] = arc4random() %1000;
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
//I think
void insertionSort(int a[], int length){
  for (int i = 1; i < length; ++i)
  {
    int j = i;
    int elem = a[i];
    while(j > 0 && elem < a[j-1]){
      a[j] = a[j-1];
      moves[2] += 1;
      compares[2] += 1;
      --j;
    }
    a[j] = elem;
    moves[2] += 1;
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
void quickSort(int a[],int length){
  if(length <= 1){
    return;
  }
  int lastlow = length - 2;
  int firsthigh = 0;
  int pivot = length-1;
  while(lastlow > firsthigh){
    compares[5]+=1;
    while(a[lastlow] > a[pivot]){
      compares[5]+=1;
      lastlow--;
    }
    while(a[firsthigh] < a[pivot]){
      compares[5]+=1;
      firsthigh++;
    }
    if(lastlow > firsthigh){
      SWAP(&a[firsthigh],&a[lastlow]);
      moves[5]+=3;
      firsthigh++;
    }
  }
  if(a[firsthigh]>a[pivot]){
    compares[5]+=1;
    moves[5]+=3;
    SWAP(&a[pivot],&a[firsthigh]);
  }
  quickSort(&a[firsthigh+1],length-(firsthigh+1));
  quickSort(a,firsthigh);
}

void merge(int a[],int al,int b[],int bl){
  int r[al+bl];
  int i=0;
  int j=0;
  while(i < al && j < bl){
    if(a[i] < b[j]){
      compares[6] += 1;
      r[i+j] = a[i];
      moves[6]+=1;
      i++;
    }else{
      compares[6] += 1;
      r[i+j] = b[j];
      moves[6]+=1;
      j++;
    }
  }
  while(i < al){
    r[i+j] = a[i];
    moves[6]+=1;
    i++;
  }
  while(j < bl){
    r[i+j] = b[j];
    moves[6]+=1;
    j++;
  }
  copylist(r,a,al+bl);
}

void mergeSort(int a[], int length){
  if(length <= 1){
    compares[6] += 1;
    return;
  }
  else{
    int half = (length)/2;
    mergeSort(a,half);
    mergeSort(&a[half],length-half);
    merge(a,half,&a[half],length-half);
  }
  return;
}
//

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
  printf("\n\n");
}
void reverselist(int a[], int length){
  for (int i = 0; i < length/2; ++i)
  {
    SWAP(&a[i],&a[length-(i+1)]);
    moves[4]+=3;
  }
}




void makeHeap(int a[],int length){
  for (int i = 1; i < length; ++i)
  {
    int parent = a[(i-1)/2];
    int elem = a[i];
    int j = i;
    while(elem > parent && j != 0){
      compares[4]+=1;
      SWAP(&a[(j-1)/2], &a[j]);
      moves[4]+=3;
      j = (j-1)/2;
      parent = a[(j-1)/2];
      elem = a[j];
    }
  }
}

void fixheap(int heap[],int length){
  int i = 0;
  int elem,left,right;
  elem = i;
  left = 2*i+1;
  right= 2*i+2;
  while(left <= length){
    compares[4] += 1;
    if(right <= length && heap[right]> heap[elem] && heap[right]>heap[left]){
      SWAP(&heap[elem],&heap[right]);
      i=right;
      compares[4] += 3;
      moves[4] += 3;
    }else if(heap[left] > heap[elem]){
      SWAP(&heap[elem],&heap[left]);
      i=left;
      compares[4] += 4;
      moves[4] += 3;
    }else{
      return;
    }
  elem = i;
  left = 2*i+1;
  right= 2*i+2;
  }
}

void heapSort(int heap[],int length){
  for (int i = length-1; i>=0; --i)
  {
    SWAP(&heap[0],&heap[i]);
    fixheap(heap,i-1);
  }
}


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
      printf("Heapsort did %i comparisons and %i moves\n", compares[4], moves[4]);
    moves[4] = 0; compares[4]=0;
    makeHeap(sortedList,i);
    heapSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Heapsort did %i comparisons and %i moves\n", compares[4], moves[4]);

  // quickSort
  copylist(inputList,sortingList,i);
    quickSort(sortingList,i);
      checkSortedLow(sortingList,i);
      printf("Quicksort did %i comparisons and %i moves\n", compares[5], moves[5]);
    moves[3] = 0; compares[3]=0;
    quickSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Quicksort did %i comparisons and %i moves\n", compares[5], moves[5]);

  // mergeSort
  copylist(inputList,sortingList,i);
    mergeSort(sortingList,i);
      checkSortedLow(sortingList,i);
      printf("Merge did %i comparisons and %i moves\n", compares[6], moves[6]);
    mergeSort(sortedList,i);
      checkSortedLow(sortedList,i);
      printf("For a sorted list Mergesort did %i comparisons and %i moves\n", compares[6], moves[6]);


  return 0;
}








