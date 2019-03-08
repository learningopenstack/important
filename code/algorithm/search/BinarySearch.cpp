#include <iostream>
#include <vector>

using namespace std;

/*
 * 二分查找
 * 前提是 数组有序
 * 递归方式
 */
int binary_search(int *head, int target, int start, int end){
    if(target < head[start] || target > head[end] || start > end){
        return -1;
    }
    int middle = (end-start)/2 + start;
    //int middle = start + 1/2 * (end - start)
    if (head[middle] > target){
        return binary_search(head, target, start, middle - 1);
    }else if(head[middle] < target){
        return  binary_search(head, target, middle + 1, end);
    }else{ //head[middle] == target
        return middle; 
    }
}

//拆值查找
int binary_searchN(int *head, int target, int start,  int end){
   if(target < head[start] || target > head[end] || start > end){
        return -1;
   }

   // int middle = start + [(target - head[start])/(head[end] - head(start) ]* (end - strt)
   int middle = start + (target - head[start])/(head[end] - head[start]) * (end - start);
   if (head[middle] == target){
        return middle;
   }else if(head[middle] > target){
        return binary_searchN(head, target, start, middle -1);
   }else{
        return binary_searchN(head, target, middle+1, end);
   }
}

int binary_search2(int *head, int target, int start, int end){
   int middle = 0;
   while(start <= end) {
        middle = (end - start)/2 + start;
        if(head[middle] > target){
            end = middle - 1;
        }else if (head[middle] < target){
            start = middle + 1;
        }else{
            return middle;
        }
   } 
   return -1;
}

//FibonacciSearch
class FibonacciSearch{
private:
    int MAXSIZE = 20;
    int fibonacciArray[20];
       

public:
    //fibonacci array
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
    FibonacciSearch(){
        fibonacciArray[0] = 1;
        fibonacciArray[1] = 1;
      
        for(int i=2; i<MAXSIZE; i++){
            fibonacciArray[i] = fibonacciArray[i-1] + fibonacciArray[i-2];
        } 
    }

    //params：@head 待查找数列的头指针
    //params: @size 待查找数列的元素个数
    int fibonacciSearch(vector<int>& v, int target){
        int k = 0;
        int originSize = v.size();
        vector<int>::iterator originEnd= v.end();
        

        //找到有序表中元素个数在斐波那契数列中最接近的最大数列值 
        while(v.size() > fibonacciArray[k]){
            k++; 
        }

        //将待查找的数组个数不全到【斐波那契数列中最接近的最大数列值】
        for(int i=v.size(); i<fibonacciArray[k]; i++){
            v.push_back(v[v.size()-1]); 
        }
        
        vector<int>::iterator start= v.begin();
        vector<int>::iterator middle= v.begin();
        vector<int>::iterator end= v.end();
        while(start != end){
            //middle 也是一个iterator
            middle = start + fibonacciArray[k-1] - 1; 

            if(*middle == target){
                if(middle <= originEnd ){
                    return originSize - (originEnd - middle);
                }else{
                    return originSize - 1 ;
                }
            }else if(*middle > target){
               end = middle-1; 
               k = k - 1;
            }else{
                start = middle + 1;
                k = k - 2;
            }
        }
        return -1;
    }
};



int main(){
    int array[7] = {1, 3, 7, 8, 10, 18, 19};
    std::cout << "result:" << binary_search(array, 19, 0, 6) << std::endl;
    std::cout << "result:" << binary_search(array, 3, 0, 6) << std::endl;
    std::cout << "result:" << binary_search(array, 3, 0, 6) << std::endl;
    std::cout << "result:" << binary_search(array, 6, 0, 6) << std::endl;

    std::cout << "result:" << binary_search2(array, 19, 0, 6) << std::endl;
    std::cout << "result:" << binary_search2(array, 3, 0, 6) << std::endl;
    std::cout << "result:" << binary_search2(array, 3, 0, 6) << std::endl;
    std::cout << "result:" << binary_search2(array, 6, 0, 6) << std::endl;

    std::cout << "result:" << binary_searchN(array, 19, 0, 6) << std::endl;
    std::cout << "result:" << binary_searchN(array, 3, 0, 6) << std::endl;
    std::cout << "result:" << binary_searchN(array, 3, 0, 6) << std::endl;
    std::cout << "result:" << binary_searchN(array, 6, 0, 6) << std::endl;

    vector<int> v = {1, 3, 4, 8, 10, 19 ,22, 45};
    FibonacciSearch fs;

    std::cout << "\nindex:" <<  fs.fibonacciSearch(v, 45) << std::endl;
}

