#ifndef _FFCC_PTRARRAY_H_
#define _FFCC_PTRARRAY_H_

#include "global.h"

template <class T>
class CPtrArray
{
public:
    CPtrArray();
    ~CPtrArray();
    
    int GetSize() const;
    T* GetAt(unsigned int index) const;
    T* operator[](unsigned int index) const;
    
private:
    T** m_items;
    int m_numItems;
};

template <class T>
CPtrArray<T>::CPtrArray() : m_items(nullptr), m_numItems(0)
{
}

template <class T>
CPtrArray<T>::~CPtrArray()
{
}

template <class T>
int CPtrArray<T>::GetSize() const
{
    return m_numItems;
}

template <class T>
T* CPtrArray<T>::GetAt(unsigned int index) const
{
    return m_items[index];
}

template <class T>
T* CPtrArray<T>::operator[](unsigned int index) const
{
    return GetAt(index);
}

#endif // _FFCC_PTRARRAY_H_