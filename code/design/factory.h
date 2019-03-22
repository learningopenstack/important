//
// Created by root on 19-3-19.
//

#ifndef CPP_PROJECT_FACTORY_H
#define CPP_PROJECT_FACTORY_H

#include <string>

/*
 * 简单工厂模式
 * start
 */

//ICar
class ICar{
public:
    virtual std::string Name() = 0;
    virtual ~ICar(){
    }
};

//
class BenzCar :public ICar{
public:
    std::string Name() override {
        return "BenzCar";
    }
};

class BMWCar : public ICar{
public:
    std::string Name() override {
        return "BMWCar";
    }
};

class Factory{
public:
    enum CAR{
        BENZ,
        BWM
    };

    //Create Car
    ICar* Create(CAR type){
        ICar *pCar = nullptr;
        switch(type){
            case CAR::BENZ:
                pCar = new BenzCar();
                break;
            case CAR::BWM:
                pCar = new BMWCar();
                break;
            default:
                break;
        }
        return pCar;
    }
};

/*
 * 简单工厂模式
 *  end 
 */


/*
 * 工厂方法模式
 *
 */

//ICar
class ICar2{
public:
    virtual std::string Name() = 0;
    virtual ~ICar2(){
    }
};

//
class BenzCar2 :public ICar2{
public:
    std::string Name() override {
        return "BenzCar2";
    }
};

class BMWCar2 : public ICar2{
public:
    std::string Name() override {
        return "BMWCar2";
    }
};

class Factory2 {
public:
    virtual ICar2* create() = 0;
    void flush();
    virtual ~Factory2(){
    }
};

class BenzFactory2 : public Factory2{
public:
    ICar2* create(){
        return new BenzCar2();
    }
};

class BMWFactory2 : public Factory2{
public:
    ICar2* create(){
        return new BMWCar2();
    }
};




#endif //CPP_PROJECT_FACTORY_H
