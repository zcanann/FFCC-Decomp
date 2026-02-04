#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

#include <dolphin/types.h>

// Forward declarations
struct VYmDeformationMdl;
struct UnkB;

struct UnkC {
    s32* m_serializedDataOffsets;
};

struct pppYmDeformationMdl {
    u8* m_serializedData;
    // Add padding for pppPObject structure + field_0x80 offset
    char pad[0x80];
};

void SetUpIndWarp(VYmDeformationMdl*);
void DisableIndWarp(void);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(pppYmDeformationMdl*, struct UnkC*);
void pppConstruct2YmDeformationMdl(void);
void pppDestructYmDeformationMdl(void);
void pppFrameYmDeformationMdl(void* pppYmDeformationMdl, void* param_2, void* param_3);
void pppRenderYmDeformationMdl(void* pppYmDeformationMdl, void* param_2, void* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_
