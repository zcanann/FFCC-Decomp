#include "ffcc/p_menu.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/game.h"
#include "ffcc/map.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/menu.h"
#include "ffcc/mesmenu.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/ptrarray.h"
#include "ffcc/ringmenu.h"
#include "ffcc/textureman.h"
#include "ffcc/fontman.h"

#include <dolphin/mtx.h>
#include <math.h>

extern CTextureMan TextureMan;
extern CMath Math;
extern CMenuPcs MenuPcs;
extern CGame Game;
extern CFontMan FontMan;

struct Vec4d
{
    float x;
    float y;
    float z;
    float w;
};
extern unsigned char lbl_8020ee40[];
extern u8 ARRAY_802ea1a0[];
extern u32 PTR_PTR_s_CMenuPcs_8020f2d0;
extern u32 DAT_8020edf8;
extern u32 DAT_8020edfc;
extern u32 PTR_create__8CMenuPcsFv_8020ee00;
extern u32 DAT_8020ee04;
extern u32 DAT_8020ee08;
extern u32 PTR_destroy__8CMenuPcsFv_8020ee0c;
extern u32 DAT_8020ee10;
extern u32 DAT_8020ee14;
extern u32 PTR_calc__8CMenuPcsFv_8020ee18;
extern u32 DAT_8020ee1c;
extern u32 DAT_8020ee20;
extern u32 PTR_draw__8CMenuPcsFv_8020ee24;
extern u32 DAT_8020ee28;
extern u32 DAT_8020ee2c;
extern u32 PTR_loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii_8020ee30;
extern u32 DAT_8020ee34;
extern u32 DAT_8020ee38;
extern u32 PTR_drawSingleMenu__8CMenuPcsFv_8020ee3c;
extern u32 DAT_8020ee44;
extern u32 DAT_8020ee48;
extern u32 DAT_8020ee4c;
extern u32 DAT_8020ee50;
extern u32 DAT_8020ee54;
extern u32 DAT_8020ee58;
extern u32 DAT_8020ee5c;
extern u32 DAT_8020ee60;
extern u32 DAT_8020ee64;
extern u32 DAT_8020ee70;
extern u32 DAT_8020ee74;
extern u32 DAT_8020ee78;
extern u32 DAT_8020ee84;
extern u32 DAT_8020ee88;
extern u32 DAT_8020ee8c;
extern u32 DAT_8020ee98;
extern u32 DAT_8020ee9c;
extern u32 DAT_8020eea0;
extern char* PTR_s_shibuya_8020f23c[];
extern int DAT_8020f260[];
extern char s_dvd__smenu__s_tex_801d9d6c[];
extern char s_dvd__smenu_gc23_fnt_801d9d8c[];
extern char s_p_menu_cpp_801d9d80[];

extern "C" void* __register_global_object(void* object, void* destructor, void* registration);
extern "C" void __dt__8CMenuPcsFv(void*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void Calc__5CMenuFv(CMenu*);
extern "C" void CalcDiaryMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void calcBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void calcVillageMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void* Open__5CFileFPcUlQ25CFile3PRI(void*, char*, unsigned long, int);
extern "C" void Read__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void SyncCompleted__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void Close__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void drawBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void drawVillageMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void createBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroyBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void createSingleMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroySingleMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroyVillageMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, unsigned char, int, int, unsigned char);
extern "C" unsigned char Graphic[];
extern "C" unsigned char CFlat[];

static inline void ReleaseRefObject(void* object)
{
    if (object == nullptr) {
        return;
    }

    u32* raw = reinterpret_cast<u32*>(object);
    int refCount = static_cast<int>(raw[1]);
    raw[1] = static_cast<u32>(refCount - 1);
    if (refCount - 1 == 0) {
        reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<u32*>(raw[0] + 8))(object, 1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80097618
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_menu_cpp()
{
    *(u32*)((u8*)&MenuPcs) = (u32)&PTR_PTR_s_CMenuPcs_8020f2d0;
    __register_global_object(&MenuPcs, reinterpret_cast<void*>(__dt__8CMenuPcsFv), ARRAY_802ea1a0);

    DAT_8020ee44 = DAT_8020edf8;
    DAT_8020ee48 = DAT_8020edfc;
    DAT_8020ee4c = PTR_create__8CMenuPcsFv_8020ee00;
    DAT_8020ee50 = DAT_8020ee04;
    DAT_8020ee54 = DAT_8020ee08;
    DAT_8020ee58 = PTR_destroy__8CMenuPcsFv_8020ee0c;
    DAT_8020ee5c = DAT_8020ee10;
    DAT_8020ee60 = DAT_8020ee14;
    DAT_8020ee64 = PTR_calc__8CMenuPcsFv_8020ee18;
    DAT_8020ee70 = DAT_8020ee1c;
    DAT_8020ee74 = DAT_8020ee20;
    DAT_8020ee78 = PTR_draw__8CMenuPcsFv_8020ee24;
    DAT_8020ee84 = DAT_8020ee28;
    DAT_8020ee88 = DAT_8020ee2c;
    DAT_8020ee8c = PTR_loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii_8020ee30;
    DAT_8020ee98 = DAT_8020ee34;
    DAT_8020ee9c = DAT_8020ee38;
    DAT_8020eea0 = PTR_drawSingleMenu__8CMenuPcsFv_8020ee3c;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMenuPcs::CMenuPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMenuPcs::~CMenuPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80097490
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetTable(unsigned long index)
{
    unsigned char* table = lbl_8020ee40;
    unsigned long offset = index * 0x15c;
    return (int)(table + offset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800970e0
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroy()
{
    changeMode(static_cast<CMenuPcs::MENUMODE>(-1));

    u8* self = reinterpret_cast<u8*>(this);
    for (int i = 0; i < 0x16; i++) {
        u8* slot = self + 0x18c + i * 4;
        ReleaseRefObject(*reinterpret_cast<void**>(slot));
        *reinterpret_cast<void**>(slot) = nullptr;
    }

    for (int i = 0; i < 2; i++) {
        u8* slot = self + 0x14c + i * 4;
        ReleaseRefObject(*reinterpret_cast<void**>(slot));
        *reinterpret_cast<void**>(slot) = nullptr;
    }

    ReleaseRefObject(*reinterpret_cast<void**>(self + 0xf8));
    *reinterpret_cast<void**>(self + 0xf8) = nullptr;

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(self + 0xec));
    if (*(self + 0x859) != 0) {
        *reinterpret_cast<void**>(self + 0xf0) = nullptr;
        *(self + 0x859) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80096d98
 * PAL Size: 840b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::loadFont(int type, char* path, int slot, int tlutMode)
{
    CMemory::CStage* stage = 0;
    u8* self = reinterpret_cast<u8*>(this);

    if (type == 1) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF0);
    } else if (type == 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    } else if (type < 3) {
        stage = pppEnvStPtr->m_stagePtr;
    }

    CFont** fontSlot = reinterpret_cast<CFont**>(self + 0xF8 + slot * 4);
    if ((slot == 0) && (FontMan.m_font != 0)) {
        *fontSlot = FontMan.m_font;
        reinterpret_cast<u32*>(*fontSlot)[1] = reinterpret_cast<u32*>(*fontSlot)[1] + 1;
    } else {
        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        CFont* font = new (Game.m_mainStage, s_p_menu_cpp_801d9d80, 0xF8) CFont;
        *fontSlot = font;
        if (font != 0) {
            font->Create(File.m_readBuffer, stage);
        }

        File.Close(fileHandle);
    }

    if (tlutMode < 2) {
        const _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
        for (int tlut = 0; tlut < 0x10; tlut++) {
            for (int i = 0; i < 0x1C; i++) {
                (*fontSlot)->SetTlutColor(tlut, i, white);
                (*fontSlot)->SetTlutColor(tlut, i + 0x1C, white);
            }
        }
        (*fontSlot)->FlushTlutColor();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::loadTexture(char **, int, int, CMenuPcs::CTmp*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::freeTexture(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80096800
 * PAL Size: 668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::changeMode(CMenuPcs::MENUMODE mode)
{
    u8* self = reinterpret_cast<u8*>(this);
    int currentMode = *reinterpret_cast<int*>(self + 0x740);

    if (currentMode == static_cast<int>(mode)) {
        return;
    }

    _WaitDrawDone__8CGraphicFPci(Graphic, s_p_menu_cpp_801d9d80, 0x1B0);

    if (currentMode == 1) {
        destroyWorld();
    } else if (currentMode < 1) {
        if (currentMode != -1 && currentMode > -2) {
            ReleaseRefObject(*reinterpret_cast<void**>(self + 0xFC));
            *reinterpret_cast<void**>(self + 0xFC) = nullptr;

            for (int i = 0; i < 10; i++) {
                u8* slot = self + 0x1E4 + i * 4;
                ReleaseRefObject(*reinterpret_cast<void**>(slot));
                *reinterpret_cast<void**>(slot) = nullptr;
            }

            for (int i = 0; i < 2; i++) {
                u8* slot = self + 0x154 + i * 4;
                ReleaseRefObject(*reinterpret_cast<void**>(slot));
                *reinterpret_cast<void**>(slot) = nullptr;
            }

            for (int i = 0; i < 4; i++) {
                u8* slot = self + 0x13C + i * 4;
                ReleaseRefObject(*reinterpret_cast<void**>(slot));
                *reinterpret_cast<void**>(slot) = nullptr;
            }

            for (int i = 0; i < 12; i++) {
                u8* slot = self + 0x10C + i * 4;
                ReleaseRefObject(*reinterpret_cast<void**>(slot));
                *reinterpret_cast<void**>(slot) = nullptr;
            }

            destroySingleMenu__8CMenuPcsFv(this);
            destroyVillageMenu__8CMenuPcsFv(this);
        }
    } else if (currentMode < 3) {
        destroyBonus__8CMenuPcsFv(this);
    }

    *reinterpret_cast<int*>(self + 0x740) = static_cast<int>(mode);
    currentMode = *reinterpret_cast<int*>(self + 0x740);

    if (currentMode == 1) {
        createWorld();
    } else if (currentMode < 1) {
        if (currentMode != -1 && currentMode > -2) {
            createBattle();
            createSingleMenu__8CMenuPcsFv(this);
        }
    } else if (currentMode < 3) {
        createBonus__8CMenuPcsFv(this);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800966e8
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calc()
{
    u8* self = reinterpret_cast<u8*>(this);
    int mode = *reinterpret_cast<int*>(self + 0x740);

    if (mode == 1) {
        CalcDiaryMenu__8CMenuPcsFv(this);
    } else if (mode < 1) {
        if (mode >= 0) {
            for (int i = 0; i < 4; i++) {
                Calc__5CMenuFv(*reinterpret_cast<CMenu**>(self + 0x13c + i * 4));
            }

            for (int i = 0; i < 0xc; i++) {
                Calc__5CMenuFv(*reinterpret_cast<CMenu**>(self + 0x10c + i * 4));
            }

            int limit = *reinterpret_cast<int*>(self + 0x68);
            int value = *reinterpret_cast<int*>(self + 0x6c) - 1;
            if (value <= limit) {
                int alt = *reinterpret_cast<int*>(self + 0x6c) + 1;
                value = limit;
                if (alt < limit) {
                    value = alt;
                }
            }
            *reinterpret_cast<int*>(self + 0x6c) = value;

            u32 counter = *reinterpret_cast<u32*>(self + 0x58) - 1;
            *reinterpret_cast<u32*>(self + 0x58) = counter & ~((int)counter >> 31);
            counter = *reinterpret_cast<u32*>(self + 0x5c) - 1;
            *reinterpret_cast<u32*>(self + 0x5c) = counter & ~((int)counter >> 31);

            calcVillageMenu__8CMenuPcsFv(this);
        }
    } else if (mode < 3) {
        calcBonus__8CMenuPcsFv(this);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009631c
 * PAL Size: 972b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::draw()
{
    Mtx modelMtx;
    Mtx texMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    C_MTXOrtho(orthoMtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        GXSetChanAmbColor(GX_COLOR0A0, white.color);
    }
    GXSetZCompLoc(GX_FALSE);
    GXSetCurrentMtx(0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);

    {
        int mode = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x740);

        if (mode == 1) {
            drawWorld();
        } else if (mode < 1) {
            if (mode >= 0) {
                drawBattle();
                drawVillageMenu__8CMenuPcsFv(this);
            }
        } else if (mode < 3) {
            drawBonus__8CMenuPcsFv(this);
        }
    }

    if (((*reinterpret_cast<unsigned int*>(CFlat + 0x12A0) & 0x10) != 0) && (System.m_scenegraphStepMode == 2)) {
        CTexture* texture = *reinterpret_cast<CTexture**>(reinterpret_cast<u8*>(this) + 0x190);
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        if (texture != nullptr) {
            float width = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x64));
            float height = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x68));
            PSMTXScale(texMtx, 1.0f / width, 1.0f / height, 1.0f);
            GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
            GXSetNumTexGens(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        }

        TextureMan.SetTextureTev(texture);

        {
            int alpha = static_cast<int>(127.5f * (1.0f + sinf(System.m_frameCounter * 0.1f)));
            CColor color(0xFF, 0xFF, 0xFF, static_cast<u8>(alpha));
            GXSetChanMatColor(GX_COLOR0A0, color.color);
            DrawRect(3, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x48), screenMtx);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetAttrFmt(CMenuPcs::FMT)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawQuit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetButtonDown(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetButtonRepeat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::onMapChanging(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::onMapChanged(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80095bd0
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetTexture(CMenuPcs::TEX tex)
{
    CTexture* texture;
    Mtx texMtx;

    if ((int)tex == -1) {
        texture = 0;
    } else {
        CTexture** textures = (CTexture**)((u8*)this + 0x18C);
        u32 width;
        u32 height;

        texture = textures[(int)tex];
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        width = *(u32*)((u8*)texture + 0x64);
        height = *(u32*)((u8*)texture + 0x68);
        PSMTXScale(texMtx, 1.0f / (f32)width, 1.0f / (f32)height, 1.0f);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    }

    TextureMan.SetTextureTev(texture);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawRect(unsigned long, float, float, float, float, float, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawRect(unsigned long, float, float, float, float, float, float, _GXColor*, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawBar(float, float, float, CMenuPcs::TEX, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawWindow(float x, float y, float width, float height, CMenuPcs::TEX texBase, float corner)
{
	if (width <= 0.0f || height <= 0.0f) {
		return;
	}

	const float twoCorner = corner * 2.0f;
	float midW = width - twoCorner;
	float midH = height - twoCorner;
	float overW = twoCorner - width;
	float overH = twoCorner - height;
	float uOff = 0.0f;
	float vOff = 0.0f;
	const int tex = static_cast<int>(texBase);
	const float xL = x;
	const float yT = y;
	const float xM = x + corner;
	const float yM = y + corner;
	const float xR = (x + width) - corner;
	const float yB = (y + height) - corner;

	if (midW < 0.0f) {
		midW = 0.0f;
	}
	if (midH < 0.0f) {
		midH = 0.0f;
	}
	if (overW < 0.0f) {
		overW = 0.0f;
	}
	if (overH < 0.0f) {
		overH = 0.0f;
	}
	if (corner > 0.0f) {
		uOff = overW / twoCorner;
		vOff = overH / twoCorner;
	}

	SetTexture(static_cast<CMenuPcs::TEX>(tex));
	DrawRect(0, xL, yT, corner, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
	DrawRect(0, xM, yT, midW, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 2));
	DrawRect(0, xR, yT, corner, corner, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 3));
	DrawRect(0, xL, yM, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 4));
	DrawRect(0, xM, yM, midW, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 5));
	DrawRect(0, xR, yM, corner, midH, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 6));
	DrawRect(0, xL, yB, corner, corner, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 7));
	DrawRect(0, xM, yB, midW, corner, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 8));
	DrawRect(0, xR, yB, corner, corner, uOff, vOff, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetColor(CColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LoadExtraFont(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetExtraFontTlut(int, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::drawPause()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009460c
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createBattle()
{
    char path[0x104];
    char fontPath[0x80];
    int* textureInfo = DAT_8020f260;
    u8* self = reinterpret_cast<u8*>(this);

    for (int i = 0; i < 2; i++) {
        const char* language = Game.GetLangString();
        sprintf(path, s_dvd__smenu__s_tex_801d9d6c, language, PTR_s_shibuya_8020f23c[i]);

        void* fileHandle = Open__5CFileFPcUlQ25CFile3PRI(&File, path, 0, 0);
        if (fileHandle != 0) {
            Read__5CFileFPQ25CFile7CHandle(&File, fileHandle);
            SyncCompleted__5CFileFPQ25CFile7CHandle(&File, fileHandle);

            void* stage = *reinterpret_cast<int*>(self + 0x740) == 1 ? *reinterpret_cast<void**>(&MapMng)
                                                                     : *reinterpret_cast<void**>(self + 0xEC);

            CTextureSet* textureSet = new (Game.m_mainStage, s_p_menu_cpp_801d9d80, 0x182) CTextureSet;
            *reinterpret_cast<CTextureSet**>(self + 0x14C + i * 4) = textureSet;
            if (textureSet != 0) {
                textureSet->Create(File.m_readBuffer, reinterpret_cast<CMemory::CStage*>(stage), 0, 0, 0, 0);
            }

            Close__5CFileFPQ25CFile7CHandle(&File, fileHandle);
        }
    }

    for (int i = 0; i < 10; i++) {
        CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(self + 0x14C + textureInfo[0] * 4);
        const unsigned long textureIndex = static_cast<unsigned long>(textureSet->Find(reinterpret_cast<char*>(textureInfo[1])));
        CTexture* texture = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(textureSet) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        *reinterpret_cast<CTexture**>(self + 0x1E4 + i * 4) = texture;
        textureInfo += 2;
    }

    for (int i = 0; i < 12; i++) {
        CMesMenu* menu = new (Game.m_mainStage, s_p_menu_cpp_801d9d80, 0x48B) CMesMenu;
        *reinterpret_cast<CMesMenu**>(self + 0x10C + i * 4) = menu;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(menu) + 0x18) = i;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(menu) + 0x1C) = i;
        menu->Create();
    }

    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = new (Game.m_mainStage, s_p_menu_cpp_801d9d80, 0x492) CRingMenu;
        *reinterpret_cast<CRingMenu**>(self + 0x13C + i * 4) = menu;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(menu) + 8) = i;
        menu->Create();
    }

    sprintf(fontPath, s_dvd__smenu_gc23_fnt_801d9d8c, Game.GetLangString());
    loadFont(0, fontPath, 1, 1);

    CTexture* fontTexture = *reinterpret_cast<CTexture**>(self + 0x1EC);
    for (int i = 0; i < 0x100; i++) {
        _GXColor color = fontTexture->GetTlutColor(i);
        const int avg2 = (((int)color.r + (int)color.g + (int)color.b) / 3) * 2;
        _GXColor outColor;
        outColor.r = static_cast<u8>(((int)color.r + avg2) / 3);
        outColor.g = static_cast<u8>(((int)color.g + avg2) / 3);
        outColor.b = static_cast<u8>(((int)color.b + avg2) / 3);
        outColor.a = color.a;

        const int tlutFmt = *reinterpret_cast<int*>(reinterpret_cast<u8*>(fontTexture) + 0x60);
        int tlutOffset = 0;
        if (tlutFmt == 9) {
            tlutOffset = 0x100;
        } else if (tlutFmt == 8) {
            tlutOffset = 0x10;
        }

        fontTexture->SetExternalTlutColor(self + 0x340, tlutOffset, i, outColor);
    }

    fontTexture->FlushExternalTlut(self + 0x340);
    *reinterpret_cast<u16*>(self + 0x864) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroyBattle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcBattle()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80093ec4
 * PAL Size: 1864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawBattle()
{
    u8* self = reinterpret_cast<u8*>(this);

    if (*reinterpret_cast<s32*>(self + 0x48) != 0) {
        const float frame = static_cast<float>(*reinterpret_cast<s32*>(self + 0x58));
        float fade = 1.0f - (frame * 0.05f);
        if (fade < 0.0f) {
            fade = 0.0f;
        }

        Mtx44 screenMtx;
        Vec4d projected;
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x48), screenMtx);
        Math.MTX44MultVec4(screenMtx, reinterpret_cast<Vec*>(self + 0x4C), &projected);

        if (projected.w > 0.0f) {
            const int totalWidth = static_cast<int>(static_cast<float>(*reinterpret_cast<s32*>(self + 0x60)) * fade);
            const int halfWidth = totalWidth / 2;
            float screenX = 320.0f + (320.0f * projected.x) / projected.w;
            float screenY = 240.0f - (240.0f * projected.y) / projected.w;

            if (screenX < static_cast<float>(halfWidth)) {
                screenX = static_cast<float>(halfWidth);
            } else {
                const float right = 640.0f - static_cast<float>(halfWidth);
                if (screenX > right) {
                    screenX = right;
                }
            }

            if (screenY < 32.0f) {
                screenY = 32.0f;
            } else if (screenY > 448.0f) {
                screenY = 448.0f;
            }

            int fillWidth = 0;
            if (*reinterpret_cast<s32*>(self + 0x64) != 0) {
                fillWidth = ((totalWidth - 16) * *reinterpret_cast<s32*>(self + 0x6C)) /
                            *reinterpret_cast<s32*>(self + 0x64);
            }

            const float left = screenX - static_cast<float>(halfWidth);
            const float bodyLeft = left + 8.0f;
            const float alphaF = 80.0f * fade;
            const u8 alpha = static_cast<u8>(alphaF < 0.0f ? 0.0f : (alphaF > 255.0f ? 255.0f : alphaF));
            const CColor frameColor(0xFF, 0xFF, 0xFF, alpha);
            GXSetChanMatColor(GX_COLOR0A0, frameColor.color);

            if (totalWidth > 0) {
                CTexture* tex = *reinterpret_cast<CTexture**>(self + 0x500);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, left, screenY, 8.0f, 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

                tex = *reinterpret_cast<CTexture**>(self + 0x504);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, bodyLeft, screenY, static_cast<float>(totalWidth - 16), 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

                tex = *reinterpret_cast<CTexture**>(self + 0x508);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, (left + static_cast<float>(totalWidth)) - 8.0f, screenY, 8.0f, 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
            }

            const u8 gauge = static_cast<u8>((*reinterpret_cast<s32*>(self + 0x5C) * 0xFF) >> 4);
            const CColor fillTop(0xFF, gauge, gauge, alpha);
            GXSetChanMatColor(GX_COLOR0A0, fillTop.color);
            TextureMan.SetTextureTev(0);
            DrawRect(0, bodyLeft, screenY + 1.0f, static_cast<float>(fillWidth), 3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

            const u8 gaugeTop = static_cast<u8>(((*reinterpret_cast<s32*>(self + 0x5C) * 0x7F) >> 4) + 0x80);
            const CColor fillBottom(0xFF, gaugeTop, gauge, alpha);
            GXSetChanMatColor(GX_COLOR0A0, fillBottom.color);
            DrawRect(0, bodyLeft, screenY + 4.0f, static_cast<float>(fillWidth), 3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    for (int i = 0; i < 4; i++) {
        CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x13C + i * 4);
        if (menu != 0) {
            menu->Draw();
        }
    }
    for (int i = 0; i < 12; i++) {
        CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x10C + i * 4);
        if (menu != 0) {
            menu->Draw();
        }
    }
    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = *reinterpret_cast<CRingMenu**>(self + 0x13C + i * 4);
        if (menu != 0) {
            menu->DrawIcon();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChgPlayModeFromScript(bool)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetTexture(CMenuPcs::TEX)
{
	// TODO
}
