//
// Created by root on 19-3-20.
//

#ifndef CPP_PROJECT_OBSERVER_H
#define CPP_PROJECT_OBSERVER_H

#include <list>
#include <algorithm>
#include <iostream>

class Observer;

//subject interface
class Subject{
public:
    Subject():m_issue(0){
    }

    void Attach(Observer *o);
    void Detach(Observer *o);
    void Notify();
    virtual void Issue() = 0;
    bool setIssue(){
        m_issue = !m_issue;
        return m_issue;
    }

    void setIssue(bool issue){
        m_issue = issue;
    }

    bool GetIssue(){
        return m_issue;
    }

    ~Subject(){
        for(auto it = m_list.begin(), it2 = m_list.end(); it != it2;){
            auto tmp = it;
            it++;
            m_list.erase(tmp);
        }

        m_list.clear();
    }

private:
    bool m_issue;
    std::list<Observer*> m_list;
};

//observer interface
class Observer{
public:
    Observer(): m_receive(0){
    }

    virtual void Update() = 0;
    virtual void Show() = 0;

    bool getReceive(){
        return m_receive;
    }

    void setReceive(bool receive){
        m_receive = receive;
    }

private:
    bool m_receive;
};

class ConcreteSubject : public Subject{
public:
    ConcreteSubject(){
    }

    void Issue();
};

class SubObserver : public Observer{
public:
    void Update();
    void ShowMessage();
};


/* 订阅报纸 */
void Subject::Attach(Observer *o)
{
    m_list.push_back(o);
}


/* 取消订阅 */
void Subject::Detach(Observer *o)
{
    std::list<Observer*>::iterator iter;
    iter = std::find(m_list.begin(),m_list.end(),o);
    while(iter != m_list.end())
    {
        m_list.erase(iter);
    }
}


/*通知更新*/
void Subject::Notify()
{
    std::list<Observer*>::iterator iter=m_list.begin();
    for ( ; iter != m_list.end(); iter++)
    {
        (*iter)->Update();
    }
}


/* 更改状态 */
void ConcreteSubject::Issue()
{
    bool issue = this->setIssue();

    if ( issue )
    {
        std::cout << "Magazine is Issued!\n" << std::endl;
        this->Notify();
        setIssue(false);
    }

}


/*订阅者更新*/
void SubObserver::Update()
{
    this->setReceive(true);
    this->Show();
    this->setReceive(false);
}


#endif //CPP_PROJECT_OBSERVER_H
