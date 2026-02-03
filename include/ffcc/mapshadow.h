#ifndef _FFCC_MAPSHADOW_H_
#define _FFCC_MAPSHADOW_H_

#include "types.h"
#include "dolphin/mtx.h"

class CMapPcs;
class COctTree;
class CTexture;

class CMapShadow
{
public:
    enum TARGET
	{
		TODO = 0,
	};
	
	u16 field_0x0;
	u16 field_0x2;
	u16 field_0x4;
	u8 field_0x6;
	u8 field_0x7;
	u32 field_0x8;
	void* field_0xc;
	void* field_0x10;
	void* field_0x14;
	Mtx field_0x18;
	Mtx field_0x48;
	f32 field_0x54;
	f32 field_0x58;
	f32 field_0x5c;
	f32 field_0x60;
	f32 field_0x64;
	f32 field_0x68;
	f32 field_0x6c;
	f32 field_0x70;
	f32 field_0x74;
	Mtx field_0x78;
	f32 field_0xa8;
	f32 field_0xac;
	f32 field_0xb0;
	f32 field_0xb4;
	f32 field_0xb8;
	f32 field_0xbc;
	
    void Init();
    void Calc();
    void Draw();
};

void CMapShadowInsertOctTree(CMapShadow::TARGET, COctTree&);

#endif // _FFCC_MAPSHADOW_H_
