#ifndef STACKTP_H_
#define STACKTP_H_
template <class Type>
class Stack
{
    private:
        enum {MAX = 10 };
        Type * items;
        int top;
        int maxSize;
        
    public:
        Stack(int n = 0);
        ~Stack();
        bool isEmpty();
        bool isFull();
        bool push(const Type & item);
        bool pop (Type & item);
        const int size() const { return top; }
};

template <class Type>
Stack<Type>::Stack(int n){
    if(n == 0)
        maxSize = MAX;
    else maxSize = n;
    items = new Type[maxSize];
    top = 0;
}

template <class Type>
Stack<Type>::~Stack(){
    delete[] items;
}
template <class Type>
bool Stack<Type>::isEmpty() {
    return top == 0;
}

template <class Type>
bool Stack<Type>::isFull(){
    return top == maxSize;
}

template <class Type>
bool Stack<Type>::push(const Type & item){
    if(top < maxSize){
        items[top++] = item;
        return true;
    }
    else 
        return false;
}

template <class Type>
bool Stack<Type>::pop(Type & item){
    if(top > 0){
        item = items[--top];
        return true;
    }
    else return false;
}
#endif
