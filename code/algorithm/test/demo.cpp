#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "singleton.h"

class Base{
public:
    int get(){
        return a;
    }
    Base(int aa=100):a(aa){
    }
    ~Base(){
    }

private:
    int a;
};

int main(){
    std::vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }

    std::vector<int>::iterator it = v.begin();
    for(;it<v.end();it++){
        std::cout << *it << "=>";
    }
    std::cout << std::endl;
    it = v.begin();
    std::cout << "begin() =" << *it <<std::endl;

    std::vector<int>::iterator it2 = find(v.begin(), v.end(), 5);
    int span = it2 - it;
    std::cout << "span = " << span << "\n begin + span:" << *(v.begin() + span) << std::endl; 
    Singleton<Base> singBase;
    Base b = singBase.getInstance();
    std::cout << b.get() << std::endl;

    std::shared_ptr<Base> b1(new Base());
    //std::shared_ptr<Base> err = new Base(); //explicit;不能隐式转换

    //b2指向的对象b2一个引用者
    std::shared_ptr<Base> b2 = std::make_shared<Base>(1);
    std::cout << "b1 use count: " << b1.use_count() << std::endl;
    std::cout << "b2 use count: " << b2.use_count() << std::endl;

    //b3和b2指向同一个对象，计数值为2
    std::shared_ptr<Base> b3(b2);
    //b4和b2指向同一个对象，计数值为3
    std::shared_ptr<Base> b4(b2);
    std::cout << "b2 use count: " << b2.use_count() << std::endl;
    std::cout << "b3 use count: " << b3.use_count() << std::endl;

    std::weak_ptr<Base> wb(b2);
    std::cout << "b2 use count: " << b2.use_count() << std::endl;

    auto p5 = std::make_shared<Base>();
    p5 = b2;    //给p5赋值使它指向p2指向的对象，会递增p2指向的对象的引用计数，递减p5指向对象的引用计数
                //此时p5指向对象的引用计数为0，被自动销毁
                
    std::unique_ptr<Base> up(new Base());
    //std::unique_ptr<Base> up2 = up; //error;
    std::unique_ptr<Base> up2 = std::move(up);  //ok
}
