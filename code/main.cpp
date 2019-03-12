#include <iostream>
#include "threadPool/threadpool_test.hpp"
#include "threadPool/task.h"
#include <gtest/gtest.h>

/*
int main() {
    std::cout << "Hello, World!" << std::endl;
    //testPool();

    return 0;
}*/


GTEST_API_ int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}