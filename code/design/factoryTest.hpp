//
// Created by root on 19-3-19.
//


#include <iostream>
//#include <functional>
#include <string>
#include "factory.h"

int factoryTest(){
    Factory *pFactory = new Factory();

    //BENZ
    ICar *pCar = pFactory->Create(Factory::BENZ);
    std::cout << pCar->Name() << std::endl;

    if(pCar){
        delete []pCar;
        pCar = nullptr;
    }

    //BMW
    ICar *pCar2 = pFactory->Create(Factory::BWM);
    std::cout << pCar2->Name() << std::endl;
    if(pCar2){
        delete []pCar2;
        pCar2 = nullptr;
    }
}


//工厂方法模式
int factoryTest2(){
    Factory2 *pBenzF = new BenzFactory2();
    Factory2 *pBMWF = new BMWFactory2();
    ICar2* pBenz = pBenzF->create();
    ICar2* pBMW  = pBMWF->create();

    std::cout << "pBenz->Name=" << pBenz->Name() << std::endl;
    std::cout << "pBMW->Name =" << pBMW->Name()  << std::endl;

    if(pBenzF){
        delete pBenzF;
        pBenzF = nullptr;
    }
    if(pBMWF){
        delete pBMWF;
        pBMWF = nullptr;
    }
    if(pBenz){
        delete pBenz;
        pBenz = nullptr;
    }
    if(pBMW){
        delete pBMW;
        pBMW = nullptr;
    }
    size_t hcode1 = hash<string>()("kiwi");
    std::cout << "hcode1 = " << hcode1 << std::endl;

    return 0;
}