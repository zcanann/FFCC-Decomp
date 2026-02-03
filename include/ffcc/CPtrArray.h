#ifndef _FFCC_CPTRARRAY_H_
#define _FFCC_CPTRARRAY_H_

#include "ffcc/memory.h"

template <class T>
class CPtrArray
{
private:
    void** m_vtable;           // 0x00
    int m_size;                // 0x04 - current count of elements
    int m_maxSize;             // 0x08 - allocated capacity
    int m_growBy;              // 0x0C - growth increment
    T** m_data;                // 0x10 - pointer to data array
    CMemory::CStage* m_stage;  // 0x14 - memory stage
    int m_autoGrow;            // 0x18 - auto growth flag

public:
    CPtrArray();
    ~CPtrArray();
    
    int Add(T* ptr);
    T* GetAt(int index);
    T* operator[](int index);
    int GetSize();
    void RemoveAll();
    void ReleaseAndRemoveAll();
    void SetStage(CMemory::CStage* stage);
    int setSize(int newSize);
};

#endif // _FFCC_CPTRARRAY_H_