#include <iostream>
#include <exception>
#include <limits>

template <typename T>
class Vector{
public:
    explicit Vector();
    explicit Vector (size_t n, T val);
    Vector (const Vector& x);
    Vector& operator= (const Vector& x);
    ~Vector();
    size_t size(const Vector&) const;
    size_t capacity(const Vector&) const;
    size_t max_size(const Vector&) const;
    void resize (size_t n, T val);
private:
    T* ptr;
    size_t m_size;
    size_t m_capacity;
};

template <typename T>
Vector<T>::Vector():ptr(NULL),m_size(0),m_capacity(0){}

template <typename T>
Vector<T>::Vector (size_t n, T val):ptr(NULL)
{
    size_t i;
    ptr= new T[n];
    for(i=0; i<n; i++)
    {
        ptr[i]= val;
    }
    m_size= n;
    m_capacity = n;
}

template <typename T>
Vector<T>::Vector(const Vector& x):ptr(NULL)
{
    int i;
    ptr = new T[x.m_size];
    for(i=0; i<size(); i++)
    {
        ptr[i]= x.ptr[i];
    }
    m_size = x.m_size;
    m_capacity = x.m_capacity;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] ptr;
    ptr = NULL;
}

template <typename T>
size_t Vector<T>::size(const Vector& x) const
{
   return x.m_size;
}

template <typename T>
size_t Vector<T>::max_size(const Vector& x) const
{
    return std::numeric_limits<size_t>::max();
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector& x)
{
    size_t i;
    T * tmp =new T[x.m_size];
    delete[] ptr;
    ptr = tmp;
    m_size = x.m_size;
    m_capacity = m_size;
    for(i=0; i<m_size;i++)
    {
        ptr[i]= x.ptr[i];
    }
}

template <typename T>
void Vector<T>::resize (size_t n, T val)
{
    if(n==0)
    {
        delete[] ptr;
        ptr = NULL;
        m_size= 0;
        m_capacity= 0;
    }
    size_t i;
    if(n<m_size)
    {
        for(i=n; i<m_size; i++)
            delete(ptr+i);
        m_size = n;
        m_capacity = n;
    }
    else
    {
        if(n<m_capacity)
        {
            for(i=m_size; i<n; i++)
            {
                ptr[i]= val;
                m_size +=n;
            }
        }
        else  // realloc vector
        {
            T * tmp;
            if(n<m_capacity*2){
                tmp = new T[m_capacity*2];
                m_capacity *=2;
            }
            else{
                tmp = new T[n];
                m_capacity = n;
            }
            ptr= tmp;
            for(i = m_size; i<n;i++)
                ptr[i]= val;
            for(i = n; i<m_capacity;i++)
                ptr[i]= 0;
            m_size = n;
        }
    }
}

template <typename T>
size_t Vector<T>::capacity(const Vector& x) const
{
    return m_capacity;
}