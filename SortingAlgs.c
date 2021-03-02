#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

unsigned COMPCOUNT;
void SWAP(int arr[],int indexOne,int indexTwo){
    int temp = arr[indexOne];
    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = temp;
}
int myrandom(int lowerBound, int upperBound){
    int i, num;
    for (i=0; i<1;i++){
        num = (rand() % (upperBound - lowerBound +1))+ lowerBound;
    }
    return num;
}
bool COMPARE(int x, int y,int op){ //returns 1 if True 0 if false
    COMPCOUNT++;
    int c=op; // this is the operation, 0= >, 1= < , 2 = ==, 3- >=, 4 = <=,
    switch(c) {
        case 0:
            return ((x > y) ? true:false);
        case 1:
            return ((x < y) ? true:false);
        case 2:
            return ((x == y) ? true:false);
        case 3:
            return ((x >= y) ? true:false);
        case 4:
            return ((x <= y) ? true:false);
        default:
            return false;
    }
}

/* MERGE SORT */

void merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int *L = malloc(sizeof(int) * n1);
    int *R = malloc(sizeof(int) * n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;j = 0;k = left;
    while (i < n1 && j < n2) {
        if (COMPARE(L[i],R[j],4)) { // Should COMPARE be used in this comparison? <--
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int A[],int l, int r){
    if(l<r){
        int m = l+(r-l)/2;
        mergeSort(A,l,m);
        mergeSort(A,m+1,r);
        merge(A,l,m,r);
    }
}
/* End of MergeSort */

/* HeapSort */
/* To heapify a subtree with node i which is an index in arr[]. n is size of the heap. */

void pushdown(int arr[], int n, int r){
    int s;
    if (2*r > n){
        return;
    }
    if(2*r == n || COMPARE(arr[2*r],arr[2*r+1],4)){
        s=2*r;
    }
    else{
        s=2*r+1;
    }
    if(COMPARE(arr[r],arr[s],1)){
        SWAP(arr,arr[r],arr[s]);
        pushdown(arr,n,s);
    }
}
void buildHeap(int arr[],int n, int r){
    if(2*r>n){return;}
    buildHeap(arr,n,2*r);
    buildHeap(arr,n,2*r+1);
    pushdown(arr,n,r);
}

void heapify(int arr[], int n, int i){
    int max = i;
    int leftChild = 2*i +1;
    int rightChild = 2*i+2;
    // If the left child is bigger than max (root)
    if(leftChild < n && COMPARE(arr[leftChild],arr[max],0)){
        max = leftChild;
    }
    if (rightChild < n && COMPARE(arr[rightChild],arr[max],0)){
        max = rightChild;
    }
    if (max != i){
        SWAP(arr,i,max);
        heapify(arr,n,max);
    }
}
void myheapsort(int arr[],int n){
    for (int i=n/2-1; i>=0; i--){
        heapify(arr,n,i);
    }
    for (int i=n-1;i>0;i--){
        SWAP(arr,0,i);
        heapify(arr,i,0);
    }
}



/* End HEAPSORT */

/* BEGIN QUICKSORT */

void cQuickSort(int arr[],int left, int right){
    if(left >= right){
        return;
    }
    int k = myrandom(left,right); // init random pivot index
    int pivot = arr[k]; // find the value at pivot
    SWAP(arr,arr[left],arr[right]);
    int l=left+1;
    int r = right;
    //inward scan to partition
    while (l <= r){
        while (l<=r && COMPARE(arr[l],pivot,4)){
            l=l+1;
        }
        while(l<=r && COMPARE(arr[r],pivot,0)){
            r=r-1;
        }
        if(l<r){
            SWAP(arr,arr[l],arr[r]);
            l=l+1;r=r-1;
        }
    }
    SWAP(arr,arr[left],arr[r]);
    cQuickSort(arr,left,r-1);
    cQuickSort(arr,r+1,right);
}

/*   END QUICKSORT     */

void printArray(int arr[], int n){
  int i;
  for (i=0; i<n; i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}
int *randomArray(int n, int arr[]){
    srand((unsigned)time(NULL));
    for (int i=0;i<n;i++){
        arr[i] = (rand() %n);
    }
    return arr; /* returns integer pointer to first value in array */
}
int *bestCase(int n, int arr[]){
    for(int i=0;i<n;i++){
        arr[i] = i;
    }
    return arr;
}
int *worstCase(int n, int arr[]){
    for(int i=0;i<n;i++){
        arr[i] = n-i;
    }
    return arr;
}
void timedRun(int *p,int n, int op){
    COMPCOUNT=0;
    clock_t start,end;
    double cpuTimeUsed;
    if(op == 0){
        //run mergesort
        printf("Running Merge-sort: \n");
        start=clock();
        mergeSort(p,0,n-1);
        end=clock();
        cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("Total Runtime: %lf \n",cpuTimeUsed);
        printf("Total Comparisons: %d \n",COMPCOUNT);
    }
    else if(op==1){
        //run quicksort
        printf("Running Quicksort: \n");
        start=clock();
        cQuickSort(p,0,n-1);
        end=clock();
        cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("Total Runtime: %lf \n",cpuTimeUsed);
        printf("Total Comparisons: %d \n",COMPCOUNT);
    }
    else{
        //run heapsort
        printf("Running Heapsort: \n");
        start=clock();
        myheapsort(p,n);
        end=clock();
        cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("Total Runtime: %lf \n",cpuTimeUsed);
        printf("Total Comparisons: %d \n",COMPCOUNT);
    }
    if(n<1000){
        printArray(p,n);//print sorted array if n<1024
    }
}
void analyzeFunction(int n,int op){
    int *arr = malloc(sizeof(int)*n);
    int *p;
    if (op==0){ // 0= random variables
        printf("Random Array: n= %d \n",n);
        p=randomArray(n,arr); //init array of random vars
    }
    else if (op==1){
        printf("Best Case Array: n = %d \n",n);
        p=bestCase(n,arr); //init array of best case scenario
    }
    else{
        printf("Worst Case Array: n = %d \n",n);
        p=worstCase(n,arr); //init array of worst case scenario
    }
    if(n<1000){
        printArray(p,n);//print unsorted array if n<1000
    }
    for(int i=0;i<3;i++){
        timedRun(p,n,i);
    }
    free(arr);
}
void analyzeFunctions(int n){
    if (n<=32){
        for(int i=0;i<3;i++){
            analyzeFunction(n,i);
        }
    }
    else{
        analyzeFunction(n,0);
    }
}

int main(int argc, char *argv[]){
    int n = 32; // initialize array size 32
    printf("Running analysis on n=32...\n");
    analyzeFunctions(n);
    printf("Running analysis on n=1024...\n");
    n=1024;
    analyzeFunctions(n);
    printf("Running analysis on n=32768...\n");
    n=32768;
    analyzeFunctions(n);
    printf("Running analysis on n=1048576...\n");
    n=1048576;
    analyzeFunctions(n);
    return 0;
}
