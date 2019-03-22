//
// Created by root on 19-3-20.
//

#include <iostream>
#include <memory>
using namespace std;

/*
 *调用shared_ptr类本身的函数时，用.操作符，如sp2.reset();
 *调用shared_ptr内部数据的函数时，用->操作符，如sp2->print();
 *
 * weak_ptr::use_count()查看有多少个shared_ptr共享同一个内部数据
 * weak_ptr::expired判断shared_ptr是否有效，即shared_ptr内部数据是否被释放
 * weak_ptr是否可以监看shared_ptr中的内部数据呢？因为weak_ptr是弱指针，所以不能直接访问，但是可以通过weak_ptr::lock间接访问。
 * weak_ptr::lock返回构造weak_ptr的shared_ptr，当shared_ptr已经被释放时，返回的是空shared_ptr；
 * 因为weak_ptr::lock返回了shared_ptr，而shared_ptr会增加引用计数，进而影响内部数据指针的释放，这也是lock的含义所在
 * 想通过weak_ptr访问shared_ptr中的内部数据，需要先lock，返回一个shared_ptr，
 * 这相当于把weak_ptr“转换”为shared_ptr，然后通过shared_ptr随便访问去吧。
 *
 */

int stdSmartPointer(){
    unique_ptr<int> up1(new int(10));

    std::weak_ptr<int> wp0;
    //weak_ptr::expired判断shared_ptr是否有效，即shared_ptr内部数据是否被释放
    std::cout << "wp0.expired()=" << wp0.expired() << std::endl;

    std::shared_ptr<int> sp1(new int(5));
    std::weak_ptr<int> wp1(sp1);

    std::cout << "*wp1.lock()=" << *wp1.lock() << std::endl;
    std::cout << "sp1.use_count()=" << sp1.use_count() << std::endl;

    std::weak_ptr<int> wp2(wp1);
    std::cout << "*wp2.lock()==" << *wp2.lock() << std::endl;
    std::shared_ptr<int> sp3 = wp2.lock();
    std::cout << "*wp3.use_count()==" << sp3.use_count() << std::endl;

    return 0;
}


//智能指针的使用场景