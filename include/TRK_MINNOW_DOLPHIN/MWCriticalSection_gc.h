#ifndef MWCRITICALSECTION_GC_H
#define MWCRITICALSECTION_GC_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void MWExitCriticalSection(u32* section);
void MWEnterCriticalSection(u32* section);
void MWInitializeCriticalSection(u32*);

#ifdef __cplusplus
}
#endif

#endif /* MWCRITICALSECTION_GC_H */
