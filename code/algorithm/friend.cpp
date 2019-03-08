/*
 *
 * 两种形式的友元:
 *   - 友元函数：普通函数对一个访问某个类中的私有或保护成员
 *   - 友元类: 类A中的成员函数访问类B中的私有或保护成员
 */

//friend function

#include <iostream>

class A{
public:
    A(int _a):a(_a){
    }
    //friend function
    friend int getA(A& classA);
    
private:
    int a;
};

int getA(A& classA){
    //access private var by object name
    return classA.a;
}

/*
 * 友元类声明在该类中，实现在该类外
 */
class B{
public:
    B(int _b): b(_b){
    }

    // friend class
    friend class C;
private:
    int b;
};

//实现友元类C
class C {
public:
    int getB(B classB){
        return classB.b;    //访问友元类B的私有成员
    }
};


int main(){
    A classA(3);
    std::cout << getA(classA) << std::endl;

    B classB(5);
    C classC;
    std::cout << classC.getB(classB) << std::endl;
    return 0;
}
