#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>
#include <string>
#include <exception>

template<typename T>
class stack
{
    private:
        const int MAX_SIZE = 20;
        T * data;
        int size;
    public:

        stack(/* args */);
        ~stack();
        void push(T val);
        void pop();
        void pop_two();
        T top();
        bool empty();
};

#endif

template<typename T>
stack<T>::stack(/* args */) {
    data = new T[MAX_SIZE];
    size = 0;
}

template<typename T>
stack<T>::~stack() {
    delete[] data;
}

template<typename T>
void stack<T>::push(T val) {

    /* code */
    if (size < MAX_SIZE) {
        data[size] = val;
        size++;
    }
    else
    {
        throw std::overflow_error("Called push on full stack.");
    }
        
    
}

template<typename T>
void stack<T>::pop() {

    /* code */
    if (size >= 1) {
    
        size--;
    }
    else
    {
        throw std::out_of_range("Called pop on empty stack.");
    }

}

template<typename T>
void stack<T>::pop_two() {

    /* code */
    if (size >= 2) {

        size -= 2;
    }
    else if (size == 1)
    {
        throw std::out_of_range("Called pop_two on a stack of size 1.");
    }
    else {
        throw std::out_of_range("Called pop_two on empty stack.");
    }
}

template<typename T>
T stack<T>::top() {
    T val;
    /* code */
    if (size > 0) {
    
        val = data[size-1];
    }
    else
    {
        throw std::underflow_error("Called top on empty stack.");
    }
    return val;
}

template<typename T>
bool stack<T>::empty() {
    return true ? size == 0 : false;
}

