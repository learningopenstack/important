//
// Created by root on 3/6/19.
//

#ifndef CPP_PROJECT_LINK_H
#define CPP_PROJECT_LINK_H

#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void addNode(ListNode* node, int val){
    if(node->next == NULL){
        node->next = new ListNode(val);
        node->next->next = NULL;
        return;
    }

    addNode(node->next, val);
}

ListNode* reverseLink(ListNode* head){
    if (head == NULL){
        return head;
    }
    ListNode* pre = NULL;
    ListNode* cur = head;
    while(cur!= NULL){
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}

void freeLink(ListNode** head){
    if((*head)->next == NULL){
        delete *head;
        *head = NULL;
    }else{
        freeLink(&((*head)->next));
        delete *head;
        *head = NULL;
    }
    return;
}

void printLink(ListNode* head){
    if (head == NULL){
        return;
    }
    if(head->next == NULL){
        std::cout << "node val:" << head << std::endl;
        return;
    }
    std::cout << "node val:" << head << std::endl;
    printLink(head->next);
}

#endif //CPP_PROJECT_LINK_H
