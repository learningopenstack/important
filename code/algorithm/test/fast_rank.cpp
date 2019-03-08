#include <iostream>
template <typename T>
void printArr(T *arr, int left, int right){
    for(int i=left; i<=right; i++) {
        std::cout << arr[i] << "\t";
    }
    std::cout << "\n";
}

template <typename T>
int partition(T *arr, int left, int right){
    int pivot = arr[right];
    int key = left;

    for(int i=left; i<right; i++){
        //if(arr[i] <= pivot && key != i){
        if(arr[i] <= pivot ){
            std::swap(arr[i], arr[key]);
            std::cout << "i=" << i << std::endl;
            std::cout << "key=" << key << std::endl;
            key++;
        }
    }
    std::swap(arr[key], arr[right]);
    return key;
}

template <typename T>
void quick_sort(T *arr, int left, int right){
    if(left<=right){
        int middle = partition(arr, left, right);
        quick_sort(arr, left, middle-1);
     //   printArr(arr, 0, 7);
        quick_sort(arr, middle+1, right);
    }
}


//挖坑
template <typename T>
int partition2(T *arr, int left, int right){
    T pivot = arr[left];
    while(left < right){
        while(arr[right] >= pivot && right > left){
                right--;
        }
        arr[left] = arr[right];
        while(arr[left] < pivot &&  right > left){
            left++;
        }
        arr[right] =  arr[left];
    }
    arr[left] = pivot;
    return left;
    /*
    T pivot = arr[(left + right)/2];
    while(left < right){
        while(arr[right] > pivot && right > left){
            right--;
        }
        while(arr[left] < pivot && right > left){
            left++;
        }
        if(left != right){
            std::swap(arr[left], arr[right]);
        }
    }
    arr[left] = pivot;
    return left;
    */
}
template <typename T>
void quick_sort2(T *arr, int left, int right){
    if(left <= right){
        int middle = partition2(arr, left, right);
        quick_sort2(arr, left, middle-1);
        quick_sort2(arr, middle+1, right);
    }
}


template <typename T>
int partition3(T *arr, int l, int r){
    T pivot = arr[l];
    int left = l;
    int right = r; 

    while(left < right){
        while(arr[left] < pivot && left < right){
            left++;
        }
        while(arr[right] > pivot && left < right){
                right--;
        }
        if(right > left){
            std::swap(arr[left], arr[right]);
        }
    }
    std::swap(arr[left], arr[right]);
    return left;
}
template <typename T>
void quick_sort3(T *arr, int left, int right){
    if(left < right){
        int middle = partition3(arr, left, right);
        quick_sort3(arr, left, middle-1);
        quick_sort3(arr, middle+1, right);
    }
}

template <typename T>
int parition11(T *arr, int left, int right){
    int pivot = arr[left];
    int l = left;
    int r = right;

    while(l < r){
        while(l<r && arr[r] >= pivot){
            r--;
        }
        arr[l] = arr[r];
            
        while(l<r && arr[l] < pivot){
            l++;
        }
        arr[r] = arr[l]; 
    }
    arr[l] = pivot; 
    return l;
}
template <typename T>
int parition12(T *arr, int left, int right){
    int pivot = arr[right];
    int l = left;
    int r = right;

    while(l < r){
        while(l<r && arr[l] < pivot){
            l++;
        }
        arr[r] = arr[l]; 

        while(l<r && arr[r] >= pivot){
            r--;
        }
        arr[l] = arr[r];
            
    }
    arr[l] = pivot; 
    return l;
}

template <typename T>
int parition13(T *arr, int left, int right){
    int mid = left + ((right - left) >> 1);
    if(arr[mid] > arr[right]){
        std::swap(arr[mid], arr[right]);
    }
    if(arr[mid] > arr[left]){
        std::swap(arr[mid], arr[left]);
    }
    if(arr[left] > arr[right]){
        std::swap(arr[left], arr[right]);
    }

    int pivot = arr[left];
    int l = left;
    int r = right;

    while(l < r){

        while(l<r && arr[r] >= pivot){
            r--;
        }
        arr[l] = arr[r];
        while(l<r && arr[l] < pivot){
            l++;
        }
        arr[r] = arr[l]; 
    }
    arr[l] = pivot; 
    return l;
}
template <typename T>
void quick_sort11(T *arr, int left, int right){
    if(left < right){
        int middle = parition13(arr, left, right);
        quick_sort11(arr, left, middle-1);
        quick_sort11(arr, middle+1, right);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int arr[8]={22, 7, 3, 1, 3, 5, 6, 4};
    printArr(arr, 0, 7);
    //quick_sort(arr, 0, 7);
    //quick_sort3(arr, 0, 7);
    quick_sort11(arr, 0, 7);
    printArr(arr, 0, 7);
    return 0;
}
