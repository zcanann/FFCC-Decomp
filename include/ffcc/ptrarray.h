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
    bool Add(T* item);
    T* GetAt(unsigned int index) const;
    T* operator[](unsigned int index) const;
    
private:
    bool setSize(unsigned int newSize);
    
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

template <class T>
bool CPtrArray<T>::Add(T* item)
{
    bool success = setSize(m_numItems + 1);
    if (success) {
        m_items[m_numItems] = item;
        m_numItems = m_numItems + 1;
    }
    return success;
}

template <class T>
bool CPtrArray<T>::setSize(unsigned int newSize)
{
    // TODO: Implement proper array resizing logic
    // For now, assume success - this needs memory allocation logic
    return true;
}

#endif // _FFCC_PTRARRAY_H_