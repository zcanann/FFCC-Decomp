#ifndef CMANAGER_H
#define CMANAGER_H

class CManager {
public:
    virtual void ScriptChanging(char*);
    virtual void ScriptChanged(char*, int);

    virtual void MapChanging(int, int);
    virtual void MapChanged(int, int, int);
};

#endif // CMANAGER_H
