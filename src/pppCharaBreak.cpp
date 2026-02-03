#include "ffcc/pppCharaBreak.h"
#include <dolphin/mtx.h>
#include <dolphin/gx.h>

extern void* CameraPcs;
extern void* MaterialMan;

extern "C" void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned short, int, int);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2CharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801411dc
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411e0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x80140f18
 * PAL Size: 708b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f(CChara::CModel* model, void* param2, void* param3, int param4, float matrix[3][4])
{
	if (*(int*)((char*)param2 + 0x44) != 0) {
		int iVar7 = *(int*)((char*)model + 0xac) + param4 * 0x14;
		int iVar3 = *(int*)((char*)iVar7 + 8);
		int iVar6 = *(int*)((char*)iVar3 + 0x50);
		
		float MStack_68[3][4];
		float MStack_98[3][4];
		
		PSMTXCopy(*((float(*)[3][4])((char*)CameraPcs + 0x70)), MStack_68);
		
		int iVar5 = *(int*)((char*)iVar3 + 0x4c) - 1;
		int iVar3_offset = iVar5 * 4;
		
		for (; iVar5 >= 0; iVar5--) {
			int iVar8 = *(int*)(param4 * 4 + *(int*)((char*)param2 + 0x1c));
			int iVar4 = *(int*)(*(int*)((char*)iVar8 + iVar3_offset) + 0xc);
			
			SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
				&MaterialMan, *(void**)((char*)*(int*)((char*)model + 0xa4) + 0x24),
				*(unsigned short*)((char*)iVar6 + 8), 0, 0);
				
			GXSetZMode((GXBool)1, (GXCompare)3, (GXBool)1);
			GXSetCullMode((GXCullMode)0);
			GXClearVtxDesc();
			GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
			GXSetVtxDesc((GXAttr)10, (GXAttrType)3);
			GXSetVtxDesc((GXAttr)0xb, (GXAttrType)3);
			GXSetVtxDesc((GXAttr)0xd, (GXAttrType)3);
			GXSetVtxDesc((GXAttr)0xe, (GXAttrType)3);
			
			GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)3, *(unsigned int*)((char*)*(int*)((char*)model + 0xa4) + 0x34) & 0xff);
			GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, (GXCompCnt)0, (GXCompType)3, *(unsigned int*)((char*)*(int*)((char*)model + 0xa4) + 0x38) & 0xff);
			GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xb, (GXCompCnt)1, (GXCompType)5, 0);
			GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xd, (GXCompCnt)1, (GXCompType)3, 0xc);
			GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xe, (GXCompCnt)1, (GXCompType)3, 0xc);
			
			if (*(int*)((char*)*(int*)((char*)iVar7 + 8) + 0x54) == 0) {
				GXLoadPosMtxImm(MStack_68, 0);
			} else {
				PSMTXConcat(MStack_68, matrix, MStack_98);
				GXLoadPosMtxImm(MStack_98, 0);
			}
			
			GXBegin((GXPrimitive)0x90, (GXVtxFmt)7, *(short*)(*(int*)((char*)iVar8 + iVar3_offset) + 8) * 3);
			
			int iVar2 = 0;
			while (iVar2 < (int)*(unsigned short*)(*(int*)((char*)iVar8 + iVar3_offset) + 8)) {
				iVar2++;
				
				// Write vertex data to GX FIFO
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x10);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x12);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x14);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x28);
				*(unsigned short*)0xcc008000 = 0;
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x2e);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x2e);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x16);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x18);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x1a);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x2a);
				*(unsigned short*)0xcc008000 = 0;
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x30);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x30);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x1c);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x1e);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x20);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x2c);
				*(unsigned short*)0xcc008000 = 0;
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x32);
				*(unsigned short*)0xcc008000 = *(unsigned short*)((char*)iVar4 + 0x32);
				
				iVar4 += 0x34;
			}
			
			iVar3_offset -= 4;
			iVar6 += 0xc;
		}
	}
}
