#ifndef LINKEDLIST_HPP
#define	LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head;
    int length;
public:

    LinkedList();
    LinkedList(const LinkedList<T>& ll);
    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data);
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};

template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */

template <class T>
LinkedList<T>::LinkedList()
{
    head = new Node<T>;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll)
{
   head = new Node<T>;
   *this =ll;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs){

    if (this != &rhs){
        clear();

        const Node<T>* r = rhs.first();
        Node<T>* p = getHead();

        while (r) {
            insertNode(p,r->getData());
            r = r->getNext();
            p = p->getNext();
        }
    }
    this->length = rhs.getLength();
    return *this;
}
template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete head;
}

template <class T>
Node<T>* LinkedList<T>::getHead() const
{
    return head;
}

template <class T>
Node<T>* LinkedList<T>::first() const
{
    return head->getNext();
}

template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const
{
    Node<T>* temp = getHead();

    while(temp->getNext())
    {
        if(temp->getNext()->getData() == data)
        {
            return temp;
        }
        else
        {
            temp = temp->getNext();
        }
    }
    return NULL;
}

template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const
{
    Node<T>* temp = first();

    while(temp)
    {
        if(temp->getData() == data)
        {
            return temp;
        }
        else
        {
            temp = temp->getNext();
        }
    }
    return NULL;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data)
{
    if(prev)
    {
        Node<T>* newnode = new Node<T>(data);
        newnode->setNext(prev->getNext());
        prev->setNext(newnode);
    }
    ++length;
}

template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode)
{
    if(prevNode)
    {
        
        Node<T>* temp = prevNode->getNext();
        prevNode->setNext(temp->getNext());
        delete temp;
    }
    --length;
}

template <class T>
void LinkedList<T>::clear()
{
    Node<T>* dummy = getHead();
    while (dummy->getNext())
    {
        Node<T>* temp = dummy->getNext();
        dummy->setNext(temp->getNext());
        delete temp;
    }
    length = 0;
}

template <class T>
size_t LinkedList<T>::getLength() const
{
    return length;
}


template <class T>
void LinkedList<T>::swap(int index1, int index2)
{
    Node<T> *prenode1 = getHead();
    Node<T> *prenode2 = getHead();
    Node<T> *node1 = NULL;
    Node<T> *node2 = NULL;
    Node<T> *x = NULL;

    for(int i = 0;i != index1;i++)
        {
            prenode1 = prenode1->getNext();
        }

    for(int j = 0;j != index2;j++)
        {
            prenode2 = prenode2->getNext();
        }

    node1 = prenode1->getNext();
    node2 = prenode2->getNext();

    if(prenode1) prenode1->setNext(node2);
    if(prenode2) prenode2->setNext(node1);
    x = node1->getNext();
    node1->setNext(node2->getNext());
    node2->setNext(x);
}




/* end of your implementations*/
#endif

