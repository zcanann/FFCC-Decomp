#ifndef _FFCC_REF_H_
#define _FFCC_REF_H_

class CRef
{
	CRef();
	virtual ~CRef();
	
	int refCount;
};

#endif
