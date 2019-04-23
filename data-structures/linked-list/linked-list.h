#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>
template <class T>
struct Node  {
    T data;
    Node * prev, *next;
    Node(){
        prev = next = 0;
    }
    Node(const T & el, Node * p =0, Node * n = 0)
    {
        data = el; prev = p; next = n;
    }
};


template <class T>
class LinkedList
{
    private:
    int x;
    Node<T> * head, * tail;
    public:
    
    class iterator {
        public:
            typedef T value_type;
            typedef std::forward_iterator_tag  iterator_category;
            typedef int difference_type;
            typedef T* pointer;
            typedef T& reference;
            iterator(Node<T> * ptr): _ptr(ptr) { }
            //Pre-increment
            iterator operator++(){ _ptr = _ptr->next; return *this; } 
            //Post-increment
            iterator operator++(int){ iterator tmp = *this; _ptr = _ptr->next; return tmp; }
            
            reference operator*() { return _ptr->data; }
            pointer operator->() { return _ptr->data;}
            bool operator==(const iterator& rhs) const { return _ptr == rhs._ptr; }
            bool operator!=(const iterator& rhs) const { return _ptr != rhs._ptr; }
            Node<T> * current() { return _ptr; }
        private:
            Node<T> * _ptr;
    };
    
        class riterator{
        public:
            typedef T value_type;
            typedef std::forward_iterator_tag   iterator_category;
            typedef int difference_type;
            typedef T* pointer;
            typedef T& reference;
            riterator(Node<T> * ptr): _ptr(ptr) { }
            //Pre-increment
            riterator operator++(){ _ptr = _ptr->prev; return *this; } 
            riterator operator++(int){ riterator tmp = *this; _ptr = _ptr->prev; return tmp; }
            
            reference operator*() { return _ptr->data; }
            pointer operator->() {  return _ptr->data;}
            bool operator==(const riterator& rhs) const { return _ptr == rhs._ptr; }
            bool operator!=(const riterator& rhs) const { return _ptr != rhs._ptr; }
            Node<T> * current() { return _ptr; }
        private:
            Node<T> * _ptr;
    };
 
 
    LinkedList(int x =0){
        head = tail = 0;
    }

    bool empty(){
        return head == 0;
    }
    void push_front(const T & data){
        if(empty())
        {
            Node<T> * n = new Node<T>(data);
            head = tail = n;
            return;
        }
        Node<T> * n = new Node<T>(data);
        head->prev =n;
        n->next = head;
        head = n;
    }
    
    void push_back(const T & data){
        if(empty()){
            Node<T> * n = new Node<T>(data);
            head = tail = n;
            return;
        }
        Node<T> * n = new Node<T>(data);
        tail->next = n;
        n->prev = tail;
        tail =  n;
    }
    
    void pop_front(){
        if(empty())
            return;
        if(head == tail){
            delete head;
            head = tail = 0;
        }
        else {
            head = head->next;
            delete head->prev;
            head->prev = 0;
        }
    }
    
    void pop_back(){
        if(empty())
            return;
        if(head == tail){
            delete tail;
            head = tail = 0;
        }
        else {
            tail = tail->prev;
            delete tail->next;
            tail->next = 0;
        }
    }
    
    iterator insert(iterator position, const T& val){
        Node<T> * n = new Node<T>(val);
        Node<T> * current = position.current();
        if(current->prev != 0){
            current->prev->next = n;
            n->prev = current->prev;
        }
        n->next = current;
        current->prev = n;
    }
    
    iterator begin(){ 
        iterator begin = head;
        return begin; 
        
    }
    
    riterator rend(){
        riterator end = head->prev; 
        return end;
    }
    
    riterator rbegin(){ 
        riterator begin = tail;
        return begin; 
        
    }
    
    iterator end(){
        if(tail == 0)
            return 0;
        iterator end = tail->next; 
        return end;
    }
    T & front() { return head->el; }
    const T & front()const { return head->el; }
    
    T & back() { return tail->el; }
    const T & back()const { return tail->el; }
    
    ~LinkedList(){
        for(Node<T> * ptr; !empty();){
            ptr = head->next;
            delete head;
            head = ptr;
        }
    }
};
#endif