#include "ffcc/MenuUtil.h"

extern "C" float GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScaleX__5CFontFf(float, CFont*);
extern "C" void SetScaleY__5CFontFf(float, CFont*);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, _GXColor*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

extern float lbl_80333558;
extern float lbl_8033356C;
extern float lbl_8033358C;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcHelpLine(int, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetLongHelpString(CFont*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos2(char* text, float margin, float scale)
{
	CFont* font = *(CFont**)((unsigned char*)this + 0xF8);

	SetShadow__5CFontFi(font, 1);
	SetMargin__5CFontFf(margin, font);
	SetScaleX__5CFontFf(scale, font);
	SetScaleY__5CFontFf(lbl_8033356C, font);
	return -(GetWidth__5CFontFPc(font, text) * lbl_80333558 - lbl_8033358C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos(char* text, CFont* font)
{
    float width = GetWidth__5CFontFPc(font, text);
    return -(width * lbl_80333558 - lbl_8033358C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawFont(int posX, int posY, _GXColor color, int tlut, char* text, float margin, float scale)
{
	CFont* font = *(CFont**)((unsigned char*)this + 0xF8);

	SetMargin__5CFontFf(margin, font);
	SetShadow__5CFontFi(font, 1);
	SetScale__5CFontFf(scale, font);
	DrawInit__5CFontFv(font);
	SetTlut__5CFontFi(font, tlut);
	SetColor__5CFontF8_GXColor(font, &color);
	SetPosX__5CFontFf((float)posX, font);
	SetPosY__5CFontFf((float)posY, font);
	Draw__5CFontFPc(font, text);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontWidth(char*, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawFont2(int, int, _GXColor, int, char*, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpMessageUS(int, CFont*, int, int, _GXColor, int, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::IsItemEquip(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetCrystalCageAttr()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetManaWaterEffect()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetOptionData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitOptionMenuParam()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcOptionMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawOptionMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::BindMcObj(int)
{
	// TODO
}
