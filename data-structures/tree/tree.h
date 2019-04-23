#ifndef AVLTREE_H
#define AVLTREE_H
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "../linked-list/linked-list.h"
template <class T>
struct TreeNode {
    T key;
    int height;
    TreeNode * left, * right, * parent;
    TreeNode(T key, TreeNode* parent = NULL, TreeNode* left = NULL, TreeNode* right = NULL):
    key(key), parent(parent), left(left), right(right), height(0) {}
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
    //m: parent of node replacing deleted node
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
    
    TreeNode<T> * search(const T& key, TreeNode<T> * n = NULL) {
        TreeNode<T> * current = n, * prev = NULL;
        if (current == NULL)
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
    
    void insert(const T& key, TreeNode<T> * n = NULL) {
        if (root == NULL) {
            root = new Node(key);
            root->height = 1;
            return;
        }
        Node *current = search(key, n);
        if(current->key < key)
            current->right = new TreeNode<T>(key, current);
        else current->left = new TreeNode<T>(key, current);
    }
    void avl_insert(const T& key, Node *n = NULL) {
        insert(key, n);
        Node *current = search(key, n);
        rebalance(current);
    }
    
    void rebalance(Node *n) {
        Node *parent = n->parent; 
        int leftHeight = n->left == NULL ? 0 : n->left->height;
        int rightHeight = n->right == NULL ? 0 : n->right->height;
        if(leftHeight > rightHeight + 1)
            rebalance_right(n);
        if(rightHeight > leftHeight + 1 )
            rebalance_left(n);
        adjust_height(n);
        if(parent != NULL)
            rebalance(parent);
    }
    
    void rebalance_right(Node *n) {
        Node *m = n->left, *nlr = m->right;
        int leftHeight = m->left == NULL ? 0 : m->left->height;
        int rightHeight = m->right == NULL ? 0 : m->right->height;
        if (rightHeight > leftHeight)
            rotate_left(m);
        rotate_right(n);
        // Adjust height on affected nodes
        adjust_height(n);
        adjust_height(m);
        if (nlr != NULL)
            adjust_height(nlr);
    }
    
    void rebalance_left(Node *n) {
        Node *m = n->right, *nrl = m->left;
        int leftHeight = m->left == NULL ? 0 : m->left->height;
        int rightHeight = m->right == NULL ? 0 : m->right->height;
        if (leftHeight > rightHeight)
            rotate_right(m);
        rotate_left(n);
        // Adjust height on affected nodes
        adjust_height(n);
        adjust_height(m);
        if (nrl != NULL)
            adjust_height(nrl);
    }
    
    void rotate_left(Node *n) {
        Node *parent = n->parent, *y = n->right, *b = y->left;
        
        y->parent = parent;
        if (parent != NULL) {
            // Appropiate child
            if ( y->key < parent->key)
                parent->left = y;
            else
                parent->right = y;
        }
        else root = y;
        n->parent = y;
        y->left = n;
        if (b != NULL) {
            b->parent = n;
        }
        n->right = b;
    }
    void rotate_right(Node *n) {
        Node *parent = n->parent, *y = n->left, *b = y->right;
        
        y->parent = parent;
        if (parent != NULL) {
            // Appropiate child
            if ( y->key < parent->key)
                parent->left = y;
            else
                parent->right = y;
        }
        else root = y;
        n->parent = y;
        y->right = n;
        if (b != NULL) {
            b->parent = n;
        }
        n->left = b;
    }
    
    void adjust_height(Node *n) {
        int leftHeight = n->left == NULL ? 0 : n->left->height;
        int rightHeight = n->right == NULL ? 0 : n->right->height;
        n->height = 1 + std::max(leftHeight, rightHeight);
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
    
    Node* remove(TreeNode<T>* n) {
        Node * parent = n->parent;
        // m: parent of node replacing n 
        Node *m;
        // if n has no right child 
        if(n->right == NULL){
            if(parent != NULL) {
                if(n->left != NULL) { 
                    n->left->parent = parent;
                }
                if(n->key < parent->key)
                    parent->left = n->left;
                else
                    parent->right = n->left;
                m = parent;
            }
            else {
                root = n->left;
                root->parent = NULL;
                m = root;
            }
        }
        // n has a right child
        else {
            Node * x = next(n);
            Node * q = x->parent;
            // if x's parent != n
            if(q != n) {
                // m set to x's parent
                m = q;
                // promote x's right child to q's left
                q->left = x->right;
                if( x->right != NULL)
                    x->right->parent = q;
                // promote x's right child as parent of n's right child 
                x->right = n->right;
                n->right->parent = x;
            }
            // otherwise x's parent == n
            else {
                if (parent == NULL){
                    m = x;
                }
                else {
                    m = parent;
                }
            }
            // x inherits n's left child
            if(n->left != NULL){
                x->left = n->left;
                n->left->parent = x;
            }
            if(parent == NULL)
            {
                root = x;
                root->parent = NULL;
            }
            else {
                //  promote x as parent of p
                if(x->key < parent->key)
                    parent->left = x;
                else
                    parent->right = x;
                x->parent = parent;
            }
        }
        delete n;
        return m;
    }
    
    void avl_remove(Node *n){
        Node *m = remove(n);
        rebalance(m);
    }
};
#endif