//
// Created by root on 19-3-8.
//
#include "pool.h"

int testPool(){
    ThreadPool tp(2);

    Task t1(1);
    Task t2(2);
    Task t3(3);

    tp.add_task(&t1);
    tp.add_task(&t2);
    tp.add_task(&t3);

    sleep(40);
    return 0;
}