#ifndef _FFCC_FUNNYSHAPE_H_
#define _FFCC_FUNNYSHAPE_H_

#include "ffcc/FS_USB_Process.h"
#include "ffcc/pppVec.h"

struct FS_tagOAN3_SPRITE
{
    u8 unk00[8];       // 0x00
    GXColor color;     // 0x08
    u8 blendMode;      // 0x0C
    u8 unk0D[3];       // 0x0D
    s16 left;          // 0x10
    s16 top;           // 0x12
    s16 right;         // 0x14
    s16 bottom;        // 0x16
    s16 texX;          // 0x18
    s16 texY;          // 0x1A
    s16 texW;          // 0x1C
    s16 texH;          // 0x1E
    u8 texIndex;       // 0x20
    u8 unk21[3];       // 0x21
};

struct FS_tagOAN3_QUAD
{
    u8 unk00[8];       // 0x00
    GXColor color;     // 0x08
    u8 blendMode;      // 0x0C
    u8 unk0D[3];       // 0x0D
    s16 vertex[4][2];  // 0x10
    s16 texX;          // 0x20
    s16 texY;          // 0x22
    s16 texW;          // 0x24
    s16 texH;          // 0x26
    u8 texIndex;       // 0x28
    u8 unk29[3];       // 0x29
};

struct FS_tagOAN3_SHAPE
{
    s16 flags;         // 0x00
    s16 count;         // 0x02
    u8 unk04[0xC];     // 0x04
};

struct CFunnyShapeAnmWork
{
    s32 index;         // 0x00
    void* animData;    // 0x04
    f32 x;             // 0x08
    f32 y;             // 0x0C
    f32 z;             // 0x10
    s16 frame;         // 0x14
    s16 delay;         // 0x16
    u8 unk18[8];       // 0x18
    f32 viewportX;     // 0x20
    f32 viewportY;     // 0x24
    f32 angle;         // 0x28
    u8 unk2C[4];       // 0x2C
};

class CFunnyShape
{
public:
	CFunnyShape();
	~CFunnyShape();

	void InitAnmWork();
	void Update();
	void Render();
	void RenderTexture();
	void RenderShape();
    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x8005ce50
     * EN Size: 52b
     * JP Address: TODO
     * JP Size: TODO
     */
    void SetDisplay(FS_DISPLAY_STATUS display) { m_displayCurrent = display; }
	void SetDefaultStage();
	void ClearShapeData();
	void Create();
	void ClearAnmData();
	void ClearTextureData();
	void RenderShape(FS_tagOAN3_SHAPE*, Vec2d, float);

    CFunnyShapeAnmWork m_anmWork[0x200]; // 0x0000
    OSFS_SHAPE_ST m_shape;               // 0x6000
    void* m_meshData;                    // 0x6010
    GXTexObj* m_texObjData[0x10];        // 0x6014
    OSFS_TEXTURE_ST* m_textureHeaders[0x10]; // 0x6054
    void* m_textureData[0x10];           // 0x6094
    s8 m_textureCount;                   // 0x60D4
    u8 m_textureCountPad[3];             // 0x60D5
    OSFS_ANM_ST m_anm;                   // 0x60D8
    FS_DISPLAY_STATUS m_displayCurrent;  // 0x60E8
};

#endif // _FFCC_FUNNYSHAPE_H_
