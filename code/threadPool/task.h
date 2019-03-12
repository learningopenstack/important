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
        return _queue.size() > _max_size ? true : false;
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

        _queue.push_back(std::forward<T>(t));
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

const int MaxTaskCount = 100;
class ThreadPool{
public:
    using Task = std::function<void()>;
    ThreadPool(int threads_num = std::thread::hardware_concurrency()):_queue(MaxTaskCount){
        Start(threads_num);
    }

    ~ThreadPool(){
        Stop();
    }

    void Stop(){
        //保证多线程情况下只调用一次StopThreadGroup
        std::call_once(_flag, [this]{StopThreadGroup();});
    }

    void AddTask(const Task& task){
        _queue.Put(task);
    }

    void AddTask(Task&& task){
        _queue.Put(task);
    }

private:
    void Start(int threads_num){
        _stop = false;
        for(int i=0; i<threads_num; i++){
            _thread_group.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
        }
    }

    void RunInThread() {
        while(!_stop){
            //Task t;
            std::list<Task> t;
            _queue.Take(t);
            if(!_stop){
                for(auto _t : t){
                    _t();
                }
            }
        }
    }

    void StopThreadGroup(){
        _queue.Stop();
        _stop = true;
        for(auto thread : _thread_group){
            if(thread){
                thread->join();
            }
        }
        _thread_group.clear();
    }

private:
    std::list<std::shared_ptr<std::thread>> _thread_group;
    SyncQueue<Task> _queue;
    std::atomic_bool _stop;
    std::once_flag   _flag;
};


/*
 *
int main()
{
	ThreadPool pool;

    //修改此处即可应用在自己的项目中
	std::thread t1([&pool]
	{
		for (int i = 0; i < 10; ++i)
		{
			auto t_id = std::this_thread::get_id();
			pool.AddTask([t_id]
			{
				std::cout << "同步线程1的线程ID：" << t_id << std::endl;
			});
		}
	});
	std::this_thread::sleep_for(std::chrono::seconds(2));
	pool.Stop();
	t1.join();
    //修改此处即可应用在自己的项目中

	return 0;
}
*/


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
