#ifndef _PPP_RYJMEGABIRTHMODEL_H_
#define _PPP_RYJMEGABIRTHMODEL_H_

struct _PARTICLE_COLOR;
struct _PARTICLE_DATA;
struct _PARTICLE_WMAT;
struct _pppPObject;
struct pppFMATRIX;
class PRyjMegaBirthModel;
class VRyjMegaBirthModel;
struct VColor;

void get_rand(void);
void get_noise(unsigned char);
void alloc_check(VRyjMegaBirthModel*, PRyjMegaBirthModel*);
void pppRyjMegaBirthModel(void);
void calc_particle(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*);
void birth(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void pppRyjDrawMegaBirthModel(void);
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirthModel*, VRyjMegaBirthModel*);
void set_matrix(_pppPObject*, pppFMATRIX&, pppFMATRIX&, PRyjMegaBirthModel*, _PARTICLE_DATA*, _PARTICLE_WMAT*, pppFMATRIX&, unsigned char);
void pppRyjMegaBirthModelCon(void);
void pppRyjMegaBirthModelDes(void);

#endif // _PPP_RYJMEGABIRTHMODEL_H_
