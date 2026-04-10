#ifndef METROTRK_PORTABLE_NUBEVENT_H
#define METROTRK_PORTABLE_NUBEVENT_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

extern TRKEventQueue gTRKEventQueue;

BOOL TRKGetNextEvent(TRKEvent* event);
void TRKDestructEvent(TRKEvent*);
void TRKConstructEvent(TRKEvent*, NubEventType);
DSError TRKPostEvent(TRKEvent*);
DSError TRKInitializeEventQueue();

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_NUBEVENT_H */
