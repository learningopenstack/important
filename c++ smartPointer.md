### 解决的问题： 内存泄漏
  - 动态申请**堆空间**，**用完之后不归还**
  - C++语言中没有垃圾回收的机制
  - 指针无法控制所指堆空间的生命周期；【指针本身也是一个变量，变量就存在着生命周期】
  
### 智能指针
  - 指针的生命周期结束时，**主动释放堆空间**
  - 一片堆空间最多只能由一个指针标识
  - 杜绝指针运算和指针比较；

### smartPointer设计思想：
  将基本类型指针封装成类对象指针（这个类肯定是个模板，以适应不同基本类型的需求），并在析构函数里编写delete语句删除指针指向的内存空间。
 
### 智能指针的设计方案
  - 通过类模板描述指针的行为
    - 能够定义不同的指针对象
  - 重载指针特征操作符（-> 和 ×)
    - 利用对象模拟原生指针的行为；
    - 对象在生命周期结束时，调用析构函数（在析构函数中释放堆空间，bingo）
  
 **智能指针使用军规：只能用来指向堆空间中的单个对象或者变量；**
 
### C++标准库中的智能指针
  - 头文件 #include <memory>
  - auto_ptr  (C++98）
  - shared_ptr (C++11) 
  - unique_ptr (C++11)
  - weak_ptr

### 注意点
  - 所有智能指针类都有explicit构造函数，以指针为参数：以auto_ptr的类模板原型为
```c++
template <typename T>
class auto_ptr{
  explicit auto_ptr(X* p = 0);
};
```
  因此不能自动将指针转换为智能指针对象，必须显示调用:
```c++
shard_ptr<int> pd;
int *p_reg = new int;
pd = p_reg;    //not allowed

pd = shared_ptr<int>(p_reg);  //allowed
shared_ptr<int> pshared = p_reg;  //not allowed;
shared_ptr<int> pshared(p_reg);   //allowed
```
  - 对三种智能指针都应该避免一点：
    智能指针不能管理非堆内存；

```c++
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
        pthread_mutex_destory(&mutex);
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
        mutex_.Unlock();
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
T* Singleton<T>::value = NULL;

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
            MutexGuard guard(mutex_);
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
```


