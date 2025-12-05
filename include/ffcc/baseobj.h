#ifndef _FFCC_BASEOBJ_H_
#define _FFCC_BASEOBJ_H_

#include "ffcc/cflat_runtime.h"

class CGBaseObj : public CFlatRuntime::CObject
{
	CGBaseObj();
	virtual ~CGBaseObj();                       // vtable 0x4
	
    virtual void onNewFinished(int) = 0;        // vtable 0x8
    virtual int GetCID();                       // vtable 0x10
	virtual void onPush(CGBaseObj* other, int); // vtable 0x14
	virtual void onTalk(CGBaseObj* other, int); // vtable 0x18
	virtual void onCreate();                    // vtable 0x1c
	virtual void onDestroy();                   // vtable 0x20
    virtual void onFrame();                     // vtable 0x24
    virtual void onDraw();                      // vtable 0x28

	void Create();
	void Destroy();
	void Frame();
	void Draw();

	unsigned char m_isActive;
};

#endif // _FFCC_BASEOBJ_H_
