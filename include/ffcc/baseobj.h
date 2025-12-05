#ifndef _FFCC_BASEOBJ_H_
#define _FFCC_BASEOBJ_H_

#include "ffcc/cflat_runtime.h"

class CGBaseObj : public CFlatRuntime::CObject
{
	CGBaseObj();
	~CGBaseObj();

	virtual void Create();
	virtual void Destroy();
    virtual void onDraw();
    virtual int GetCID();
	void Frame();
	void Draw();
	void onPush(CGBaseObj*, int);
	void onTalk(CGBaseObj*, int);

	int placeholder;
};

#endif // _FFCC_BASEOBJ_H_
