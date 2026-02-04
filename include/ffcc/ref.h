#ifndef _FFCC_REF_H_
#define _FFCC_REF_H_

class CRef
{
public:
	CRef();
	virtual ~CRef();

private:
	int refCount;
};

#endif
