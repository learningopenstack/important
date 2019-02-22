### 虚函数定义
  虚函数的定义是在**基类**中进行的。它是在基类中需要定义为虚函数的成员函数的声明中**冠以关键字virtual**。当基类中的某个成员函数被声明为虚函数后，</br>
  **此虚函数就可以在一个或多个派生类中被重新定义;** </br>
  在**派生类中重新定义**时，**其函数原型，包括返回类型、函数名、参数个数、参数类型以及参数的顺序都必须与基类中的原型完全相同。**</br>

### 用法
  一般虚函数的定义语法如下：</br>
          virtual<函数类型><函数名>(形参表)</br>
           {        函数体            }</br>
   其中，被关键字virtual说明的函数为虚函数。</br>
   **特别要注意的是，虚函数的作用是允许在派生类中对基类的虚函数重新定义，显然它只能用于类的继承层次中。**</br>
   
＊虚函数的使用场景：
  - 首先应考虑成员函数所在的类是否作为一个基类，然后看成员函数在类的继承后有无可能被更改功能，如果希望更改其功能，一般应该把它声明为虚函数。
  - 应考虑对成员函数的调用是通过对象名还是通过基类指针或引用，如果是通过基类指针或引用去访问，则应声明为虚函数。

```c++
//没有使用虚函数的例子
class base{
public:
    void who(){
        std::cout << "this is the class of base" << std::endl;
    }
};

class derive1 : public base {
public:
    void who(){
        std::cout << "this is the class of derive1" << std::endl;
    }
};

class derive2 : public base{
public:
    void who(){
        std::cout << "this is the class of derive2" << std::endl;
    }
};

int main(){
    base obj, *ptr;
    derive1 obj1;
    derive2 obj2;

    ptr = &obj;
    ptr->who();     // this is the class of base

    ptr = &obj1;    //* point to derive1
    ptr->who();     // this is the class of base

    ptr = &obj2;    //* point to derive2
    ptr->who();     //this is the class of base

    obj1.who();     //this is the class of derive1
    obj2.who();     //this is the class of derive2

    return 0;
}

/* 总结：
 *      通过指针引起的普通成员函数调用，仅仅与指针的类型有关，而与指针正指向什么对象无关。
 *      在这种情况下，必须采用显式的方式调用派生类的函数成员。
 *
 *      要调用派生类的函数成员，就需要引入虚函数的概念。这里，只需将基类的who()函数声明为虚函数即可。
 */

 class Base{
 public:
    Base(int x, int y){
        a = x;
        b = y;
    }

    virtual void show(){  //定义虚函数show()
        std::cout << "Base -- a= " << a << "; b= " << b << std::endl;
    }
 private:
    int a,b;
 };

 class Derived : public Base{
 public:
    Derived(int x,  int y, int z): Base(x, y){
        c = z;
    }

    void show(){    //重新定义虚函数show()
        std::cout << "Derived -- c = " << c << std::endl;
    }
  private:
    int c;
 };

int main(){
    Base b(5,10), *pb;
    Derived d(2, 4, 8);

    pb = &b;
    pb->show();     //调用基类Base的show()版本

    pc = &d;
    pc->show();     //调用派生类Derived的show()版本
    return 0;
}
```

#### 虚函数与重载的关系
  - 在一个派生类中重新定义基类的虚函数是函数重载的另一种特殊形式，但它不同于一般的函数重载。
  - 一般的函数重载，只要函数名相同即可，函数的返回类型及所带的参数可以不同。但当重载一个虚函数时，也就是说在派生类中重新定义此虚函数时，要求函数名、返回类型、参数个数、参数类型以及参数的顺序都与基类中的原型完全相同，不能有任何的不同。

```c++
class Base1{
public:
    virtual void Show(){
        std::cout << "Base --" <<std::endl;
    }
};

class Base2{
public:
    void Show(){
        std::cout << "Base2 --" << std::endl;
    }
};

class Derived : public Base1, public Base2{
public:
    void Show(){
        std::cout << "Derived --" << std::endl;
    }
};

int main(){
    Base1 obj1, *ptr1;
    Base2 obj2, *ptr2;

    Derived obj3;

    ptr1 = &obj1;
    ptr1->Show();   //Base --

    ptr2 = &obj2;
    ptr2->Show();   //Base2 --

    ptr1 = &obj3;
    ptr1->Show();   //Derived --

    ptr2 = &obj3;
    ptr2->Show();   //Base2 --
}

/*
 * 派生类Derived中的函数Show()在不同的场合呈现不同的性质。
 *   如相对Base1路径，由于在Base1中的Show()函数前有关键字virtual，所以它是一个虚函数；
 *   若相对于Base2派生路径，在Base2中的Show()函数为一般函数，所以，此时它只是一个重载函数。
 */
```

#### 多继承中的虚函数
```c++
*  若一个派生类，它的多个基类中有公共的基类，在公共基类中定义一个虚函数，则多重派生以后仍可以重新定义虚函数，
 *  也就是说，虚特性是可以传递的。
 */

class Base {
public:
    virtual void who(){     //定义虚函数
        std::cout << "Base --" << std::endl;
    }
};

class Base1 : public Base{
public:
    void who(){
        std::cout << "Base1 --" << std::endl;
    }
};

class Base2 : public Base{
public:
    void who(){
        std::cout << "Base2 --" << std::endl;
    }
};

class Derive : public Base1, public Base2 {
public:
    void who(){
        std::cout << "Derive --"  << std::endl;
    }
};

int main(){
    Base1 *ptr1;
    Base2 *ptr2;

    Derive obj;

    ptr1 = &obj;
    ptr1->who();    //Derive --

    ptr2 = &obj;
    ptr2->who();    //Derive --

}
```
###　图式虚函数
```c++
class A {
public:
    virtual void vfunc1(){
        std::cout << "A vfunc1() == " << std::endl;
    }

    virtual void vfunc2(){
        std::cout << "A vfunc2() == " << std::endl;
    }

    void func1(){
        std::cout << "A func1() == " << std::endl;
    }
    void func2(){
        std::cout << "A func2() ==" << std::endl;
    }
};


class B : public A {
public:
    void vfunc1(){
        std::cout  << " vfunc1 B == " << std::endl;
    }

    void func1(){
        std::cout << "func1() B == " << std::endl;
    }
};

class C : public B{
public:
    void vfunc1(){
        std::cout << "C vfunc1 == " << std::endl;
    }

    void func1(){
        std::cout << "func1() c == " << std::endl;
    }
};
```
![avatar](https://github.com/tianser/work/blob/master/001_dataStruct/pic/vfunction.png)
 
 首先给vptr分配地址，它所占字节数决定对象中最长数据成员的长度。因为3个类的数据成员都是整型，所以VC为vptr分配4个字节。如果有double型的数据，则要分配8个字节。</br>
　从图中可见，对象的起始地址是vptr。它指向vtable，vtable为每个虚函数建立一个指针函数;</br>
  如果只是继承基类的虚函数，则它们调用基类的虚函数，这就是b和c的vtable表中(*vfunc2)( )项所描述的情况。</br>
  如果派生类改写了基类的虚函数，则调用自己的虚函数，这就是b和c的vtable表中(*vfunc1)( )项所描述的情况。</br>
　　
  实函数不是通过地址调用，用带底纹的方框表示，它们由对象的名字支配规律决定。

#### 构造函数和析构函数调用虚函数
  
  在构造函数和析构函数中调用虚函数时，采用静态联编，即它们所调用的虚函数是自己的类或基类中定义的函数，但不是任何在派生类中重定义的虚函数。  
  
