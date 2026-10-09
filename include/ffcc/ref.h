#ifndef _FFCC_REF_H_
#define _FFCC_REF_H_

class CRef
{
public:
	CRef();
	virtual ~CRef();
	void AddRef() { refCount++; }
	int GetRef() { return refCount; }
	void Release()
	{
		if (--refCount == 0) {
			delete this;
		}
	}

	int refCount;
};

#endif
