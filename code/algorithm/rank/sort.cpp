#include <iostream>
#include "merge_sort.cpp"
#include "fast_sort.cpp"

void printArray(int *head, int len){
    for(int i=0; i<len; i++){
        std::cout << head[i] << "->";    
    }
    std::cout << "\n";
}

/* 
 * 1.从左开始比较相邻的两个元素x和y，如果 x > y 就交换两者
 * 2.执行比较和交换，直到到达数组的最后一个元素
 * 3.重复执行1和2，直到执行n次，也就是n个最大元素都排到了最后
 * 时间复杂度:O(n^2)
 * 空间复杂度:O(n)
 */
void bubble(int *head, int len){
   for(int i=0; i<len-1; i++){   //time
       for(int j=0;j<len-1-i; j++){ //position
            if (head[j] > head[j+1] ){ 
                int tmp = head[j];
                head[j] = head[j+1];
                head[j+1] = tmp;
            }
       } 
   } 
}

/* 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
 * 再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
 * 重复第二步，直到所有元素均排序完毕。
 */
void select_sort(int *head, int len){
    for(int i=0; i<len; i++){
        for(int j=i+1; j<len; j++){
            if(head[i]>head[j]){
                int tmp = head[i];
                head[i] = head[j];
                head[j] = tmp;
            }
       }
    }
}

//每次遍历找出min, max 
void select_sort2(int *head, int len){
   for(int i=0; i<len/2; i++){
       int max = len - 1 - i; 
       int min = i;
       if(head[min] > head[max]){
            int tmp = head[max];
            head[max] = head[min];
            head[min] = tmp;
       }
       for(int j=i+1; j<len - i; j++){
            if(head[j]<head[min]){
                min = j;
            }
            if(head[j]>head[max]){
                max = j;
            }
       }
       
       //std::cout << "min:" << head[min] << std::endl;
       int tmp = head[i];
       head[i] = head[min];
       head[min] = tmp;

       //std::cout << "max:" << head[max] << std::endl;
       tmp = head[len-1-i];
       head[len-1-i] = head[max];
       head[max] = tmp;
   }
}

/*
 * 将前面的区间（初始区间为1，包含第一个元素）视作有序区间
 * 再将有序区间的后一元素插入到前面有序区间的适当位置。
 * 至有有序区间扩展到原区间的大小
 */
void insert_sort(int *head, int len){
    for(int i=1; i<len; i++){
        for(int j=i; j>0; j--){
            if(head[j]<head[j-1]){
                int tmp = head[j];
                head[j] = head[j-1];
                head[j-1] = tmp;
            }
        }
    }
}


/* 低级排序算法:
 *     冒泡、选择、插入, shell排序
 * 高级排序算法:
 *      堆、归并、排序树、快速
 */
int main(){
    int arr[10] = {10, 8, 98, 28, 33, 45, 32, 25, 12, 3};
    printArray(arr, 10);
    bubble(arr, 10);
    printArray(arr, 10);
    int arr2[10] = {10, 8, 98, 28, 33, 45, 32, 25, 12, 3};
    printArray(arr2, 10);
    select_sort(arr2, 10);
    printArray(arr2, 10);

    std::cout << "select_sort2" << std::endl;
    int arr3[10] = {100, 8, 98, 28, 33, 45, 32, 25, 12, 39};
    printArray(arr3, 10);
    select_sort2(arr3, 10);
    printArray(arr3, 10);

    std::cout << "insert_sort3" << std::endl;
    int arr4[10] = {100, 8, 98, 28, 33, 45, 32, 25, 12, 39};
    printArray(arr4, 10);
    insert_sort(arr4, 10);
    printArray(arr4, 10);
 
    std::cout << "insert_sort4" << std::endl;
    int arr5[10] = {100, 8, 98, 28, 33, 45, 32, 25, 12, 39};
    MergeSort(arr5, 10);

    std::cout << "fast order" << std::endl;
    int arr6[10] = {100, 8, 98, 28, 33, 45, 32, 25, 12, 39};
    quickSort(arr6, 0, 9);
    printArray(arr6, 10);
}
