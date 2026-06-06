#ifndef _FFCC_HSD_IMAGE_H_
#define _FFCC_HSD_IMAGE_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct HSD_ImageBuffer {
    u8* m_imageData;
    GXTexFmt m_format;
    u32 m_width;
    u32 m_height;
    u32 m_imageCount;
    u32 m_bufferSize;
};

#endif // _FFCC_HSD_IMAGE_H_
