

#ifndef LIST_H
#define LIST_H




// Everytime you work with Append or Push function, there is a corner case.
// When a NULL Node is passed you have to return a Node that points to the given value.
// There are two ways to achieve this:
// 1. Receive the double pointer as an argument.
// 2. Return the new Node.



 #define nullptr  NULL 
//#include <stdio.h>

#ifdef  (__LINUX__)
   #include <pthread.h>
#endif

template<typename T>
struct Node{
    T data;
    Node* next;

    #ifdef  (__LINUX__)
    pthread_mutex_t m_mutex;
    #endif 

};


void * New(size_t sz)
{       
    void *ret;
    do {
         std::cout<<"malloc"<<std::endl;
       }while(!(ret=malloc(sz)));

   return ret;
}


Node *createNode()
{
     Node *newnode=new Node();
     pthread_mutex_init(&newnode->m_mutex,NULL);
}




void printList( Node *head){
    while(head){
        std::cout<<head->data<<" ";
        head = head->next;
    }
    std::cout<<std::endl;
}






template<typename T>
void push( Node** headref, T &x){
    Node* head = *headref;
    Node* newNode = new createNode();
    pthread_mutex_lock(&newNode->m_mutex);
    newNode->data = x;
    newNode->next = head;
    *headref = newNode;
    pthread_mutex_unlock(&newNode->m_mutex);


}

template<typename T>
void pushAfter(Node* prev_Node, T data){
    Node* newNode= new createNode();
    pthread_mutex_lock(&newNode->m_mutex);
    newNode->data =data;
    newNode->next = prev_Node->next;
    prev_Node->next = newNode;
    pthread_mutex_unlock(&newNode->m_mutex);
}

template<typename T> 
void append( Node** headref, T x){
    Node* head = *headref;
    if(head==nullptr){
        Node* newNode = new createNode();
        pthread_mutex_lock(&newNode->m_mutex);
        newNode->data = x;
        newNode->next = nullptr;
        *headref= newNode;
        pthread_mutex_unlock(&newNode->m_mutex);
        return;
    }
    while(head->next){
        head= head->next;
    }
    Node *temp = new createNode();
    pthread_mutex_lock(&temp->m_mutex);
    head->next = temp;
    temp->data = x;
    pthread_mutex_unlock(&temp->m_mutex);
}


#endif // LIST_H
