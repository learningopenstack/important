
#ifndef  SMARTPOINTERTEST_H
#define SMARTPOINTERTEST_H

#include <iostream>>
class Test{
public:
    Test(){
        std::cout << "Test()" << std::endl;
    }

    ~Test(){
        std::cout << "~Test()" << std::endl;
    }

};

#endif 

