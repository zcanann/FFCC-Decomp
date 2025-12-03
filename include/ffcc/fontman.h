#ifndef _FFCC_FONTMAN_H_
#define _FFCC_FONTMAN_H_

struct _GXColor;
class CMemory;

void GXEnd(void);
void GXSetTexCoordGen(void);

class CFontMan
{
public:
	CFontMan();
	~CFontMan();

	void Init();
	void Quit();
	void GetInternal22Size();
};

class CFont
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

	void GetWidth(char*);
	void GetWidth(unsigned short);

	void searchChar(unsigned short);
	void getNextChar(char**, unsigned short*);
};

#endif // _FFCC_FONTMAN_H_
