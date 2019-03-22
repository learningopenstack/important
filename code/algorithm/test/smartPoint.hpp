//
// Created by root on 19-3-19.
//
#include <iostream>
#include <memory>

using namespace std;

int testSmartPointerSTD(){
    unique_ptr<int> up1(new int(11));
    //unique_ptr<int> up2 = up1;

    std::cout << "up1=" <<*up1 << std::endl;
    unique_ptr<int> up3 = move(up1);
    std::cout << "up3=" << *up3 << std::endl;

    up3.reset();
    up1.reset();

    shared_ptr<string> sp1(make_shared<string>("nice"));
    shared_ptr<string> sp2 = sp1;

    std::cout << "sp1 use_count =" <<sp1.use_count() << std::endl;
    std::cout << "sp2 use_count =" <<sp2.use_count() << std::endl;

    sp1.reset();
    std::cout << "sp1 use_count=" << sp1.use_count() << std::endl;




    return 0;
}