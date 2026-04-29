#ifndef _PPP_RYJMEGABIRTHMODEL_H_
#define _PPP_RYJMEGABIRTHMODEL_H_

#include "ffcc/partMng.h"

struct PRyjMegaBirthModel : _PARTICLE_DATA {}; // Size 0x140

struct VRyjMegaBirthModel
{
    Vec m_accelerationAxis;
    _PARTICLE_DATA* m_particleBlock;
    PARTICLE_WMAT* m_worldMatrixBlock;
    _PARTICLE_COLOR* m_colorBlock;
    s32 m_numParticles;
    u16 m_emitTimer;
    u16 m_unused1E;
    Vec m_previousPosition;
    Vec m_currentPosition;
};

struct PRyjMegaBirthModelOffsets
{
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

void calc_particle(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*);
void birth(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirthModel*, VRyjMegaBirthModel*);
void set_matrix(_pppPObject*, pppFMATRIX, pppFMATRIX, PRyjMegaBirthModel*, _PARTICLE_DATA*, _PARTICLE_WMAT*, pppFMATRIX&, unsigned char);

#ifdef __cplusplus
extern "C" {
#endif

void pppRyjMegaBirthModel(_pppPObject*, PRyjMegaBirthModel*, PRyjMegaBirthModelOffsets*);
void pppRyjDrawMegaBirthModel(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);
void pppRyjMegaBirthModelCon(_pppPObject*, PRyjMegaBirthModelOffsets*);
void pppRyjMegaBirthModelDes(_pppPObject*, PRyjMegaBirthModelOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RYJMEGABIRTHMODEL_H_
