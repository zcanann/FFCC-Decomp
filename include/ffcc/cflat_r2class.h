#ifndef _FFCC_CFLAT_R2CLASS_H_
#define _FFCC_CFLAT_R2CLASS_H_

void SAFE_CAST_MON_WORK(CGObjWork *);

class CFlatRuntime2
{
	void onClassSystemFunc(CFlatRuntime::CObject *, int, int, int &);
	void onClassSystemVal(CFlatRuntime::CObject *, int);
	void onSetClassSystemVal(int, CFlatRuntime::CObject *, CFlatRuntime::CStack *, int);
};

#endif // _FFCC_CFLAT_R2CLASS_H_
