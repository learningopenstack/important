#ifndef SINGLETON_H
#define SINGLETON_H

#include <pthread.h>

/*****************
 *
 * mutex api的简单封装
 *
 ****************/

class MutexLock{
public:
    MutexLock(){
        pthread_mutex_init(&mutex_, NULL);
    } 

    ~MutexLock(){
        pthread_mutex_destroy(&mutex_);
    }

    void Lock(){
            pthread_mutex_lock(&mutex_);
    }
    
    void UnLock(){
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;

private:
    //not allow copy
    MutexLock(const MutexLock &);
    MutexLock& operator=(const MutexLock &);    
};

class MutexGuard{
public:
    //explicit 防止隐式转换
    explicit MutexGuard(MutexLock &mutex):mutex_(mutex){
        //mutex_ = mutex;
        mutex_.Lock();
    }
    ~MutexGuard(){
        mutex_.UnLock();
    }
private:
    MutexLock &mutex_;  //由于mutexLock不允许拷贝，所以用引用
private:
    //not allow copy
    MutexGuard(const MutexGuard &);
    MutexGuard& operator=(const MutexGuard &);
};


template <typename T>
class Singleton{
public:
    static T& getInstance(){
        if(!value){
            value = new T();
        }
        return *value;
    }
    Singleton(){
    };
    ~Singleton(){
    };
private:
    static T* value;
};

/*
template <typename T>
T* Singleton<T>::value = NULL;
*/

//static T* 为指针类型
template <typename T>
T* Singleton<T>::value = NULL;


/************************
 *
 * 在多线程下就能正常工作了。可能有人会站出来说这种做法每次调用getInstance的时候都会进入临界区，
 * 在频繁调用getInstance的时候会比较影响性能。
 * 为了解决这个问题，DCL写法就被聪明的先驱者发明了
 * double check lock
 */
template <typename T>
class Singleton2{
public:
    Singleton2(){
    }
    ~Singleton2(){
    }

    static T& getInstance(){
        MutexLock guard(mutex_);       
        if(!value){
            value = new T();
        }
        return *value;
    }
private:
    static T* value;
    static MutexLock mutex_;
    
};

template <typename T>
T* Singleton2<T>::value = NULL;

template <typename T>
MutexLock Singleton2<T>::mutex_;


//DCL double check lock
template <typename T>
class Singleton3{
public:
    Singleton3(){
    }
    ~Singleton3(){
    }
    static T& getInstance(){
        if(!value){
            MutexGuard guard(mutex_);
            if(!value){
                value = new T();
            }
        }
        return *value;
    }    
private:
    static T* value;
    static MutexLock mutex_;
};


template <typename T>
T* Singleton3<T>::value = NULL;

template <typename T>
MutexLock Singleton3<T>::mutex_;

//DCL 优化版本 + RCU
template <typename T>
class Singleton4{
public:
    Singleton4(){
    }
    ~Singleton4(){
    }
    static T& getInstance(){
        if(!value){
            MutexGuard guard(l);
            if(!value){
                T* p = static_cast<T*>(operator new(sizeof(T)));
                new (p) T();

                //insert some memory barier
                value = p; //RCU method
            }
        }
        return *value;
    }    
private:
    static T* value;
    static MutexLock l;
};
template <typename T>
T* Singleton4<T>::value = NULL;

template <typename T>
MutexLock Singleton4<T>::l;


//C++11
/*
 * C++11及以后的版本（如C++14）的多线程下，正确。
 * C++11却是线程安全的，这是因为新的C++标准规定了当一个线程正在初始化一个变量的时候，其他线程必须得等到该初始化完成以后才能访问它
 */

template <typename T>
class Singleton5{
public:
    static T& getInstance(){
        static T value;
        return value;
    }

    Singleton5(){
    }
    ~Singleton5(){
    }
};
#endif
