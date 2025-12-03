#ifndef _FFCC_MANAGER_H
#define _FFCC_MANAGER_H

class CManager {
public:
    virtual void ScriptChanging(char*);
    virtual void ScriptChanged(char*, int);

    virtual void MapChanging(int, int);
    virtual void MapChanged(int, int, int);
};

#endif // _FFCC_MANAGER_H
