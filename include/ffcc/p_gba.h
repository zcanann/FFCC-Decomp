#ifndef _FFCC_P_GBA_H_
#define _FFCC_P_GBA_H_

class CGbaPcs
{
public:
    CGbaPcs();
	
    void Init();
    void Quit();
    void GetTable(unsigned long);

    void SetFirstZone();

    void create();
    void destroy();
    void calc();
    void draw();

    virtual void onMapChanging(int, int);
    virtual void onMapChanged(int, int, int);
    virtual void onScriptChanging(char *);

};

#endif // _FFCC_P_GBA_H_
