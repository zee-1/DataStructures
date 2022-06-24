#include <stack>
#include <queue>
#include <iostream>
#include <initializer_list>



using std::stack;
using std::queue;


#pragma once
template <typename T>
class Stack: public stack<T>{
public:
    T Pop(){
        T temp = stack<T>::top() ;
        stack<T>::pop(); 
        return temp;
    }

    void Push(const T& t){
        stack<T>::push(t);
    }
};

template <typename T>
class Queue:public queue<T>{
public:
    T dequeue(){
        T temp = queue<T>::front();
        queue<T>::pop();
        return temp;
    }

    void enqueue(const T& ele){
        queue<T>::push(ele);
    }
};


// Setting up Binary search tree node
template <typename T>
class BSTnode{
public:
    BSTnode<T> *left,*right;
    T elem;

    BSTnode(){
        left=right=0;
    }
    BSTnode(const T& el,BSTnode* l=0, BSTnode* r=0){elem = el; left=l; right=r;};
};

//? Binary Search tree
template <typename T>
class BST{
    
protected:
public:
    void insert         (const T&);                     // Insert element in an array
    void visit          (BSTnode<T>*);                  // Visit the element and give console outputof the visited node
    void preorder       ();                             // Pre-order traversal of the tree VLR
    void postorder      ();                             // Post-order traversal of the tree LRV
    void inorder        ();                             // In-Order traversal of the tree LVR
    void BreadthFisrt   ();                             // Breadth first traversal of the tree --> simply means first visit the node and then all of its child
                            //:         RECURSIVE APPROACHES
    void inorder_Rec    (BSTnode<T>*);                  
    void preorder_Rec   (BSTnode<T>*);
    void postorder_Rec  (BSTnode<T>*);

    void deletionByMerging   (BSTnode<T>*&);            // Delete the node by merging the subtree with desired position
    void deletionByCopying   (BSTnode<T>*&);            // Delete the node by copying the best suitable node which can be the parent as the current node and further adjustment
    void findAndDeleteCopying(const T&);                // Find the node and delete the node by delete by copying method
    void findAndDeleteMerging(const T&);                // Find the node and delete the node by delete by merging method
                            //:         AVL rotations
    BSTnode<T>* rotate_r (BSTnode<T>*);
    BSTnode<T>* rotate_l (BSTnode<T>*);
    BSTnode<T>* rotate_lr(BSTnode<T>*);
    BSTnode<T>* rotate_rl(BSTnode<T>*);
    BSTnode<T>* backbone (BSTnode<T>*);


    //: Constructors
    BST(){root=0;};
    BST(std::initializer_list<T> l);
    
    BSTnode<T>* root;
};

//;                 Utilities
//---------------------------------------------------------
template <typename T>
BST<T>::BST(std::initializer_list<T> l){
    root=0;

    for(auto i = l.begin(); i!=l.end();++i){
        insert(*i);}
};

template <typename Y>
void BST<Y>::visit(BSTnode<Y>* f){
    std::cout<<f->elem<<" ";
}

template <typename T>
void  BST<T>::insert(const T& el){
    BSTnode<T> *ptr=root;
    BSTnode<T> *prev=0;
    if(!root){
        root = new BSTnode<T>(el);
        return;    
    }
        while(ptr){
            prev =ptr;
            if(el < ptr->elem)
                ptr = (ptr->left);
            else 
                ptr =  ptr->right;
        }
    if(el< prev->elem)
         prev->left  = new BSTnode<T>(el);
    else prev->right = new BSTnode<T>(el);
}
//---------------------------------------------------------
//;                     DELETION
//---------------------------------------------------------


//]             Deletion by merging
template <typename T>
void BST<T>::deletionByMerging(BSTnode<T>*& node){
    BSTnode<T>* t=node;
    if(node){
        if(!node->left)
            node = node->right;
        else if(!node->right)
            node = node->left;
        else{
            t = node->left;
            while(t->right)
                t = t->right;
            t->right = node->right;
            t = node;
            node = node->left;
        }   
    delete t;}
}

//]             Deletion by Copying
template <typename T>
void BST<T>::deletionByCopying(BSTnode<T>*& node){
    BSTnode<T> *prev, *temp=node;
    if(!node->right)
        node = node->left;
    else if(!node->left)
        node = node->right;
    else{
        temp = node->left;
        while(temp->right){
            prev =temp;
            temp =temp->right;
        }
        node->elem = temp->elem;
        if(prev == node)
            prev->left   = temp->left;
        else prev->right = temp->left;    
    }
    delete temp;
}

//]             find and Deletion by merging
template <typename T>
void BST<T>::findAndDeleteMerging(const T& el){
    BSTnode<T>* node =root,*prev=0;
    while(node){
        if(node->elem == el)
            break;
        prev = node;
        if(el> node->elem)
            node = node->right;
        else node = node->left;
    }

    if(node && node->elem ==el){
        if(node == root)
            deletionByMerging(root);
        else if(node == prev->left)
            deletionByMerging(prev->left);
        else deletionByMerging(node->right);
    }
    else if(root)
        std::cout<<"Element not found cannot be deleted"<<std::endl;
    else std::cout<<"Tree is empty"<<std::endl;
}
//---------------------------------------------------------

//;                 Breadth First Traversal

//---------------------------------------------------------
template <typename T>
void BST<T>::BreadthFisrt(){
    Queue<BSTnode<T>*> q;
    BSTnode<T> *ptr = root;
    if(ptr){
        q.enqueue(ptr);
        while(!q.empty()){
            auto s = q.size();
            while(s){
                BSTnode<T>* temp;
                temp =q.front();
                ptr = q.dequeue();
                visit(temp);
                if(ptr->left)
                    q.enqueue(ptr->left);
                if(ptr->right)
                    q.enqueue(ptr->right);
                s--;
            }
            std::cout<<std::endl;
        }
        std::cout<<'\a'<<std::endl;
    }
}
//---------------------------------------------------------
//]                 Depth first Traversal
//[                 Recurrsive approaches
//---------------------------------------------------------
// for calling pass node as root
template <typename T>
void BST<T>::inorder_Rec(BSTnode<T>* Node){
    if(Node){
        inorder_Rec   (Node->left);
            visit     (Node);
        inorder_Rec   (Node->right);
    }
}

template <typename T>
void BST<T>::preorder_Rec(BSTnode<T>* Node){
    if(Node){
        visit           (Node);
        preorder_Rec    (Node->left);
        preorder_Rec    (Node->right);
    }
}

template <typename T>
void BST<T>::postorder_Rec(BSTnode<T>* Node){
    if(Node){
        postorder_Rec(Node->left);
        postorder_Rec(Node->right);
        visit        (Node);
    }
}
//---------------------------------------------------------
//---------------------------------------------------------
//[                 Iterative Approach

template <typename T>
void BST<T>::preorder(){
    BSTnode<T>* temp = root;
    
    Stack<BSTnode<T>*> s;
    if(temp){
        s.push(temp);
        while (!s.empty()){
            temp = s.Pop();
            if(temp->left)  s.Push(temp->left);
            visit(temp);
            if(temp->right) s.Push(temp->right);
        }
    }
}

template <typename T>
void BST<T>::postorder(){
    Stack<BSTnode<T>*> s;
    BSTnode<T> *temp=root,*prev=root;
    while(temp){
        for(;temp->left;temp=temp->left)
            s.Push(temp);
        while( !temp->right || temp->right==prev    ){
            visit(temp);
            prev=temp;
            if(s.empty())
                return;
            temp=s.Pop();
        }
        s.push(temp);
        temp = temp->right;
    }
}

template <typename T>
void BST<T>::inorder(){
    BSTnode<T>* temp =root;
    Stack<BSTnode<T>*> s;

    while(temp){
        //!  Collecting right node then visit node then moving to the left part 
        //!  because the stack pops in reverse order which make is LVR instead RVL
        while(temp){
            if(temp->right)
                s.Push(temp->right);
            s.Push(temp);
            temp = temp->left;
        }
        //!  Visiting all the nodes stored in stack
        temp = s.Pop();
        while(!s.empty() && !temp->right){
            visit(temp);
            temp = s.Pop();
        }
        //! visiting root seperately
        visit(temp);
        if(!s.empty()){
            temp = s.Pop();
        }else temp=0;
    }
}
//---------------------------------------------------------

/*
        44
       /
      18
    /
   17
*/
//----------------------------------------------------------
//;             Rotate Right

template <typename T>
BSTnode<T>* BST<T>::rotate_r(BSTnode<T>* node){
    BSTnode<T>* temp = node->left;
        node->left       = temp->right;
        temp->right      = node;
    return temp;
}

//;             Rotate Left
template <typename T>
BSTnode<T>* BST<T>::rotate_l(BSTnode<T>* node){
    BSTnode<T>* temp = node->right;
    node->      right= temp->left;
    temp->      left = node;
    return temp;
}

//;            Rotate  Right-Left
template <typename T>
BSTnode<T>* BST<T>::rotate_rl(BSTnode<T>* node){
    node->right=rotate_r(node->right);
    return rotate_l(node);
}

//;            Rotate  Left-Right
template <typename T>
BSTnode<T>* BST<T>::rotate_lr(BSTnode<T>* node){
    node->left  = rotate_l(node->left);
    return rotate_r(node); 
}


template <typename T>
BSTnode<T>* BST<T>::backbone(BSTnode<T>* node){
    BSTnode<T> *head=root;
    while (head->left)
        head=head->left;
    BSTnode<T>* temp=root;
    while(temp){
        if(temp->right){
            temp = rotate_l(temp->right);
        }
        else    temp = temp->left;
    }

    return head;
}
//* Practice corner 
//! remember to comment down or clear all the code written below




//simple breadth first
// template <typename T>
// void BST<T>::BreadthFisrt(){
//     Queue<BSTnode<T>*> q;
//     BSTnode<T>* ptr = root;

//     if(ptr){
//         q.enqueue(ptr);
//         while(!q.empty()){
//             ptr = q.dequeue();
//             visit(ptr);
//             if(ptr->left)   ptr=ptr->left;
//             if(ptr->right)  ptr=ptr->right;
//         }
//     }
// }

//breadth first with pretty printing