//
// Created by root on 19-3-6.
//

#ifndef CPP_PROJECT_SMARTPOINTER_H
#define CPP_PROJECT_SMARTPOINTER_H
namespace DTLib {

    template <typename T>
    class SmartPointer{
    protected:
        T *m_pointer;

    public:
        SmartPointer(T *p = NULL){
            m_pointer = p;
        }

        //拷贝构造函数
        SmartPointer(const SmartPointer<T>& obj){
            m_pointer = obj.m_pointer;
            // obj.m_pointer = NULL; 参数是const，所以无法直接将obj.m_pointer指向NULL；
            //去除一个对象的const属性
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        SmartPointer<T>& operator=(const SmartPointer<T>& obj){
            if(this != obj){  //不给自己赋值
                delete m_pointer;
                m_pointer = obj.m_pointer;
                const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            }
            return *this;
        }


        T *operator-> (){
            return m_pointer;
        }

        T&  operator* (){
            return *m_pointer;
        }

        bool isNull(){
            return (m_pointer == NULL);
        }

        T* get(){
            return m_pointer;
        }

        ~SmartPointer(){
            delete m_pointer;
        }
    };

}

#endif //CPP_PROJECT_SMARTPOINTER_H
