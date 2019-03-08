//
// Created by root on 3/7/19.
//
#include <iostream>

enum{
    DEFAULT_SIZE = 10
};

template <typename T>
class Heap{
public:
    Heap() = default;
    virtual ~Heap() = default;

    virtual void show_heap() const = 0;
    virtual bool insert_heap(const T&) = 0;
    virtual bool remove_heap(T &) = 0;
};

template <typename T>
class MaxHeap : public Heap<T>{
public:
    MaxHeap(int);
    MaxHeap(const T[], const int);
    ~MaxHeap();

public:
    bool insert_heap(const T&);
    bool remove_heap(T &);
    void show_heap() const;
protected:
    void  sift_down(int, int);
    void  sift_up(int);

private:
    T *heap;
    int size;
    int capacity;
};

template <typename T>
MaxHeap<T>::MaxHeap(int sz = DEFAULT_SIZE) {
    capacity = sz > DEFAULT_SIZE? sz : DEFAULT_SIZE;
    heap = new T[capacity];

    assert(heap != NULL);
    size = 0;
}

template <typename T>
MaxHeap<T>::MaxHeap(const T arr[], const int arrSize){
    capacity = arrSize > DEFAULT_SIZE ? arrSize : DEFAULT_SIZE;
    heap = new T[capacity];
    assert(heap != NULL);
    size = arrSize;

    for(int i=0; i<size; i++){
        heap[i] = arr[i];
    }

    int curPos = size/2 - 1;
    while(curPos >=0){
        sift_down(curPos, size - 1);
        --curPos;
    }
}


template <typename T>
MaxHeap<T>::sift_down(int start, int end){
    int i = start;
    int j = i * 2 +1;

    T tmp = heap[i];
    while(j<=end){
        if(j+1 <= end && heap[j] < heap[j+1]){
            j++;
        }
        if(tmp < heap[j])
            heap[i] = heap[j];
        else
            break;
        i = j;
        j = i * 2 + 1;
    }
    heap[i] = tmp;
}


















