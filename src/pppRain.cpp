#include "ffcc/pppRain.h"
#include "ffcc/memory.h"
#include "ffcc/pppPart.h"
#include "dolphin/gx.h"

extern float lbl_80331018;
extern float lbl_8033101c;
extern int DAT_8032ec70;
extern "C" void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitRainData(VRain*, PRain*, RAIN_DATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateRain(VRain*, PRain*, RAIN_DATA*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800ddacc
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructRain(struct pppRain* pppRain, struct RAIN_DATA* param_2)
{
    float fVar1;
    float* puVar2;
    
    fVar1 = lbl_80331018;
    puVar2 = (float*)((u8*)pppRain + 0x80 + param_2->m_serializedDataOffsets[2]);
    *(u32*)puVar2 = 0;
    puVar2[3] = fVar1;
    puVar2[2] = fVar1;
    puVar2[1] = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x800dda78
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructRain(struct pppRain* pppRain, struct RAIN_DATA* param_2)
{
    int iVar1;
    
    iVar1 = param_2->m_serializedDataOffsets[2];
    if (*(void**)((u8*)pppRain + 0x80 + iVar1) != 0) {
        pppHeapUseRate((CMemory::CStage*)*(void**)((u8*)pppRain + 0x80 + iVar1));
        *(u32*)((u8*)pppRain + 0x80 + iVar1) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800dd648
 * PAL Size: 1072b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameRain(struct pppRain*, struct PRain*, struct RAIN_DATA*)
{
}

/*
 * --INFO--
 * PAL Address: 0x800dd424
 * PAL Size: 548b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderRain(struct pppRain* pppRain, struct PRain* param_2, struct RAIN_DATA* param_3)
{
	int colorOffset = param_3->m_serializedDataOffsets[1];
	int rainDataOffset = param_3->m_serializedDataOffsets[2];
	float* rainData = *(float**)((u8*)pppRain + 0x80 + rainDataOffset);
	u16 count = *(u16*)&param_2->payload[0];

	pppSetBlendMode(param_2->payload[0x48]);
	pppSetDrawEnv(
		(pppCVECTOR*)((u8*)pppRain + 0x88 + colorOffset),
		(pppFMATRIX*)&ppvCameraMatrix0,
		lbl_80331018,
		param_2->payload[0x4a],
		param_2->payload[0x49],
		param_2->payload[0x48],
		(u8)0,
		(u8)1,
		(u8)1,
		(u8)0);

	GXSetNumChans(1);
	GXSetNumTevStages(1);
	GXSetTevDirect(GX_TEVSTAGE0);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GXSetLineWidth(param_2->payload[0x3c], GX_TO_ZERO);
	SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);

	GXBegin(GX_LINES, GX_VTXFMT7, (count & 0x7fff) << 1);

	for (u16 i = 0; i < count; i++) {
		Vec lineDir;
		float px = pppMngStPtr->m_matrix.value[0][3] + rainData[0];
		float py = pppMngStPtr->m_matrix.value[1][3] + rainData[1];
		float pz = pppMngStPtr->m_matrix.value[2][3] + rainData[2];
		u32 color = *(u32*)((u8*)pppRain + 0x88 + colorOffset);

		PSVECScale((Vec*)(rainData + 3), &lineDir, rainData[6]);

		GXPosition3f32(px, py, pz);
		GXColor1u32(color);
		GXTexCoord2f32(lbl_80331018, lbl_80331018);

		GXPosition3f32(px + lineDir.x, py + lineDir.y, pz + lineDir.z);
		GXColor1u32(color);
		GXTexCoord2f32(lbl_8033101c, lbl_8033101c);

		rainData += 8;
	}

	GXSetLineWidth(8, GX_TO_ZERO);
}
