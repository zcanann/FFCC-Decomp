#ifndef _FFCC_PPP_TEXANIM_H_
#define _FFCC_PPP_TEXANIM_H_

#include "ffcc/memory.h"

class CMaterialSet;
class CChunkFile;
class CMemory;
struct Vec;

// CPtrArray template class
template <typename T>
class CPtrArray
{
public:
    void** vtable;
    unsigned long size;
    unsigned long numItems;
    unsigned long defaultSize;
    T** items;
    CMemory::CStage* stage;
    int growCapacity;

public:
    CPtrArray()
    {
        vtable = 0; // Will be set by specific instantiation
        size = 0;
        numItems = 0;
        defaultSize = 0x10;
        items = 0;
        stage = 0;
        growCapacity = 1;
    }
    
    ~CPtrArray()
    {
        RemoveAll();
    }
    
    bool Add(T* item)
    {
        int result = setSize(numItems + 1);
        if (result != 0) {
            items[numItems] = item;
            numItems = numItems + 1;
        }
        return result != 0;
    }
    
    void RemoveAll()
    {
        if (items != 0) {
            delete[] items;
            items = 0;
        }
        size = 0;
        numItems = 0;
    }
    
    int setSize(unsigned long newSize)
    {
        T** newItems;
        
        if (size < newSize) {
            if (size == 0) {
                size = defaultSize;
            } else {
                if (growCapacity == 0) {
                    // Printf error - skipping for now
                }
                size = size << 1;
            }
            
            // Allocate new buffer (simplified - would need proper memory management)
            newItems = new T*[size];
            if (newItems == 0) {
                return 0;
            }
            
            // Copy existing items
            if (items != 0) {
                for (unsigned long i = 0; i < numItems; i++) {
                    newItems[i] = items[i];
                }
            }
            
            // Free old buffer
            if (items != 0) {
                delete[] items;
                items = 0;
            }
            
            items = newItems;
        }
        return 1;
    }
};

class CTexAnimSet
{
public:
    enum ANIM_TYPE
    {
        TODO,
    };

    CTexAnimSet();
    ~CTexAnimSet();

    void Create(CChunkFile&, CMemory::CStage*);
    void Duplicate(CMemory::CStage*);
    void AttachMaterialSet(CMaterialSet*);
    void AddFrame();
    void Change(char*, float, ANIM_TYPE);
    void SetTexGen();
};

class CTexAnimSeq
{
public:
    CTexAnimSeq();
    ~CTexAnimSeq();

    void Create(CChunkFile&, CMemory::CStage*);
    void Interp(float, Vec&);
    void GetTotalFrame();
    void GetName();
    void IsChin();
};

class CTexAnim
{
public:
	class CRefData
	{
	public:
		CRefData();
		~CRefData();
	};

    CTexAnim();
    ~CTexAnim();

    void Create(CChunkFile&, CMemory::CStage*);
    void Duplicate(CMemory::CStage*);
    void AttachMaterialSet(CMaterialSet*);
    void AddFrame(float);
    void Find(char*);
    void Change(int, float, CTexAnimSet::ANIM_TYPE);
    void SetTexGen();
    void IsChin();
    void GetChin();
};

#endif // _FFCC_PPP_TEXANIM_H_
