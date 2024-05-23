#pragma once
#include <iostream>

template<typename T>
class Node
{
public:
    T data; 
    Node* nextNode;
    Node(T data, Node* nextNode = nullptr)
        : data(data), nextNode(nextNode) {}
};

template<typename T>
class Stack 
{
private:
    Node<T>* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack(); 
    T top() const;
    void push(T data); 
    size_t size() const;
    T pop();
    bool isEmpty() const;      
    void print() const;
};

template<typename T>
Stack<T>::~Stack()
{
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
T Stack<T>::top() const 
{
    if (isEmpty()) throw std::out_of_range("Stack is empty, cannot peek.");
    return topNode->data;
}

template<typename T>
void Stack<T>::push(T data) 
{
    Node<T>* newNode = new Node<T>(data, topNode);
    topNode = newNode;
}


template<typename T>
size_t Stack<T>::size() const 
{
    size_t size = 0;
    Node<T>* current = topNode;
    for (Node<T>* current = topNode; current != nullptr; current = current->nextNode) {
        size++;
    }
    return size;
}

template<typename T>
T Stack<T>::pop() 
{
    if (isEmpty()) throw std::out_of_range("Stack is empty, cannot pop.");
    Node<T>* nodeToDelete = topNode;
    T data = topNode->data;
    topNode = topNode->nextNode;
    delete nodeToDelete;
    return data;
}

template<typename T>
bool Stack<T>::isEmpty() const 
{
    return topNode == nullptr;
}

template<typename T>
void Stack<T>::print() const 
{
    Node<T>* current = topNode;
    for (Node<T>* current = topNode; current; current = current->nextNode)
    {
        std::cout << current->data << " ";
    }

}