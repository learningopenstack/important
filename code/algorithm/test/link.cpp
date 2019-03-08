#include <iostream>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
}node;

void addNode(node *head, int v){
    if(head == NULL){
        return;
    }

    node *newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL){
        return;
    }
    newNode->value = v;
    newNode->next = NULL;
    
    while(head->next != NULL){
        head = head->next;     
    }
    head->next = newNode; 
}


void destoryLink(node** head){
    if(*head != NULL){
        destoryLink(&((*head)->next) );
        free(*head);
        head = NULL;
    }
}

void Print(node* head){
    while(head != NULL){
        std::cout << head->value << "=>";
        head = head->next;
    }
    std::cout << std::endl;
}


node *oddEvenList(node* head){
   if(head == NULL ){
        return head;
   } 

   node *odd_head = NULL;
   node *even_head = NULL;
   node *odd = NULL;
   node *even = NULL;
   node *current = head;
   
   while(current != NULL){
        if((current->value)%2 == 1){
            if(odd_head){
                odd->next = current;
                odd = odd->next;
            }else{
                odd_head = current;
                odd = current;
            }
        }else{
           if(even_head){
             even->next = current;
             even = even->next;
           }else{
                even_head = current;
                even = current;
           }
        } 
        current = current->next;
   }
   odd->next = even_head; 
   return odd_head;
}

/*  
 * 如何判断一个单链表中有环？
 */
bool isCycle(node *head){
    if(head == NULL || head->next == NULL){
        return true;
    }

    if(head == head->next){
        return true;
    }

    node *slow = head; 
    node *fast = head->next->next;

    while(fast != slow || slow != NULL || fast != NULL ){
       slow = slow->next; 
       if(fast->next != NULL){
            fast = fast->next->next;
       }
    }
    if(fast == slow){
       return true; 
    }
    return false;
} 


node *FindK(node* head, int k){
    node* h = head; 
    node* kNode = head; 
    for(int i=0; i<k-1; i++){
        if(kNode == NULL){
            return NULL;
        }
        kNode = kNode->next;
    }
    while(kNode->next != NULL){
        kNode = kNode->next;
        h = h->next;
    }
    return h;
}

//第k-1个节点
void reverse_from_k(node *k){
   if(k == NULL || k->next == NULL){
        return ; 
   } 

   node *pre = NULL;
   node *current = k->next;
   node *next = NULL;

   while(current != NULL){
        next = current->next;
        current->next = pre;
        pre = current;
        current = next;
   }
   k->next = pre;
}

node *reverse(node *head){
    if(head == NULL || head->next == NULL){
       return head; 
    }
    node *pre = NULL;
    node *current = head;
    node *next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = pre;
        pre = current;
        current = next; 
    }
    return pre;
}

/*
void reverseK(node* k){
   node *pre = NULL;
   if(k->next == NULL){
    return ;
   }
   node *n = k->next;
   node *current = k->next;

   while(n != NULL){
       // 一次只反转一个节点
        n = n->next;
        current->next = pre;
        pre = current;
        current = n;
   }
   k->next = pre;
}

node *reverse(node* head){
   node *pre = NULL;
   node *n = head;
   node *current = head;
   //node *current = head;

   if(head == NULL || head->next == NULL){
        return head;
   }

   while(n != NULL){
       // 一次只反转一个节点
        n = n->next;
        current->next = pre;
        pre = current;
        current = n;
   }
   return pre;
}*/


































int main(){
    node *head = (node*)malloc(sizeof(node));
    if(head == NULL){
        return -1;
    }
    head->value = 0;
    head->next = NULL;

    for(int i=1; i<10; i++){
        addNode(head, i);
    }
    Print(head);

    node* th5 = FindK(head, 5); 
    std::cout << "th5= " << th5->value << std::endl;
    //reverseK(th5);
    reverse_from_k(th5);
    Print(head);

    head = reverse(head);
    std::cout << "print " << std::endl;
    Print(head);

    head = oddEvenList(head);
    Print(head);
    destoryLink(&head);
    return 0;
}

