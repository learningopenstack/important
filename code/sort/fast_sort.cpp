//
// Created by root on 19-3-6.
//


#include <iostream>
/*
 * 查找数组中第k大的数
 */

int partition(int *arr, int l, int r){
    int first = l;
    int guard = (l+r)/2;
    for(int i=first; i<=r; i++){
        if(arr[i] < k){
            int tmp = arr[i];
            arr[(i)] = arr[guard];
            arr[guard] = tmp;
            guard++;
        }
    }
    int tmp = arr[l];
    arr[l] = k;
    arr[first] = tmp;
    return l - 1;
}

void quickSort(int *arr, int start, int end){
    if(start < end){
        int mid = partition(arr, start, end);
        std::cout << "mid: " << mid << std::endl;
        quickSort(arr, start, mid - 1);
        quickSort(arr, mid + 1, end);
    }
}

int find_kth_largest(int *arr, int start, int end, int k){
    while(start < end){
        int i = start;
        int j = end;

        int pivot = arr[start];
        while(i <= j){
            while(i <= j && arr[i] >= pivot)
                i++;
            while(i<=j && arr[j] < pivot)
                j--;
            if(i<j)
                swap(nums[i++], nums[j--]);
        }
    }
}


