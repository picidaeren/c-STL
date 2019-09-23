//
// Created by Administrator on 2019/9/23 0023.
//

#ifndef QUICKSORT_MYLIST_H
#define QUICKSORT_MYLIST_H

#include <list>
#include <iostream>

using namespace std;

//List的节点
template <typename  Object> struct Node{
    Object object;
    //Object data_;
    Node <Object> *previous_;
    Node <Object> *next_;
    Node(const Object &obj):object(obj),next_(nullptr),previous_(nullptr){};
    Node():next_(nullptr),previous_(nullptr);
};



//基类迭代器的实现
template <typename Object> class const_iterator{
protected:
    Node<Object>* current;
    Object& retrive() const {return current->data_;}
    const_iterator &operator++(int);
    const_iterator &operator++();
    bool operator==(const const_iterator &);
    bool operator!=(const const_iterator &);
    Object& operator*() const;
    friend class List<Object>;


};

template <typename Object>
Object& const_iterator<Object>::operator*() const {
    return current->object;
}

template <typename Object>
const_iterator<Object>& const_iterator<Object>::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename Object>
const_iterator<Object>& const_iterator<Object>::operator++(){
    current = current->next;
    return *this;
}

template  <typename Object>
bool const_iterator<Object>::operator==(const const_iterator &rhs) {
    return current == rhs.current ? true : false;
}
template  <typename Object>
bool const_iterator<Object>::operator!=(const const_iterator &rhs) {
    return !(current == rhs.current);
}


//迭代器基类
template <typename Object> class iterator : public const_iterator<Object>{
public:
        iterator(){};
        Object& operator*() const { return const_iterator<Object>::current->object;};
        const Object&operator*() const {
            return const_iterator<Object>::operator*();
        }
    iterator&operator++() {
        const_iterator<Object>::current = const_iterator<Object>::current->next;
        return *this;
    }
    iterator&operator++(int) {
        iterator old = *this;
        ++(*this);
        return old;
    }
    friend class List<Object>;


    };


//List实现
template <typename Object> class List {
private:
    Node<Object> *head;
    Node<Object> *tail;
    int theSize;
public:
    typedef iterator<Object> iterator;
    typedef const_iterator<Object> const_iterator;
    List();
    ~List();
    List(const List<Object>&);
    List(unsigned initSize);
    void push_back(const Object&);
    void push_front(const Object&);
    void pop_front();
    void pop_back();
    bool empty();
    void clear();
    void resize(unsigned);
    const Object& front();
    const Object& back();
    int size()const;
    void insert(iterator, const Object&);
    void remove(const Object&);
    const List<Object>&operator=(const List<Object>&);
    iterator begin() {
        iterator it;
        it.current = head->next;
        return it;
    }
    iterator end() {
        iterator it;
        it.current = tail;
        return it;
    }
    const_iterator begin()const{
        const_iterator it;
        it.current=head->next;
        return it;
    }
    const_iterator end()const{
        const_iterator it;
        it.current=tail;
        return it;
    }
    iterator erase(iterator it){
        if(it!=end()&&!empty()){
            Node<Object>*tmp=it.current;
            Node<Object>*p=tmp;
            tmp->previous->next=tmp->next;
            tmp=tmp->next;
            delete p;
            iterator to;
            to.current=tmp;
            --theSize;
            return to;
        }
    }
};
template <typename Object> List<Object>::~List() {
    clear();
    delete head;
    delete tail;
}
template <typename Object> List<Object>::List() :head(new Node<Object>()), theSize(0),tail(new Node<Object>()) {
    tail->previous=head;
    head->next=tail;
}
template <typename Object> List<Object>::List(unsigned initSize) : head(new Node<Object>()),theSize(initSize),tail(new Node<Object>()) {
    tail->previous=head;
    head->next=tail;
    for (int i = 0; i < theSize; i++) {
        Node<Object>*tmp = new Node<Object>();
        tail->previous->next=tmp;
        tmp->previous=tail->previous;
        tail->previous=tmp;
        tmp->next=tail;
    }
}
template <typename Object> List<Object>::List(const List<Object> &rhs):head(new Node<Object>()),tail(new Node<Object>()),theSize(0) {
    tail->previous=head;
    head->next=tail;
    for(const_iterator it=rhs.begin();it!=rhs.end();++it)
        push_back(*it);
}
template <typename Object> const List<Object>& List<Object>::operator=(const List<Object> &rhs) {
    if(this==&rhs)return *this;
    clear();
    for(const_iterator it=rhs.begin();it!=rhs.end();++it)
        push_back(*it);
    return *this;
}
template <typename Object> void List<Object>::push_back(const Object &rhs) {
    Node<Object>*tmp=new Node<Object>(rhs);
    tail->previous->next=tmp;
    tmp->previous=tail->previous;
    tail->previous=tmp;
    tmp->next=tail;
    ++theSize;
}
template <typename Object> void List<Object>::pop_back() {
    if(empty())return;
    else{
        Node<Object>*tmp=tail->previous;
        tmp->previous->next=tail;
        tail->previous=tmp->previous;
        delete tmp;
        --theSize;
    }
}
template <typename Object> void List<Object>::push_front(const Object &obj) {
    Node<Object>*tmp = new Node<Object>(obj);
    tmp->previous=head;
    head->next->previous=tmp;
    tmp->next = head->next;
    head->next = tmp;
    ++theSize;
}
template <typename Object> void List<Object>::pop_front() {
    if (empty()) return;
    else {
        Node<Object>*tmp = head->next;
        head->next = tmp->next;
        delete tmp;
        --theSize;
    }
}
template <typename Object> int List<Object>::size() const {
    return theSize;
}
template <typename Object> bool List<Object>::empty() {
    return theSize == 0 ? true : false;
}
template <typename Object> void List<Object>::clear() {
    while (!empty()){
        pop_back();
    }
}
template <typename Object> const Object& List<Object>::front() {
    if (!empty())
        return head->next->object;
}
template <typename Object> const Object& List<Object>::back() {
    if(!empty()){
        return tail->previous->object;
    }
}
template <typename Object> void List<Object>::remove(const Object &obj) {
    if(empty())return;
    else{
        Node<Object>*tmp=head->next;
        while(tmp!=tail){
            if(tmp->object==obj){
                Node<Object>*p=tmp;
                tmp->previous->next=tmp->next;
                tmp->next->previous=p->previous;
                tmp=tmp->next;
                std::cout<<"remove()"<<p->object<<std::endl;
                delete p;
                p=NULL;
                --theSize;
            }
            else
                tmp=tmp->next;

        }
    }
}
template <typename Object> void List<Object>::resize(unsigned newSize) {
    if(newSize==theSize)return;
    else if(newSize<theSize){
        int num=theSize-newSize;
        for(int i=0;i<num;i++) {
            std::cout<<"pop"<<back()<<" ";
            pop_back();
        }
    }
    else{
        int num=newSize-theSize;
        for(int i=0;i<num;i++)
            push_back(Object());
    }
}
template <typename Object> const Object& const_iterator<Object>::operator*() const {
    return current->object;
}
template <typename Object> const_iterator<Object>& const_iterator<Object>::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}
template <typename Object> const_iterator<Object>& const_iterator<Object>::operator++() {
    current = current->next;
    return *this;
}
template <typename Object>bool const_iterator<Object>::operator==(const const_iterator &rhs) {
    return current == rhs.current ? true : false;
}
template <typename Object>bool const_iterator<Object>::operator!=(const const_iterator &rhs) {
    return !(this->current == rhs.current);
}
template <typename Object>void List<Object>::insert(iterator it, const Object &obj) {
    Node<Object> *tmp = it.current;
    Node<Object>* p = new Node<Object>(obj);
    tmp->previous->next=p;
    p->next = tmp;
    p->previous=tmp->previous;
    tmp->previous=p;
    ++theSize;
}







#endif //QUICKSORT_MYLIST_H
