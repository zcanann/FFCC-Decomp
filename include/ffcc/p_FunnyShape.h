#ifndef _FFCC_P_FUNNYSHAPE_H_
#define _FFCC_P_FUNNYSHAPE_H_

#include "ffcc/system.h"
#include "ffcc/FS_USB_Process.h"

class CDataHeader;

class CFunnyShapePcs : public CProcess
{
public:
    CFunnyShapePcs();
    ~CFunnyShapePcs();
	
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void createViewer();
    void destroyViewer();
    void calcViewer();
    void drawViewer();

    void SetDisplay(FS_DISPLAY_STATUS);
    void SetUSBData();
    void USBDataCallback(CDataHeader*);
};

#endif // _FFCC_P_FUNNYSHAPE_H_
