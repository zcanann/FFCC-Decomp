#ifndef _FFCC_PTRARRAY_DECL_H_
#define _FFCC_PTRARRAY_DECL_H_

#include "ffcc/memory.h"

template <class T>
class CPtrArray
{
public:
    CPtrArray();
    virtual ~CPtrArray();

    int Add(T item);
    void SetAt(unsigned long index, T item);
    int GetSize();
    void RemoveAll();
    void ReleaseAndRemoveAll();
    void DeleteAndRemoveAll();
    void RemoveAt(unsigned long index);
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    void SetDefaultSize(unsigned long defaultSize);
    void SetGrow(int growCapacity);
    T GetAt(unsigned long index);

private:
    int setSize(unsigned long newSize);

    unsigned long m_numItems;
    unsigned long m_size;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

#endif // _FFCC_PTRARRAY_DECL_H_
