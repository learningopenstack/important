#include <iostream>
using namespace std;

/*
void Merge(int *a, int *l, int lSize, int *r, int rSize){
    int i, j, k;
    i=0; j=0; k=0;

    while(i<lSize && j <rSize){
        if(l[i] < r[j]){
            a[k++] = l[i++];
        }else{
            a[k++] = r[j++];
        }
    }

    while(i<lSize) {
        a[k++] = l[i++];
    }

    while(j < rSize){
        a[k++] = r[j++];
    }
}

// Recursive function to sort an array of integers.
void MergeSort(int *A,int n) {
    int mid,i, *L, *R;
    if(n < 2) return; // base condition. If the array has less than two element, do nothing.

    mid = n/2;  // find the mid index.

    // create left and right subarrays
    // mid elements (from index 0 till mid-1) should be part of left sub-array
    // and (n-mid) elements (from mid to n-1) will be part of right sub-array
    L = new int[mid];
    R = new int[n - mid];

    for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
    for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

    MergeSort(L,mid);  // sorting the left subarray
    MergeSort(R,n-mid);  // sorting the right subarray
    Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
    // the delete operations is very important
    delete [] R;
    delete [] L;
}
*/


int count = 0;
void Merge(int *a, int left, int mid, int right){
    int i, j, k;
    i=0; j=0; k=left;

    int left_size = mid - left + 1;
    int right_size = right - mid;

    int *left_ptr = new int[left_size];
    int *right_ptr = new int[right_size];

    for(i=0; i<left_size; i++){
        left_ptr[i] = a[left+i];
    }

    for(i=0; i<right_size; i++){
        right_ptr[i] = a[mid+1+i];
    }
    i = 0; j=0;
    while(i<left_size && j <right_size){
        if(left_ptr[i] > right_ptr[j]){
            a[k++] = right_ptr[j++];
        }else{
            a[k++] = left_ptr[i++];
            if(right_ptr[j] < left_ptr[i]){
                count += left_size - i + 1;
            }
        }
    }

    while(i<left_size){
        a[k++] = left_ptr[i++];
    }

    while(j<right_size){
        a[k++] = right_ptr[j++];
    }
    delete []left_ptr;
    delete []right_ptr;
}

/*
void Merge(int a[],int left,int mid,int right)
{
    //两段区间的长度
    int length1 = mid-left+1;
    int length2 = right-mid;
 
    //分配两段新的内存空间存储原内容
    int *l1 = new int[length1];
    int *l2 = new int[length2];
 
    for (int i = 0; i < length1; ++i)
    {
        l1[i] = a[left+i];
    }
    for (int j = 0; j < length2; ++j)
    {
        l2[j] = a[j+mid+1];
    }
 
    //存入原内容之后，比较两个序列
    int i = 0,j = 0;
    //比较两个序列的重合部分，进行排序
    while (i<length1 && j<length2)
    {
        if (l1[i] < l2[j])
        {
            a[left++] = l1[i++];
        }
        else
        {
            a[left++] = l2[j++];
            //因为l2[j]大于l1[i],所以l2[j]肯定大于[0,length-1]之中[0,i]之间的所有数，产生逆序对
            if (l2[j] > l1[i])
            {
                count +=  length1-i+1;
            }       
        }
    }
    //两序列的剩余部分分别放于结尾
    while (i<length1)
    {
        a[left++] = l1[i++];
    }
 
    while (j<length2)
    {
        a[left++] = l2[j++];
    }
 
    //分配的内存需要释放掉
    delete []l1;
    delete []l2;
}
*/

void merge_sort(int *a, int left, int right){
    if(left < right){
        int mid = (left + right)/2;
        merge_sort(a, left, mid);
        merge_sort(a, mid+1, right);
        Merge(a, left, mid, right);
    }
}

int main() {
    /* Code to test the MergeSort function. */

    int A[] = {6,2,3,1,9,10,15,13,10,12,17}; // creating an array of integers.
    int i,numberOfElements;

    // finding number of elements in array as size of complete array in bytes divided by size of integer in bytes.
    // This won't work if array is passed to the function because array
    // is always passed by reference through a pointer. So sizeOf function will give size of pointer and not the array.
    // Watch this video to understand this concept - http://www.youtube.com/watch?v=CpjVucvAc3g
    numberOfElements = sizeof(A)/sizeof(A[0]);

    // Calling merge sort to sort the array.
    //MergeSort(A,numberOfElements);
    merge_sort(A, 0, numberOfElements -1);
    //printing all elements in the array once its sorted.
    for(i = 0;i < numberOfElements;i++)
       cout << "->" << A[i];
    std::cout << std::endl;
    return 0;
}
