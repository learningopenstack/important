#include <iostream>
#include "../common/Link.h"

using namespace std;

// 1->2->4
// 1->3->4
// 1->1->2->3->4->4
/*
 * 两个有序链表，进行合并，使得合并之后的链表有序
 */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
   if(l1->next == NULL){
       return l2;
    }
   if(l2->next == NULL){
       return l1;  
   }
   ListNode* newNode;
   if(l1->val > l2->val){
       newNode = l2;
       newNode->next = mergeTwoLists(l1, l2->next);
   }else{
       newNode = l1;
       newNode->next = mergeTwoLists(l1->next, l2);
   }
   return newNode;
}

int main(){
    ListNode* head = new ListNode(1);
    head->next = NULL;
    
    addNode(head, 2);
    addNode(head, 4);


    ListNode* head2 = new ListNode(1);
    head2->next = NULL;
    
    addNode(head2, 3);
    addNode(head2, 4);
    printLink(head);
    printLink(head2);
    std::cout << "Link print ok" << std::endl;

    ListNode* r_head = reverseLink(head);
    printLink(r_head);
    std::cout << "reverse Link print ok" << std::endl;

    ListNode* newLink = mergeTwoLists(r_head, head2);
    printLink(newLink); 

    std::cout << "newLink print ok" << std::endl;


    printLink(head2);

    //freeLink(&r_head);
    freeLink(&head2);
    return 0;
}
