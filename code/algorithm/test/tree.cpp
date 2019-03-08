#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

typedef struct TreeNode{
    char val;
    struct TreeNode *left;
    struct TreeNode *right;
}TNode;

TNode* buildTree(vector<char>& preorder, int prebegin, int preend, vector<char>& inorder,int inbegin, int inend){
    if(prebegin < preend && inbegin < inend){
        TNode *tNode = (TNode*)malloc(sizeof(TreeNode));
        vector<char>::iterator it = find(inorder.begin()+inbegin, inorder.begin() + inend, preorder[prebegin]);
        int span = it - inorder.begin() - inbegin;
        tNode->val = preorder[prebegin];
        tNode->left = buildTree(preorder, prebegin+1, prebegin+1+span, inorder, inbegin, inbegin+span);
        tNode->right = buildTree(preorder,prebegin+1+span, preend, inorder, inbegin+span+1, inend);
        return tNode;
    }
    return NULL;
}

TNode* buildTree2(vector<char>& pastorder, int pastbegin, int pastend, vector<char>& inorder, int inbegin, int inend){
    if(pastbegin < pastend && inbegin < inend){
        TNode* head = (TNode*)malloc(sizeof(TreeNode));
        vector<char>::iterator it = find(inorder.begin()+inbegin, inorder.begin()+inend, pastorder[pastend-1]);
        int span = it - inorder.begin() - inbegin;
        head->val = pastorder[pastend-1];
        head->left = buildTree2(pastorder, pastbegin, pastbegin+span, inorder, inbegin, inbegin+span);
        head->right = buildTree2(pastorder, pastbegin+span, pastend-1, inorder, inbegin+span+1, inend);
        return head;
    }
    return NULL;
}


void preTree(TNode* head){
    if(head != NULL){
        std::cout << head->val << "=>";
        preTree(head->left);
        preTree(head->right);
    }
}


//广度优先遍历 使用队列
void breadthFirstSearch(TNode* head){
    std::cout << "\nbreadthFirstSearch" << std::endl;
    TNode* tmp = head;
    if(tmp == NULL){
        return;
    }

    queue<TNode*> q;
    q.push(tmp); 

    while(!q.empty()){
        tmp = q.front();
        std::cout << tmp->val << "=>";
        q.pop();

        if(tmp->left != NULL){
            q.push(tmp->left);
        }
        if(tmp->right != NULL){
            q.push(tmp->right);
        }
    }
    std::cout << std::endl;
}

//深度优先遍历 使用栈
void depthFirstSearch(TNode* head){
    std::cout << "\n depthFirstSearch" << std::endl;
    TNode* tmp = head;
    if(tmp == NULL){
        return;
    }
    stack<TNode*> s;
    s.push(tmp);

    while(!s.empty()){
        tmp = s.top();
        std::cout << tmp->val << "=>";
        s.pop();

        if(tmp->right != NULL){
            s.push(tmp->right);
        }
        if(tmp->left != NULL){
            s.push(tmp->left);
        }
    }
    std::cout << std::endl;
}

bool HasSubTreee(TNode* parent, TNode* child){
    if(child == NULL){
        return true;
    }
    if(parent == NULL){
        return false;
    }

    if(parent->val == child->val){
        return HasSubTreee(parent->left, child->left) && HasSubTreee(parent->right, child->right);
    }else{
        return HasSubTreee(parent->left, child) && HasSubTreee(parent->right, child);
    }

}
































int main()
{
    char _pre[6] = {'A', 'B', 'D', 'E', 'C', 'F'};
    char _in[6]  = {'D', 'B', 'E', 'A', 'F', 'C'}; 
    char _post[6] = {'D', 'E', 'B', 'F', 'C', 'A'};
    vector<char> pre(_pre, _pre+6);
    vector<char> in(_in, _in+6);
    vector<char> post(_post, _post+6);
    TNode* head = buildTree(pre, 0, pre.size(), in, 0, in.size());
    TNode* head2 = buildTree2(post, 0, pre.size(), in, 0, in.size());
    preTree(head2);
    preTree(head);
    breadthFirstSearch(head);
    depthFirstSearch(head);
    return 0;
}
