#ifndef AVLTREE_H
#define AVLTREE_H
#include <cstdio>
#include <iostream>
#include "../linked-list/linked-list.h"
template <class T>
struct TreeNode {
    T key;
    TreeNode * left, * right, * parent;
    TreeNode(T key, TreeNode* parent = NULL, TreeNode* left = NULL, TreeNode* right = NULL):
    key(key), parent(parent), left(left), right(right) {}
};

template <class T>
class AVLTree
{
    protected:
    LinkedList<TreeNode<T> *> breadthFirstTraversal() {
        LinkedList<TreeNode<T> *> tStack(1), vStack(2);
        TreeNode<T> * current = root;
        tStack.push_front(current);
        while(!tStack.empty()) {
            // visit
            current = *tStack.begin();
            tStack.pop_front(); 
            vStack.push_back(current);
            
            if(current->right != NULL)
                tStack.push_front(current->right);
            if(current->left != NULL)
                tStack.push_front(current->left);
        }
        return vStack;
    }
    public:
    typedef TreeNode<T> Node;
    TreeNode<T> * root;
    AVLTree() {
       root = NULL;
    }
    
    ~AVLTree() {
        if(root == NULL) return;
        LinkedList<TreeNode<T>*> stack = breadthFirstTraversal();
        
        for(typename LinkedList<TreeNode<T>*>::iterator ptr = stack.begin(); ptr != stack.end(); ptr++ )
        {
            delete *ptr; 
        }
    }
    
    TreeNode<T> * search(const T& key) {
        TreeNode<T> * current, * prev = NULL;
        current = root;
        while(current != NULL) {
            prev = current;
            if(current->key == key)
                return current;
            if(key < current->key)
                current = current->left;
            else  
                current = current->right;
        }
        return prev;
    }
    
    void insert(const T& key) {
        if (root == NULL) {
            root = new TreeNode<T> (key);
            return;
        }
        TreeNode<T> * current = search(key);
        if(current->key <= key)
            current->right = new TreeNode<T>(key, current);
        else current->left = new TreeNode<T>(key, current);
    }
    
    const TreeNode<T> * next(const TreeNode<T> * n) {
        if(n->right != NULL)
            return leftDescendant(n->right);
        return rightAncestor(n);
    }
    
    TreeNode<T> * next(TreeNode<T> * n) {
        if(n->right != NULL)
            return leftDescendant(n->right);
        return rightAncestor(n);
    }
    
    const TreeNode<T> * leftDescendant(const TreeNode<T> * n) {
        const TreeNode<T> * current = n;
        while(current->left != NULL) {
           current = current->left; 
        }
        return current;
    }
    
    const TreeNode<T> * rightAncestor(const TreeNode<T> * n) {
        const TreeNode<T> * current = n->parent;
        while( current != NULL && n->key > current->key) {
            current = current->parent;
        }
        return current;
    }
    
    TreeNode<T> * leftDescendant(TreeNode<T> * n) {
        TreeNode<T> * current = n;
        while(current->left != NULL) {
           current = current->left; 
        }
        return current;
    }
    
    TreeNode<T> * rightAncestor(TreeNode<T> * n) {
        TreeNode<T> * current = n->parent;
        while( current != NULL && n->key > current->key) {
            current = current->parent;
        }
        return current;
    }
    
    const LinkedList<const TreeNode<T>*> range(T min, T max) {
        LinkedList<const TreeNode<T>*> list;
        const TreeNode<T> * current = search(min);
        while( current != NULL && current->key <= max) {
            if(current->key >= min)
                list.push_back(current);
            current = next(current);
        }
        return list;
    }
    
    void remove(TreeNode<T>* n) {
        Node * parent = n->parent;
        // if n has no right child 
        if(n->right == NULL){
            if(parent != NULL) {
                if(n->left != NULL)
                    n->left->parent = parent;
                parent->right = n->left;
            }
            else {
                root = n->left;
            }
        }
        else {
            Node * x = next(n);
           
            Node * q = x->parent;
            // promote x's right child
            if(q != n) {
               q->left = x->right;
               if( x->right != NULL)
                    x->right->parent = q;
            }
            // replace n by x
            if(parent != NULL){
                if(x->key < parent->key)
                    parent->left = x;
                else
                    parent->right = x;
            }
            x->parent = parent;
            x->right = n->right;
            n->right->parent = x;
            if(n->left != NULL){
                x->left = n->left;
                n->left->parent = x;
            }
            if(parent == NULL)
                root = x;
        }
        delete n;
    }
};
#endif