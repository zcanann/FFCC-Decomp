#ifndef _FFCC_FUNNYSHAPE_H_
#define _FFCC_FUNNYSHAPE_H_

#include "ffcc/FS_USB_Process.h"

class FS_tagOAN3_SHAPE;

struct Vec2d {
    float x;
    float y;
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
	void ClearShapeData();
	void ClearAnmData();
	void ClearTextureData();
	void RenderShape(FS_tagOAN3_SHAPE*, Vec2d, float);

    CFunnyShapeAnmWork m_anmWork[0x200]; // 0x0000
    OSFS_SHAPE_ST m_shape;               // 0x6000
    void* m_meshData;                    // 0x6010
    void* m_texObjData[0x10];            // 0x6014
    OSFS_TEXTURE_ST* m_textureHeaders[0x10]; // 0x6054
    void* m_textureData[0x10];           // 0x6094
    s8 m_textureCount;                   // 0x60D4
    u8 m_textureCountPad[3];             // 0x60D5
    OSFS_ANM_ST m_anm;                   // 0x60D8
    FS_DISPLAY_STATUS m_displayCurrent;  // 0x60E8
};

#endif // _FFCC_FUNNYSHAPE_H_
