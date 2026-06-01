#ifndef _FFCC_REF_H_
#define _FFCC_REF_H_

class CRef
{
public:
	CRef();
	virtual ~CRef();
	void AddRef() { refCount++; }
	int DecRef() { return --refCount; }
	int GetRef() { return refCount; }

private:
	int refCount;
};

#endif
