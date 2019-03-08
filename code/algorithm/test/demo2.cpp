
class FooBase{
public:
    virtual void foo();
};

class FooImpl : public FooBase{
public:
    void foo() override;
};

class FooMock : public FooBase{
public:
    void foo() override;
};

class Bar{
public:
    Bar(): foo_(new FooImpl()){
    }
    void func(){
        foo_ -> foo();
    }

private:
    FooBase* foo_
};


/*
 * 当我们写单元测试时，如何能够保证当 Bar::func 被调用时，访问的是 FooMock::foo，而不是 FooImpl::foo？
 * 我们可以借用 Factory 的思想。对象的构建不是直接通过 new，而是通过一个函数来完成。
 */
class FooFactory{
public:
    virtual FooBase* CreateFoo();
};

class Bar{
public:
    Bar(FooFactory *ff):foo_(ff->CreateFoo()){
         
    }
    
    void func(){
        foo_->foo();
    }
private:
    FooBase *foo_
};

/*
 * 此时，单元测试代码可以继承 FooFactory，并在 CreateFoo 的时候，返回一个 FooMock，
 * 并在创建 Bar 的时候，把我们实现的 FooFactory 作为参数传给 Bar。
 * 
 */
class Solution {
    public:
    void flatten(TreeNode* root) {
        if(root == NULL){
            return;
        }        

        stack<TreeNode*> s;
        s.push(root);
        TreeNode *tmp = root;
        TreeNode *current = NULL;

        while(s.empty()){
           current = s.top(); 
           if(current != root){
               tmp->next = current;
           }
           s.pop();

           if(root->left != NULL){
                s.push(current->left);
           }
           if(root->right != NULL){
                s.push(current->right)
           }
           
        }
    }
};

/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     ListNode *next;
 *      *     ListNode(int x) : val(x), next(NULL) {}
 *       * };
 */
class Solution {
    public:
    ListNode* deleteDuplicates(ListNode* head) {
            if(head == NULL || head->next == NULL){
                        return head;
            }
            ListNode *current = head;
            while(current && current->next){
                if(current->val == current->next->val){
                    current = current->next->next;
                }else{
                    current = current->next;  
                }
            } 
        }
};
