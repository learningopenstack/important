cmake_minimum_required(VERSION 3.13)
project(cpp_project)

set(CMAKE_CXX_STANDARD 14)

#add_executable(cpp_project main.cpp link/link.h sort/fast_sort.cpp sort/merge_sort.cpp smartPointer/smartPointer.h)
add_executable(ppt
        main.cpp
        link/link.h
        threadPool/threadpool_test.hpp
        threadPool/task.h
        threadPool/pool.h
        test/gtest.cpp
        c11-template/template.cpp
        algorithm/test/smartPoint.hpp
        design/factory.h design/factoryTest.hpp smartPointer/stdSmartPointer.hpp design/observer.hpp)

TARGET_LINK_LIBRARIES(ppt pthread)
TARGET_LINK_LIBRARIES(ppt gtest)

