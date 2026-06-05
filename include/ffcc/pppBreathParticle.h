#ifndef _FFCC_PPPBREATHPARTICLE_H_
#define _FFCC_PPPBREATHPARTICLE_H_

#include <dolphin/mtx.h>

struct PARTICLE_WMAT {
    Mtx m_matrix;
};

struct PARTICLE_COLOR {
    float m_color[4];
    float m_colorFrameDeltas[4];
};

#endif
