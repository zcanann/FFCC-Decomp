#ifndef _FFCC_PTRARRAY_H_
#define _FFCC_PTRARRAY_H_

#include "global.h"
#include "ffcc/memory.h"
#include "ffcc/ref.h"
#include "ffcc/system.h"
#include <string.h>

#ifndef FFCC_PTRARRAY_GROW_ERROR
#define FFCC_PTRARRAY_GROW_ERROR "CPtrArray grow error"
#endif

#ifndef FFCC_PTRARRAY_FILE
#define FFCC_PTRARRAY_FILE "collection_ptrarray.h"
#endif

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

#ifndef FFCC_PTRARRAY_NO_INLINE_ACCESSORS
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
#endif

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
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        T item = m_items[i];
        if (item != 0) {
            CRef* ref = reinterpret_cast<CRef*>(item);
            if (ref->DecRef() == 0) {
                delete ref;
            }
            m_items[i] = 0;
        }
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
                System.Printf(const_cast<char*>(FFCC_PTRARRAY_GROW_ERROR));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<T*>(Memory._Alloc(m_size * sizeof(T), m_stage, const_cast<char*>(FFCC_PTRARRAY_FILE), 0xfa, 0));
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
