#ifndef _FFCC_BASEOBJ_H_
#define _FFCC_BASEOBJ_H_

#include "ffcc/cflat_runtime.h"

class CGBaseObj : public CFlatRuntime::CObject
{
	CGBaseObj();
	virtual ~CGBaseObj();                       // vtable entry 0x4
	
    virtual void onNewFinished(int) = 0;        // vtable entry 0x8
	void InitFinished();
    virtual int GetCID();                       // vtable entry 0x10
	virtual void onPush(CGBaseObj* other, int); // vtable entry 0x14
	virtual void onTalk(CGBaseObj* other, int); // vtable entry 0x18
	virtual void onCreate();                    // vtable entry 0x1c
	virtual void onDestroy();                   // vtable entry 0x20
    virtual void onFrame();                     // vtable entry 0x24
    virtual void onDraw();                      // vtable entry 0x28

	void Create();
	void Destroy();
	void Frame();
	void Draw();

	unsigned char m_isActive;
};

#endif // _FFCC_BASEOBJ_H_
