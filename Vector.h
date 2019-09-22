//
// Created by Administrator on 2019/9/22 0022.
//

#ifndef QUICKSORT_VECTOR_H
#define QUICKSORT_VECTOR_H

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <iterator>


using namespace std;

template <typename T>
class Vector {
private:
    T *p_;
    int capacity_;
    int size_;

public:
    Vector();
    Vector(int size,T data);
    ~Vector();
    Vector(const Vector& v);
    void Vprint() const;
    void Vpush_back(const T data);
    void Vpop_back();
    void Vinsert(const int pos,const T data);
    void Vclear();
    T& operator[](const int index);
    void operator=(const Vector& v);
};

template <typename T>
Vector<T>::Vector(){
    this->capacity_ = 20;
    this->size_ = 0;
    T *p_ = new T[capacity_];
}

template <typename T>
Vector<T>::Vector(int size,T data){
    this->capacity_ = 20 + size;
    this->size_ = size;
    T *p_ = new T[capacity_];
    for(int i = 0;i < this->size_;i++){
        p_[i] = data;
    }
}

template <typename T>
Vector<T>::~Vector() {
    if(this->p_!=NULL)
    {
        delete[] this->p_;
    }
    this->p_ = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector &v) {
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;
    this->p_ = new T[this->capacity_];
    memcpy(this->p_,v.p_,this->size_*sizeof(T));
}

template <typename T>
void Vector<T>::Vprint() const {
    for (int i = 0; i < this->size_; ++i) {
        cout<<this->p_[i]<<"\t";
    }
    cout<<endl;
}

template <typename T>
void Vector<T>::Vpush_back(const T data) {
    if(nullptr == this->p_){
        this->capacity_ = 20;
        this->size_ = 0;
        T *p = new T[this->capacity_];
    }
    if(this->size_ == this->capacity_){
        //满了每次容量拓展至原来的二倍
        T *new_p = new T[this->capacity_*2];
        memcpy(new_p,this->p_,this->size_*sizeof(T));
        this->capacity_ *= 2;
        delete[] this->p_;
        this->p_ = new_p;
    }
    this->Vprint();
    this->p_[this->size_] = data;
    this->size_++;

}

template <typename T>
void Vector<T>::Vpop_back() {
    if(this->size_ > 1){
        this->p_[this->size_ - 1] = 0;
        this->size_--;
    }
}

template <typename T>
void Vector<T>::Vinsert(const int pos, const T data) {
    if(pos >= 0 && pos <= this->size_){
        if(this->size_ == this->capacity_){
            T *new_p = new T[this->capacity_*2];
            memcpy(new_p,this->p_,this->size_*sizeof(T));
            this->capacity *= 2;
            delete[] this->p_;
            this->p_ = new_p;
        }
        for (int i = 0; i < this->size_; ++i) {
            this->p_[i] = this->p_[i-1];
        }
        this->p_[pos] = data;
        this->size_++;
    }
}

template <typename T>
void Vector<T>::Vclear() {
    this->size_ = 0;
}

template <typename T>
T& Vector<T>::operator[](const int index) {
    if(index > 0 && index < this->size_){
        return this->p_[index];
    }
}

template <typename T>
void Vector<T>::operator=(const Vector &v) {
    if(nullptr != this->p_){
        delete[] this->p_;
        this->capacity_ = 0;
        this->size_ = 0;
        this->p_ = nullptr;
    }
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;
    this->p_ = new T[this->capacity_];
    memcpy(this->p_,v.p_,this->size_* sizeof(T));
}

#endif //QUICKSORT_VECTOR_H
