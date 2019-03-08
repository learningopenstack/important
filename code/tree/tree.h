#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm> 
#include <stack>
#include <queue>

using namespace std;
typedef struct node{
    char val;
    struct node* l;
    struct node* r;
}Node;


Node* _buildTree(vector<char>& preorder, vector<char>& inorder, int prebegin, int preend, int inbegin, int inend){
    if(prebegin<preend && inbegin < inend){
        Node *node = (Node*)malloc(sizeof(Node));
        vector<char>::iterator mid = find(inorder.begin() + inbegin, inorder.begin()+ inend, preorder[prebegin]);
        int span =mid - inorder.begin() - inbegin;
        node->val = preorder[prebegin];
        //左子树
        node->l = _buildTree(preorder, inorder, prebegin + 1, prebegin + span + 1, inbegin, inbegin+span );
        //右子树
        node->r = _buildTree(preorder, inorder, prebegin + span + 1, preend, inbegin+span + 1 , inend);
        return node;
    } 
        return NULL;
}

void destoryTree(Node** root){
   if(*root){
      destoryTree(&((*root)->l)); 
      destoryTree(&((*root)->r)); 

      free(*root);

      root = NULL;
   } 
}

Node* BuildTree(vector<char>& preorder, vector<char>& inorder){
    return _buildTree(preorder, inorder, 0, preorder.size(), 0, inorder.size() );
}

void preOrderTree(Node* root){
    if (root==NULL){
        return;
    }
    //1、先打印root
    std::cout << "preOrderTree:" << root->val << std::endl;

    //2、打印左子树
    preOrderTree(root->l);
    //3、右子树
    preOrderTree(root->r);

}
void inOrderTree(Node* root){
    if (root==NULL){
        return;
    }
    //1、打印左子树
    inOrderTree(root->l);
    //2、先打印root
    std::cout << " inorderTree: " << root->val << std::endl;
    //3、右子树
    inOrderTree(root->r);
}
void postOrderTree(Node* root){
    if (root==NULL){
        return;
    }
    //1、打印左子树
    postOrderTree(root->l);
    //2、右子树
    postOrderTree(root->r);
    //3、先打印root
    std::cout << "postOrderTree: " << root->val << std::endl;
}

void depthFirstSearch(Node* root){
   std::cout << "depthFirstSearch:" << std::endl;
   stack<Node*> nodeStack;
   nodeStack.push(root);

   Node* node; 

   // n次,压栈2个，出栈1个，将右子树放在栈内
   while(!nodeStack.empty()){
        node = nodeStack.top();
        std::cout << node->val; 
        nodeStack.pop();

        if(node->r){
            nodeStack.push(node->r);
        }
        if(node->l){
            nodeStack.push(node->l);
        }
   }
   std::cout << "\n";
}
void preOrderTree3(Node* root){
    std::cout << "preOrderTree3" << std::endl;
    stack<Node*> nodeStack;
    Node* node = root;
    
    while(!nodeStack.empty() || node){
        if(node){
            std::cout << node->val ;
            nodeStack.push(node);
            node = node->l;
        }else{
            node = nodeStack.top();
            nodeStack.pop(); 
            node = node->r;
        }
    }
}    

void inOrderTree2(Node* root){
    std::cout << "inOrderTree2" << std::endl;
    stack<Node*> nodeStack;
    Node* node = root;
    
    while(!nodeStack.empty() || node){
        while(node){    //先root 和 root的左子树
            nodeStack.push(node);
            node = node->l;
        }

        if(!node && !nodeStack.empty()){
            node = nodeStack.top();
            nodeStack.pop();
            std::cout << node->val;
            node = node->r; //子节点的右子树
        }
    }
    std::cout << "\n";
}
void inOrderTree3(Node* root){
    std::cout << "inOrderTree3" << std::endl;
    stack<Node*> nodeStack;
    Node* node = root;
    
    while(!nodeStack.empty() || node){
        if(node){
            nodeStack.push(node);
            node = node->l;
        }else{
            node = nodeStack.top();
            std::cout << node->val ;
            nodeStack.pop(); 
            node = node->r;
        }
    }
}    

enum Tag {
    leftT, rightT
};

typedef struct{
    enum Tag tag;
    Node* node;
}TagNode;

void postOrderTree2(Node* root){
    std::cout << "postOrderTree2 " << std::endl;
    stack<TagNode> nodeStack;
    Node* node = root;
    TagNode tagnode;

    while(!nodeStack.empty() || node){
        while(node){
            tagnode.node = node;
            tagnode.tag = leftT;
            nodeStack.push(tagnode);
            node = node->l;
        }
        
        //此时到了左子树的leaf节点
        tagnode = nodeStack.top();
        nodeStack.pop();

        if(tagnode.tag == leftT){
            tagnode.tag = rightT;
            nodeStack.push(tagnode);
            node = tagnode.node;
            node = node->r;
        }else{  //此时右子树入栈了，可访问当前节点
            std::cout << tagnode.node->val; 
            node = NULL;
        }
    }
    std::cout << "\n";
}


//宽度优先算法,使用队列
void widthSearch(Node* root){

}
