#ifndef _FFCC_PTRARRAY_H_
#define _FFCC_PTRARRAY_H_

#include "global.h"
#include "ffcc/memory.h"

template <class T>
class CPtrArray
{
public:
    CPtrArray();
    ~CPtrArray();
    
    int GetSize() const;
    bool Add(T* item);
    void RemoveAll();
    T* GetAt(unsigned int index) const;
    T* operator[](unsigned int index) const;
    
private:
    bool setSize(unsigned int newSize);
        
    unsigned long m_size;
    unsigned long m_numItems;
    unsigned long m_defaultSize;
    T** m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

template <class T>
CPtrArray<T>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

template <class T>
CPtrArray<T>::~CPtrArray()
{
    RemoveAll();
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
void CPtrArray<T>::RemoveAll()
{
    if (items != 0) {
        delete[] items;
        items = 0;
    }
    size = 0;
    numItems = 0;
}

template <class T>
bool CPtrArray<T>::setSize(unsigned int newSize)
{
    T** newItems;
    
    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                // Printf error - skipping for now
            }
            m_size = m_size << 1;
        }
        
        // Allocate new buffer (simplified - would need proper memory management)
        newItems = new T*[m_size];
        if (newItems == 0) {
            return false;
        }
        
        // Copy existing items
        if (m_items != 0) {
            for (unsigned long i = 0; i < m_numItems; i++) {
                newItems[i] = m_items[i];
            }
        }
        
        // Free old buffer
        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }
        
        m_items = newItems;
    }

    return true;
}

#endif // _FFCC_PTRARRAY_H_
