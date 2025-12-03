#ifndef _FFCC_CFLAT_R2SYSTEM_H_
#define _FFCC_CFLAT_R2SYSTEM_H_

class CFlatRuntime;

class CFlatRuntime2
{
	void onSystemFunc(CFlatRuntime::CObject *, int, int, int &);
	void onSystemVal(CFlatRuntime::CObject *, int);
	void onSetSystemVal(int, CFlatRuntime::CStack *, int);
};

#endif // _FFCC_CFLAT_R2SYSTEM_H_
