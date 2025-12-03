#ifndef _FFCC_BASEOBJ_H_
#define _FFCC_BASEOBJ_H_

class CGBaseObj
{
	CGBaseObj();
	~CGBaseObj();

	void Create();
	void Destroy();
	void Frame();
	void Draw();
	void onPush(CGBaseObj *, int);
	void onTalk(CGBaseObj *, int);
};

#endif // _FFCC_BASEOBJ_H_
