//
// Created by root on 19-3-8.
//

#ifndef CPP_PROJECT_POOL_H
#define CPP_PROJECT_POOL_H
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include "task.h"

class Thread{
private:
    std::thread _thread;
    bool _isfree;
    Task *_task;
    std::mutex _lock;

public:
    Thread():_isfree(true), _task(nullptr){
        //@paras
        //@1 function pointer
        //@2
        _thread = std::thread(&Thread::run, this);
        _thread.detach();
    }

    bool isfree(){
        return _isfree;
    }

    void set_task(Task *task){
        if(_isfree){
            _lock.lock();
            _task = task;
            _isfree = false;
            _lock.unlock();
        }
    }

    void run(){
        while(true){
            if(_task){
                _lock.lock();
                _isfree = true;
                _task->run();
                _task = nullptr;
                _lock.unlock();
            }
        }
    }
};

class ThreadPool2{
private:
    std::queue<Task *> task_queue;
    std::vector<Thread*> _pool;
    std::mutex _lock;
public:
    ThreadPool2(int n=10){
        while(n--){
            Thread *t = new Thread();
            _pool.push_back(t);
        }
        std::thread main_thread(&ThreadPool2::run, this);
        main_thread.detach();
    }

    ~ThreadPool2(){
        for(int i=0; i<_pool.size(); i++){
            delete _pool[i];
        }
    }

    void add_task(Task *task){
        _lock.lock();
        task_queue.push(task);
        _lock.unlock();
    }

    void run(){
        while(true){
            _lock.lock();
            if(task_queue.empty()){
                continue;
            }

            for(int i=0; i< _pool.size(); i++){
                if(_pool[i]->isfree()){
                    _pool[i]->set_task(task_queue.front());
                    task_queue.pop();
                    break;
                }
            }
            _lock.unlock();
        }
    }
};



#endif //CPP_PROJECT_POOL_H
