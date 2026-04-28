#ifndef _FFCC_PTRARRAY_H_
#define _FFCC_PTRARRAY_H_

#include "global.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include <string.h>

template <class T>
class CPtrArray
{
public:
    CPtrArray();
    virtual ~CPtrArray();

    int GetSize();
    int Add(T item);
    void RemoveAll();
    void ReleaseAndRemoveAll();
    T GetAt(unsigned long index);
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    void SetDefaultSize(unsigned long defaultSize);
    void SetGrow(int growCapacity);

private:
    int setSize(unsigned long newSize);

    unsigned long m_numItems;
    unsigned long m_size;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

template <class T>
CPtrArray<T>::CPtrArray()
{
    m_numItems = 0;
    m_size = 0;
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
int CPtrArray<T>::GetSize()
{
    return m_numItems;
}

template <class T>
T CPtrArray<T>::GetAt(unsigned long index)
{
    return m_items[index];
}

template <class T>
T CPtrArray<T>::operator[](unsigned long index)
{
    return GetAt(index);
}

template <class T>
void CPtrArray<T>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

template <class T>
void CPtrArray<T>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}

template <class T>
void CPtrArray<T>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
}

template <class T>
int CPtrArray<T>::Add(T item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return 1;
}

template <class T>
void CPtrArray<T>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_numItems = 0;
    m_size = 0;
}

template <class T>
void CPtrArray<T>::ReleaseAndRemoveAll()
{
    int offset = 0;
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        int* item = *(int**)((int)m_items + offset);
        if (item != 0) {
            int refCount = item[1];
            item[1] = refCount - 1;
            if (refCount - 1 == 0 && item != 0) {
                (*(void (**)(int*, int))(*item + 8))(item, 1);
            }
            *(unsigned int*)((int)m_items + offset) = 0;
        }
        offset += 4;
    }
    RemoveAll();
}

template <class T>
int CPtrArray<T>::setSize(unsigned long newSize)
{
    T* newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf("CPtrArray grow error");
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<T*>(Memory._Alloc(m_size * sizeof(T), m_stage, "collection_ptrarray.h", 0xfa, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems * sizeof(T));
        }

        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }

        m_items = newItems;
    }

    return 1;
}

#endif // _FFCC_PTRARRAY_H_
