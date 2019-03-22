#include <iostream>
#include "threadPool/threadpool_test.hpp"
#include "threadPool/task.h"
#include <gtest/gtest.h>
#include "algorithm/test/smartPoint.hpp"
#include "design/factoryTest.hpp"
#include "design/observer.hpp"
#include "smartPointer/stdSmartPointer.hpp"


int main() {
    std::cout << "Hello, World!" << std::endl;
    //testPool();
    //testSmartPointerSTD();
    //factoryTest();
    factoryTest2();
    stdSmartPointer();
    return 0;
}


/*
GTEST_API_ int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 */