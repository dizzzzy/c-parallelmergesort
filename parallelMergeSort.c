#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


//gcc -ggdb -lpthread parallel-mergesort.c 

 int a[] = {75, 25, 100, 24, 19, 67, 45, 88, 70, 96, 41,
 36, 72, 150, 1, 25, 25, 77, 200, 90, 166, 139, 55, 31,
  8, 29, 119, 126, 137, 34, 62, 1, 35, 121, 108, 197, 
  45, 35, 24, 1, 16, 43};

struct Params
{  
    int from_index; 
    int to_index; 
    int length;
}; 

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void* bubbleSort(void* params_v) //n= length of array
{
    struct Params* params = (struct Params*) params_v;
    printf("from index: %d\n", params->from_index);
    fflush(stdin);
    printf("to index: %d\n", params->to_index);
    fflush(stdin);
    int b, i, j;
    int n = params->length + params->from_index;
    for (i = params->from_index; i < n-1; i++ && b++)  
    {
        for (j = params->from_index; j < n-b-1; j++) 
        {
            if (a[j] > a[j+1])
                swap(&a[j], &a[j+1]);
        }
    }  
}
 
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
        fflush(stdin);
    printf("\n");
    fflush(stdin);
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


int main()
{
    int n = sizeof(a)/sizeof(a[0]);
    int mid = n/2;  // -> 21
    int* temp_a;
    int* temp_b;
    temp_a = a; //0 to mid-1
    temp_b = a; //mid to n-1
    int length_a = mid;
    int length_b = n - mid;
    int ret; 
    int ret2;
    pthread_t tid;
    pthread_t tid2;
    printf("Unsorted array: \n");
    printArray(a, n);
    struct Params* params_pa;
    struct Params* params_pb;
    struct Params param_a;
    struct Params param_b;
    param_a.from_index = 0;
    param_a.to_index = length_a - 1;
    param_a.length = length_a;
    param_b.from_index = length_a;
    param_b.to_index = length_a + length_b ;
    param_b.length = length_b;
    params_pa = &param_a;
    params_pb = &param_b;
    //create threads for bubblesort
    ret = pthread_create(&tid, NULL, bubbleSort, params_pa); 
    ret2 = pthread_create(&tid2, NULL, bubbleSort, params_pb);
    if (ret) {
            printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);    
            exit(1);
    }
    if (ret2) {
            printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);    
            exit(1);
    }
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    merge(a, 0, mid-1, n-1);
    printf("Sorted array: \n");
    printArray(a, n);
    getchar();
    return 0;
}

