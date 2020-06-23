#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdint>

template <typename T>
class Vector
{
public:
    Vector();
    Vector(size_t num, T val);
    Vector(const Vector&);
    ~Vector();
    Vector& operator=(const Vector<T>&);
//capacity:
    size_t size()const;
    size_t max_size()const;
    void resize(size_t num, T val=T(0));
    size_t capacity()const;
    bool empty()const;
    void reserve(size_t);
//element access:
    T& operator[](size_t index);
    const T& operator[](size_t index)const;
    T& at(size_t index);
    T& front();
    const T& front()const ;
    const T& back()const;
    const T* data()const;
    T& back();
    T* data();
//modifiers:
    void assign(size_t n, const T& val);
    void push_back(const T&);
    void pop_back();
    void insert (size_t position, size_t n, const T& val);
    void erase (size_t position);
    void erase (size_t first, size_t last);
    void swap(Vector& x);
    void clear();

private:
    T* m_vector;
    size_t m_size;
    size_t m_capacity;
};

template<typename T>
Vector<T>::Vector():m_vector(NULL),m_size(0),m_capacity(0) {}

template<typename T>
Vector<T>::Vector(size_t num, T val):m_vector(new T[num]),m_size(num),m_capacity(num) {
    for (size_t i = 0; i <num ; i++) {
        m_vector[i]=val;
    }
}
template<typename T>
Vector<T>::Vector(const Vector& other):m_vector(new T[other.m_capacity]),m_size(other.m_size),m_capacity(other.m_capacity){
    for (size_t i = 0; i <m_size ; ++i) {
        m_vector[i]=other.m_vector[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete [] m_vector;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other){
    T* tmp=new T[other.m_capacity];
    if(tmp)
    {
        for (size_t i = 0; i < other.m_size; ++i) {
            tmp[i]=other.m_vector[i];
        }
        delete[] m_vector;
        m_vector=tmp;
        m_capacity=other.m_capacity;
        m_size=other.m_size;
    }
    return *this;
}

template<typename T>
size_t Vector<T>::size()const{
    return m_size;
}

template<typename T>
size_t Vector<T>::max_size()const{
    return SIZE_MAX;
}

template<typename T>
void Vector<T>::resize(size_t num, T val){
    if(num<m_size)
    {
        for(size_t i =num; i<m_size;i++)
            m_vector[i].~T();
        m_size=num;
        return;
    }
    T* tmp=new T[num];
    if(tmp)
    {
        for (size_t i = 0; i < m_size,i<num; ++i) {
            tmp[i]=m_vector[i];
        }
        for (size_t j = m_size; j <num ; ++j) {
            tmp[j]=val;
        }
        delete[]m_vector;
        m_vector=tmp;
        m_size=num;
    }
}

template<typename T>
size_t Vector<T>::capacity()const{
    return m_capacity;
}

template<typename T>
bool Vector<T>::empty()const{
    return m_size==0;
}

template<typename T>
void Vector<T>::reserve(size_t num){
    if(num>m_capacity)
    {
        this->resize(num);
    }
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return m_vector[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const{
    return m_vector[index];
}


template<typename T>
T& Vector<T>::at(size_t index){
    if(index>m_size)
    {
        throw std::out_of_range("index out of range!");
    }
    return m_vector[index];
}

template<typename T>
T& Vector<T>::front() {
    return m_vector[0];
}

template<typename T>
const T& Vector<T>::front()const {
    return m_vector[0];
}


template<typename T>
T& Vector<T>::back() {
    return m_vector[m_size-1];
}

template<typename T>
const T& Vector<T>::back()const {
    return m_vector[m_size-1];
}

template<typename T>
T* Vector<T>::data()
{
    return m_vector;
}

template<typename T>
const T* Vector<T>::data()const
{
    return m_vector;
}

template<typename T>
void Vector<T>::assign(size_t n, const T& val){

    if(n<m_capacity)
    {
        for (size_t i = 0; i<n; ++i) {
            m_vector[i]=val;
        }
        m_size=n;
        return;
    }
    T* tmp=new T[n];
    if(*tmp!=NULL)
    {
        for (size_t i = 0; i<n; ++i) {
            tmp[i]=val;
        }
        delete[]m_vector;
        m_vector=tmp;
        m_size=n;
        m_capacity=n;
    }
}

template<typename T>
void Vector<T>::push_back(const T& val){
    if(m_size==m_capacity)
    {
        T* tmp=new T[m_capacity*2];
        m_vector = tmp;
        m_vector[m_size]= val;
        m_size++;
        m_capacity*=2;
    }
    else
    {
        m_vector[m_size]= val;
        m_size++;
    }
}

template<typename T>
void Vector<T>::pop_back()
{
    ~m_vector[m_size-1];
    m_size--;
}

template<typename T>
void Vector<T>::insert (size_t position, size_t n, const T& val)
{
    size_t i;
    size_t size;
    if(m_capacity >= m_size+n)
    {
        for(i=0; i<n; i++)
        {
            m_vector[position+i+n] =  m_vector[position+i];
            m_vector[position+i] = val;
        }
        m_size +=n;
    }
    else
    {
        size = n>m_capacity*2? n+m_size:m_capacity*2;
        T * tmp = new T [size];
        for(i=0; i<position; i++){
            tmp[i]= m_vector[i];
        }
        for(i=position;i<position+n;i++){
            tmp[i]= val;
        }
        for(i=position+n;i<m_size+n;i++){
            tmp[i]= m_vector[i-n];
        }
        m_size+=n;
        m_capacity = size;
        m_vector = tmp;
    }
}

template<typename T>
void Vector<T>:: erase (size_t position)
{
    size_t i;
    m_vector[position].~T();
    for(i=position; i<m_size-1;i++)
        m_vector[i]= m_vector[i+1];
    //last place guarbage???
}

template<typename T>
void Vector<T>::erase (size_t first, size_t last)
{
    size_t i;
    for(i=first; i<last;i++)
        m_vector[i].~T();
    for(i=first; i<m_size-1;i++)
        m_vector[i]= m_vector[i+last-first];
}

#endif