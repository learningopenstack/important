//
// Created by root on 19-3-8.
//

#ifndef CPP_PROJECT_TASK_H
#define CPP_PROJECT_TASK_H

#include <unistd.h>
#include <iostream>
#include <condition_variable>
#include <atomic>
#include <list>

template <typename T>
class SyncQueue{
public:
    SyncQueue(int max_size):_max_size(max_size), _stop(false){
    }

    void Put(const T& x){
        add(x);
    }

    //@TODO
    void Put(T&& x){
        add(std::forward<T>(x));
    }

    void Take(std::list<T>& l){
        std::unique_lock<std::mutex> lock(_mutex);
        _empty.wait(lock, [this]{return _stop || isEmpty(); });

        if(_stop){
            return;
        }
        l = std::move(_queue);
        _full.notify_one();
    }

    void Stop(){
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _stop = true;
        }
        _empty.notify_all();
        _full.notify_all();
    }


    bool Empty(){
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }

    bool Full(){
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.size() == _max_size;
    }

    size_t Size(){
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.size();
    }

private:
    bool isFull() const{
        return _queue.size > _max_size ? true : false;
    }

    bool isEmpty() const{
        return _queue.empty();
    }

    void add(const T& t){
        std::unique_lock<std::mutex> lock(_mutex);
        _full.wait(lock, [this]{return _stop || isFull(); });

        if(_stop){
            return;
        }

        _queue.push_back(t);
        _empty.notify_one();
    }

    void add(const T&& t){
        std::unique_lock<std::mutex> lock(_mutex);
        _full.wait(lock, [this]{return _stop || isFull(); });

        if(_stop){
            return;
        }

        _queue.push_back(std::forward<T>(x));
        _empty.notify_one();
    }

private:
    std::list<T> _queue;    //缓存队列
    std::mutex   _mutex;    //互斥量，与下面的条件变量结合起来使用
    std::condition_variable _empty;
    std::condition_variable _full;
    size_t _max_size;
    std::atomic_bool _stop;
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


//http://ezreal.tech/2017/09/15/implements-thread-pool-using-C++11/
#endif //CPP_PROJECT_TASK_H
