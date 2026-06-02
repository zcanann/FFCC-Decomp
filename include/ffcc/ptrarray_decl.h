#ifndef _FFCC_PTRARRAY_DECL_H_
#define _FFCC_PTRARRAY_DECL_H_

#include "ffcc/memory.h"

#ifndef _FFCC_PTRARRAY_H_
template <class T>
class CPtrArray
{
public:
    CPtrArray();
    virtual ~CPtrArray();

#ifdef FFCC_PTRARRAY_DECL_BOOL_ADD
    bool Add(T item);
#else
    int Add(T item);
#endif
#ifndef FFCC_PTRARRAY_DECL_NO_SET_AT
    void SetAt(unsigned long index, T item);
#endif
    int GetSize();
    void RemoveAll();
    void ReleaseAndRemoveAll();
#ifdef FFCC_PTRARRAY_DECL_REMOVE_AT
    void RemoveAt(unsigned long index);
#endif
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    void SetDefaultSize(unsigned long defaultSize);
    void SetGrow(int growCapacity);
    int setSize(unsigned long newSize);
    T GetAt(unsigned long index);

private:
    unsigned long m_numItems;
    unsigned long m_size;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};
#endif

#endif // _FFCC_PTRARRAY_DECL_H_
