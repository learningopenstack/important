#include <iostream>

void mergeArray(int *a, int first, int mid, int last, int temp[] ){  
    int i = first, j = mid + 1;
    int m = mid,   n = last;
    int k = 0;
          
    while (i <= m && j <= n)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    
    while (i <= m)
        temp[k++] = a[i++];
        
    while (j <= n)
        temp[k++] = a[j++];
            
    for (i = 0; i < k; i++)
       a[first + i] = temp[i];
}

void mergesort(int *head, int first, int last, int temp[]){
    if(first < last){
        int mid = (first + last)/2;
        mergesort(head, first, mid, temp);
        mergesort(head, mid + 1, last, temp);
        mergeArray(head, first, mid, last, temp);
    }
}

void Print(int *head, int len){
   for(int i=0; i<len; i++){
        std::cout << head[i] << "->" ;
   } 
   std::cout << "\n";
}

bool MergeSort(int head[], int len){
    int *p = new int[len];
    if(p==NULL){
        std::cout << "new int[n] failed; "<< std::endl;
        return false;
    }
    mergesort(head, 0, len-1, p);
    Print(head, len);
    delete[] p;
    return true;
}

/*
 * https://blog.csdn.net/misayaaaaa/article/details/66478422
 * https://juejin.im/entry/59a4dd3d518825242927d704
 * https://vimsky.com/article/169.html
 */


