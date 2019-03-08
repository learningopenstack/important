#include <iostream>
#include "smartPointer.h"
#include "smartPointerTest.h"

using namespace DTLib;


int main(){
    SmartPointer<Test> sp = new Test();

    SmartPronter<Test> nsp;

    nsp = sp;

    // sp 为空； nsp 不为空
    std::cout << sp.isNull() << std::endl;
    std::cout << nsp.isNull() << std::endl;
   return 0;
}
