#include "ffcc/p_chara_viewer.h"
#include "dolphin/mtx.h"

extern "C" int DAT_8032edc0;
extern "C" unsigned char Chara[];
extern "C" unsigned char LightPcs[];
extern "C" unsigned char Memory[];
extern "C" unsigned char Graphic[];
extern "C" unsigned char File[];
extern "C" unsigned char USBPcs[];
extern "C" void Destroy__6CCharaFv(void*);
extern "C" void Create__6CCharaFv(void*);
extern "C" void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(void*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" void SetCopyClear__8CGraphicF8_GXColori(void*, void*, int);
extern "C" void* Open__5CFileFPcUlQ25CFile3PRI(void*, char*, unsigned long, int);
extern "C" void Read__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void SyncCompleted__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void Close__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void* createTextureSet__9CCharaPcsFPvi(void*, void*, int);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);
extern "C" int AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
    void*, void*, int, void*, int);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void __ct__6CColorFv(void*);
extern "C" void __ct__6CColorFR6CColor(void*, void*);
extern "C" char lbl_801DA7E8[];
extern "C" float lbl_80330BE8;
extern "C" float lbl_80330C28;
extern "C" float lbl_80330C2C;
extern "C" float lbl_80330C48;
extern "C" float lbl_80330C4C;
extern "C" float lbl_80330C50;
extern "C" float lbl_80330C54;
extern "C" float lbl_80330C58;
extern "C" float lbl_80330C5C;
extern "C" char lbl_80330C44[];
extern "C" double lbl_80330BE0;
extern "C" double lbl_80330C10;
extern "C" void* memset(void*, int, unsigned long);
extern "C" char* strcpy(char*, const char*);
extern "C" int sprintf(char*, const char*, ...);

namespace {
static void releaseRef(void** slot)
{
    int* ref = (int*)*slot;
    if (ref != 0) {
        int count = ref[1] - 1;
        ref[1] = count;
        if (count == 0) {
            (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
        }
        *slot = 0;
    }
}
} // namespace

/*
 * --INFO--
 * PAL Address: 0x800BF094
 * PAL Size: 1420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void createViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    unsigned int i;
    unsigned int x;
    unsigned char colorTmp[4];
    unsigned char white[4];
    char pathBuf[256];
    void* fileHandle;
    unsigned char bumpLight[0x138];
    Vec lightPos;
    Vec lightTarget;
    Vec lightDir;

    memset(p + 0xCC, 0, 0x18);
    *(void**)(p + 0xCC) = CreateStage__7CMemoryFUlPci(Memory, 0x177000, lbl_801DA7E8 + 0xDC, 0);
    *(void**)(p + 0xD0) = CreateStage__7CMemoryFUlPci(Memory, 0x200000, lbl_801DA7E8 + 0xF0, 0);
    *(void**)(p + 0xD4) = CreateStage__7CMemoryFUlPci(Memory, 0x190000, lbl_801DA7E8 + 0x108, 0);

    p[0xE8] = 0x3F;
    p[0xE9] = 0x3F;
    p[0xEA] = 0x3F;
    p[0xEB] = 0xFF;
    p[0xF0] = 0x3F;
    p[0xF1] = 0x3F;
    p[0xF2] = 0x3F;
    p[0xF3] = 0xFF;
    p[0xF4] = 0;
    p[0xF5] = 0;
    p[0xF6] = 0;
    p[0xF7] = 0xFF;
    p[0xF8] = 0;
    p[0xF9] = 0;
    p[0xFA] = 0;
    p[0xFB] = 0xFF;
    *(float*)(p + 0x108) = lbl_80330BE8;
    *(float*)(p + 0x10C) = lbl_80330BE8;
    *(float*)(p + 0x110) = lbl_80330C28;
    *(float*)(p + 0x114) = lbl_80330BE8;
    *(float*)(p + 0x118) = lbl_80330BE8;
    *(float*)(p + 0x11C) = lbl_80330C28;
    *(float*)(p + 0x120) = lbl_80330BE8;
    *(float*)(p + 0x124) = lbl_80330BE8;
    *(float*)(p + 0x128) = lbl_80330C28;

    for (i = 0; i < 5; i++) {
        __ct__6CColorFUcUcUcUc(white, 0xFF, 0xFF, 0xFF, 0xFF);
        __ct__6CColorFv(colorTmp);
        x = i ^ 0x80000000;
        for (int c = 0; c < 4; c++) {
            double v = (double)(float)(((double)(unsigned int)white[c] - lbl_80330C10) *
                                        ((float)((double)x - lbl_80330BE0) * lbl_80330C2C));
            colorTmp[c] = (unsigned char)(int)v;
        }
        __ct__6CColorFR6CColor(p + 0x12C + i * 4, colorTmp);
    }

    *(unsigned int*)(p + 0x0C) = 0x404040FF;
    SetCopyClear__8CGraphicF8_GXColori(Graphic, p + 0x0C, 0xFFFF);

    *(int*)(p + 0x190) = 0;
    *(int*)(p + 0x194) = 0;
    *(int*)(p + 0x198) = 0;
    *(int*)(p + 0x19C) = 0;
    *(int*)(p + 0x1A0) = 0;
    *(int*)(p + 0x2B0) = 0;
    *(int*)(p + 0x2B4) = 0;
    *(int*)(p + 0x2B8) = 0;
    *(int*)(p + 0x2BC) = 0;
    *(int*)(p + 0x3C0) = 0;
    *(int*)(p + 0x4C4) = 0;
    *(int*)(p + 0x5C8) = 0;
    *(int*)(p + 0x6F4) = 0;
    *(int*)(p + 0x6F8) = 1;
    *(int*)(p + 0x6FC) = 0;
    *(float*)(p + 0x700) = lbl_80330BE8;
    *(int*)(p + 0x704) = 0;
    *(int*)(p + 0x708) = 0;
    *(int*)(p + 0x70C) = 0;
    *(int*)(p + 0x710) = 0;
    *(int*)(p + 0x1A4) = 0;
    *(int*)(p + 0x1A8) = 0;
    *(int*)(p + 0x1AC) = 0;
    memset(p + 0x1B0, 0, 0x100);

    strcpy((char*)(p + 0x2C0), lbl_801DA7E8 + 0x11C);
    *(int*)(p + 0x2BC) = 1;
    strcpy((char*)(p + 0x5F4), lbl_801DA7E8 + 0x134);
    *(int*)(p + 0x5F0) = 1;
    strcpy((char*)(p + 0x3C4), lbl_801DA7E8 + 0x14C);
    *(int*)(p + 0x3C0) = 1;
    strcpy((char*)(p + 0x4C8), lbl_801DA7E8 + 0x164);
    *(int*)(p + 0x4C4) = 1;
    strcpy((char*)(p + 0x5CC), lbl_80330C44);
    *(int*)(p + 0x5EC) = -1;
    *(int*)(p + 0x5C8) = 1;

    sprintf(pathBuf, lbl_801DA7E8 + 0x17C, *(unsigned int*)(USBPcs + 4));
    fileHandle = Open__5CFileFPcUlQ25CFile3PRI(File, pathBuf, 0, 0);
    if (fileHandle != 0) {
        Read__5CFileFPQ25CFile7CHandle(File, fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(File, fileHandle);
        *(void**)(p + 0x2B8) = createTextureSet__9CCharaPcsFPvi(p, *(void**)(File + 8), 0);
        Close__5CFileFPQ25CFile7CHandle(File, fileHandle);
    }

    __ct__Q29CLightPcs10CBumpLightFv(bumpLight);
    *(int*)(bumpLight + 0x00) = 1;
    lightPos.x = lbl_80330C48;
    lightPos.y = lbl_80330C4C;
    lightPos.z = lbl_80330C50;
    lightTarget.x = lbl_80330C54;
    lightTarget.y = lbl_80330C58;
    lightTarget.z = lbl_80330C5C;
    PSVECSubtract(&lightTarget, &lightPos, &lightDir);
    PSVECNormalize(&lightDir, &lightDir);
    *(unsigned char*)(bumpLight + 0x68) = 0x80;
    *(unsigned char*)(bumpLight + 0x69) = 0x80;
    *(unsigned char*)(bumpLight + 0x6A) = 0;
    *(unsigned char*)(bumpLight + 0x6B) = 0xFF;
    *(float*)(bumpLight + 0x2C) = lbl_80330BE8;
    *(float*)(bumpLight + 0x30) = lbl_80330BE8;
    DAT_8032edc0 = AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
        LightPcs, bumpLight, 0, *(void**)(Chara + 0x2058), 4);

    Create__6CCharaFv(Chara);
}

/*
 * --INFO--
 * PAL Address: 0x800BEE50
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void destroyViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    unsigned int i;

    Destroy__6CCharaFv(Chara);
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(LightPcs, 0);
    DAT_8032edc0 = 0;

    releaseRef((void**)(p + 0x1A0));

    i = 0;
    do {
        releaseRef((void**)(p + 0x190 + i * 4));
        releaseRef((void**)(p + 0x198 + i * 4));
        releaseRef((void**)(p + 0x2B0 + i * 4));
        i++;
    } while (i < 2);

    releaseRef((void**)(p + 0x2B8));

    i = 0;
    do {
        releaseRef((void**)(p + 0x1B0 + i * 4));
        i++;
    } while (i < 0x40);

    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xCC));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xD0));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xD4));
}
