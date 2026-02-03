#ifndef _PPP_YMCHECKBGHEIGHT_H_
#define _PPP_YMCHECKBGHEIGHT_H_

#include <dolphin/types.h>

struct pppYmCheckBGHeight;

struct UnkC {
    float m_serializedDataOffsets;
    float m_unk0x4;
    float m_unk0x8;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmCheckBGHeight(void);
struct pppYmCheckBGHeight* pppFrameYmCheckBGHeight(struct pppYmCheckBGHeight* param1, struct UnkC* param2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCHECKBGHEIGHT_H_
