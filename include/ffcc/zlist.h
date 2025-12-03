#ifndef _FFCC_PPP_ZLIST_H_
#define _FFCC_PPP_ZLIST_H_

struct _ZLISTITEM
{
};

class ZLIST
{
public:
    ZLIST();
    ~ZLIST();

    void DeleteList();
    void AddTail(void *);
    void GetDataNext(_ZLISTITEM **);
    void GetDataIdx(int);
    void MakeItem();
    void GetItemIdx(int);
};

#endif // _FFCC_PPP_ZLIST_H_
