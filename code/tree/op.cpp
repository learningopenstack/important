#include <iostream>
#include "tree.h"

int main(){
   char pre[10] = {'A', 'B', 'D', 'E', 'F', 'C', 'G', 'H', 'I', 'J'}; 
   char in[10] = {'E', 'D', 'F', 'B', 'A', 'G', 'C', 'I', 'H', 'J'}; 
    
   std::vector<char> preOrder(pre, pre + 10);
   std::vector<char> inOrder(in, in + 10);
   Node* root = BuildTree(preOrder, inOrder);
   preOrderTree(root); 
   inOrderTree(root);
   postOrderTree(root);
   depthFirstSearch(root);
   inOrderTree2(root);

   postOrderTree2(root);
   destoryTree(&root);

   return 0;
}
