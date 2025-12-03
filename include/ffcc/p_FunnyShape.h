#ifndef _FFCC_P_FUNNYSHAPE_H_
#define _FFCC_P_FUNNYSHAPE_H_

class CFunnyShapePcs
{
public:
    CFunnyShapePcs();
    ~CFunnyShapePcs();
	
    void Init();
    void Quit();
    void GetTable(unsigned long);

    void createViewer();
    void destroyViewer();
    void calcViewer();
    void drawViewer();
};

#endif // _FFCC_P_FUNNYSHAPE_H_
