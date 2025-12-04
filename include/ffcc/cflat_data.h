#ifndef _FFCC_CFLAT_DATA_H_
#define _FFCC_CFLAT_DATA_H_

class CFlatData
{
	CFlatData();
	~CFlatData();

	void Create(void *);
	void Destroy();

    char placeholderData[0x14D4];
};

#endif // _FFCC_CFLAT_DATA_H_
