//
// Created by root on 19-3-11.
//
#include <iostream>

//No.1
void Print(){
    std::cout << "handle empty paras " << std::endl;
}

//No.2
template <typename T, typename... Types>
void Print(const T& firstArg, const Types&... args){
    int num = sizeof...(args);
    std::cout << firstArg << std::endl;
    Print(args...);
}

/*
 *  优势：支持不定参数，更好的递归
 */

/*
 * Print(7.5, "hello", bitset<16>(377), 42)
 * 7.4
 * hello
 * bitset<16>(377)
 * 42
 * handle empty paras  --- call No.1
 */


//No.3
template <typename... Types>
void Print(const Types... args){

}

/*
 * No.2 No.3 可以共存，但是如何调用那个呢？？
 *
 */


//example tuple
template <typename... Values>
class tuple;

template <> class tuple<>{};

template <typename Head, typename... Tail>
class tuple<Head, Tail...>
:private tuple<Tail...>
{
    typedef tuple<Tail...> inherited;
public:
    tuple(){ }
    tuple(Head v, Tail... vtail)
    :m_head(v), inherited(vtail...){
    }

    typename Head::type head(){ return m_head; }
    inherited& tail() { return *this; }

protected:
    Head m_head;
};

//lambda
auto l = [](int x)->bool{

};

