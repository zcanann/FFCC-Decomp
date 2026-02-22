#ifndef _PPP_RYJMEGABIRTHMODEL_H_
#define _PPP_RYJMEGABIRTHMODEL_H_

#include "ffcc/partMng.h"

struct PRyjMegaBirthModel : _PARTICLE_DATA {}; // Size 0x140

struct VRyjMegaBirthModel
{

};

struct PRyjMegaBirthModelOffsets
{
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

void get_rand(void);
void get_noise(unsigned char);
void alloc_check(VRyjMegaBirthModel*, PRyjMegaBirthModel*);
void calc_particle(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*);
void birth(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirthModel*, VRyjMegaBirthModel*);
void set_matrix(_pppPObject*, pppFMATRIX, pppFMATRIX, PRyjMegaBirthModel*, _PARTICLE_DATA*, _PARTICLE_WMAT*, pppFMATRIX&, unsigned char);

#ifdef __cplusplus
extern "C" {
#endif

void pppRyjMegaBirthModel(_pppPObject*, PRyjMegaBirthModel*, PRyjMegaBirthModelOffsets*);
void pppRyjDrawMegaBirthModel(void);
void pppRyjMegaBirthModelCon(_pppPObject*, PRyjMegaBirthModelOffsets*);
void pppRyjMegaBirthModelDes(_pppPObject*, PRyjMegaBirthModelOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RYJMEGABIRTHMODEL_H_
