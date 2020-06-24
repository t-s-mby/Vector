#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdint>

template <typename T>
class Vector
{
public:
    Vector();
    explicit Vector(size_t num, const T& val= T()); //init vector of num elements with val T
    Vector(const Vector&);
    ~Vector();

    Vector& operator=(const Vector<T>&);
    T& operator[](size_t index); //set
    const T& operator[](size_t index)const; //get

    size_t size()const;
    size_t max_size()const;
    void resize(size_t num, T val=T());
    size_t capacity()const;
    bool empty()const;
    void reserve(size_t);
    T& at(size_t index);
    T& front();
    const T& front()const ;
    T& back();
    const T& back()const;
    T* data();
    const T* data()const;
    void assign(size_t n, const T& val=T());
    void push_back(const T&);
    void pop_back();
    void insert (size_t position, size_t n, const T& val);
    void erase (size_t position, size_t num = 1); //todo erase number of elements form position on
    void swap(Vector& x);
    void clear();
    friend std::ostream& operator <<(std::ostream&os, const Vector<T>&);

private:
    void init(size_t n);
    T* m_vector;
    size_t m_size;
    size_t m_capacity;
};

template<typename T>
void Vector<T>::init(size_t n)
{
    T * tmp =new T[n];
    if(m_vector!= NULL)
        delete[] m_vector;
    m_vector = tmp;
}

template<typename T>
Vector<T>::Vector():m_vector(init(1)),m_size(0),m_capacity(1) {}

template<typename T>
Vector<T>::Vector(size_t num, const T& val):m_vector(init(num)),m_size(num),m_capacity(num) {
    for (size_t i = 0; i <num ; i++) {
        m_vector[i]=val;
    }
}
template<typename T>
Vector<T>::Vector(const Vector& other):m_vector(init(other.m_capacity)),m_size(other.m_size),m_capacity(other.m_capacity){
    for (size_t i = 0; i <m_size ; ++i) {
        m_vector[i]=other.m_vector[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete [] m_vector;
    m_vector= NULL;
    m_size=0;
    m_capacity=0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other){

    if(this->m_vector!=other.m_vector)
    {
        T* tmp=new T[other.m_capacity];
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
inline size_t Vector<T>::size()const{
    return m_size;
}

template<typename T>
inline size_t Vector<T>::max_size()const{
    return SIZE_MAX;
}

template<typename T>
void Vector<T>::resize(size_t num, T val){
    if(num<m_size)
    {
        for(size_t i =num; i<m_size;i++)
            m_vector[i].~T();
        m_size=num;
    }
    else
    {
        T* tmp=new T[num];

        for (size_t i = 0; i < m_size; ++i) {
            tmp[i]=m_vector[i];
        }
        for (size_t j = m_size; j <num ; ++j) {
            tmp[j]=val;
        }
        delete[]m_vector;
        m_vector=tmp;
        m_size=num;
        m_capacity = num;
    }
}

template<typename T>
inline size_t Vector<T>::capacity()const{
    return m_capacity;
}

template<typename T>
inline bool Vector<T>::empty()const{
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
inline T& Vector<T>::operator[](size_t index) {
    return m_vector[index];
}

template<typename T>
inline const T& Vector<T>::operator[](size_t index) const{
    return m_vector[index];
}


template<typename T>
inline T& Vector<T>::at(size_t index){
    if(index>m_size)
    {
        throw std::out_of_range("index out of range!");
    }
    return m_vector[index];
}

template<typename T>
inline T& Vector<T>::front() {
    return m_vector[0];
}

template<typename T>
inline const T& Vector<T>::front()const {
    return m_vector[0];
}


template<typename T>
inline T& Vector<T>::back() {
    return m_vector[m_size-1];
}

template<typename T>
inline const T& Vector<T>::back()const {
    return m_vector[m_size-1];
}

template<typename T>
inline T* Vector<T>::data()
{
    return m_vector;
}

template<typename T>
inline const T* Vector<T>::data()const
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
        for(size_t j=n; j<m_size;j++)
        {
            m_vector[j].~T();
        }
        m_size=n;
        return;
    }
    T* tmp=new T[n];

    for (size_t i = 0; i<n; ++i) {
        tmp[i]=val;
    }
    delete[]m_vector;
    m_vector=tmp;
    m_size=n;
    m_capacity=n;
}

template<typename T>
void Vector<T>::push_back(const T& val){
    if(m_size==m_capacity)
    {
        T* tmp=new T[m_capacity*2];
        for(size_t i=0; i<m_size; i++)
            tmp[i]=m_vector[i];
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
inline void Vector<T>::pop_back()
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
        for(i=position+n; i<m_size+n; i++)
        {
            m_vector[i+n]= m_vector[i];
        }
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
    m_size--;
}

template<typename T>
void Vector<T>::erase (size_t first, size_t last)
{
    size_t i;
    for(i=first; i<last;i++)
        m_vector[i].~T();
    for(i=first; i<m_size-(last-first);i++)
        m_vector[i]= m_vector[i+last-first];
    m_size-=last-first;
}

template<typename T>
void Vector<T>::swap (Vector& x)
{
    T* tmp;
    tmp= m_vector;
    m_vector = x.m_vector;
    x.m_vector = tmp;

    size_t tmp1= m_size;
    m_size=x.m_size;
    x.m_size=tmp1;

    size_t tmp2= m_capacity;
    m_capacity=x.m_capacity;
    x.m_capacity=tmp1;
}

template<typename T>
void Vector<T> :: clear()
{
    size_t i;
    for(i=0; i<m_size; i++)
    {
        m_vector[i].~T();
    }
    delete[](m_vector);
    m_size= 0;
    m_capacity = 0;
}

template<typename T>
inline std::ostream& operator << (std::ostream&os, const Vector<T>& x)
{
    int *p = x.data();
    for(size_t i=0; i<x.size(); i++)
        os<<p[i]<<' ';
    return os;
}

#endif