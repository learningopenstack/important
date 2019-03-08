#include <iostream>
#include <queue>

//pop(), push(), top(), empty()
class QueueStack{
    bool empty(){
        return q1.empty() && q2.empty();
    }

    bool push(int x){
       if(q1.empty()){
            q1.push(x);
            while(!q2.empty()){
                q1.push(q2.front());
                q2.pop();
            }
       }else{
            q2.push(x);
            while(!q1.empty()){
                q2.push(q1.front());
                q1.pop();
            }
       } 
    }

    //remove the element on top of stack
    void pop(){
        if(q1.empty()){
           q2.pop(); 
        }else{
            q1.pop();
        }
    }

    // get the top element
    int top(){
       if(q1.empty()){
            return q2.front();
       }else{
            return q1.front();
       } 
    }

    queue<int> q1;
    queue<int> q2;    
}
