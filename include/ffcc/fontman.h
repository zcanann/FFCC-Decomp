#ifndef _FFCC_FONTMAN_H_
#define _FFCC_FONTMAN_H_

#include "ffcc/memory.h"
#include "ffcc/ref.h"
#include "ffcc/textureman.h"

#include <dolphin/gx.h>

class CFont;

class CFontMan
{
public:
	CFontMan();
	virtual ~CFontMan();

	void Init();
	void Quit();
	unsigned long GetInternal22Size();

	CMemory::CStage* m_stage;
	CFont* m_font;
};

class CFont : public CRef
{
public:
	CFont();
	~CFont();

	static void* operator new(unsigned long, CMemory::CStage*, char*, int);

	void Create(void*, CMemory::CStage*);

	void SetPosX(float);
	void SetPosY(float);
	void SetPosZ(float);

	void SetZMode(int, int);

	void SetMargin(float);
	void SetScale(float);
	void SetScaleX(float);
	void SetScaleY(float);

	void SetShadow(int);
	void SetColor(_GXColor);
	void SetTlut(int);
	void SetTlutColor(int, int, _GXColor);
	void FlushTlutColor();

	void DrawInit();
	void DrawQuit();
	void Draw(char*);
	void Draw(unsigned short);

	float GetWidth(char*);
	float GetWidth(unsigned short);

	void searchChar(unsigned short);
	void getNextChar(char**, unsigned short*);

	unsigned short m_glyphWidth;
	unsigned short m_glyphHeight;
	unsigned short m_glyphColumns;
	unsigned char m_usesEmbeddedData;
	unsigned char m_pad0f;
	float posX;
	float posY;
	float posZ;
	float margin;
	float scaleX;
	float scaleY;
	unsigned char m_pad28[7];
	unsigned char renderFlags;
	_GXColor m_color;
	CTexture* texturePtr;
	void* m_glyphData;
	unsigned short* m_glyphBuckets[64];
	unsigned char m_pad13c[0x304];
	unsigned char m_tlutData[0x400];
};

#endif // _FFCC_FONTMAN_H_
