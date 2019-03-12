//
// Created by root on 19-3-11.
//

#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

atomic_int total{0};

void func(int){
    for(int i=0; i<100; i++){
        total +=i;
    }
}

int main(){
    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();
    std::cout << total << std::endl;
    return 0;
}