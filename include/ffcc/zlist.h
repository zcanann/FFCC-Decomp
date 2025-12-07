#ifndef _FFCC_PPP_ZLIST_H_
#define _FFCC_PPP_ZLIST_H_

#include <dolphin/types.h>

struct _ZLISTITEM
{
    _ZLISTITEM* m_previous; // 0x0
    _ZLISTITEM* m_next;     // 0x4
    void* m_data;           // 0x8
}; // Size 0xC

class ZLIST
{
public:
    ZLIST();
    ~ZLIST();

    void DeleteList();
    bool AddTail(void* data);
    void* GetDataNext(_ZLISTITEM** it);
    void* GetDataIdx(int index);

    _ZLISTITEM m_root;
    short m_count;
}; // Size 0x10

#endif // _FFCC_PPP_ZLIST_H_
