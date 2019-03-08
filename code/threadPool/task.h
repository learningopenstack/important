//
// Created by root on 19-3-8.
//

#ifndef CPP_PROJECT_TASK_H
#define CPP_PROJECT_TASK_H

#include <unistd.h>
#include <iostream>
#include <list>

template <typename T>
class SyncQueue{

private:
    std::list<T> _queue;    //缓存队列
    std::mutex   _mutex;    //互斥量，与下面的条件变量结合起来使用

};

class Task{
private:
    int no;
public:
    Task(int n):no(n){
    }

    virtual void run(){
        sleep(no);
        std::cout << "no:" << no << "\t\n";
    }
};

#endif //CPP_PROJECT_TASK_H
