#ifndef GUARD_EFFECT_H
#define GUARD_EFFECT_H

#include "obj.h"

/* Homing shots steer with racer handling parameters */
extern const struct ActorData gFreezeShotParams;
extern const struct ActorData gSlipShotParams;
extern const u8 gItemBoxAnims[];
extern const u8 gPanelAnims[];
extern const char gEffectFileName[];

struct Effect *Effect_Alloc(struct Game *game);
struct Effect *Effect_AllocLast(struct Game *game);
void Effect_InitItemBox(struct Effect *e, va_list *ap);
void Effect_InitPanel(struct Effect *e, va_list *ap);
void Effect_InitShot(struct Effect *e, va_list *ap);
void Effect_InitFreezeTrail(struct Effect *e, va_list *ap);
void Effect_InitFreezeShot(struct Effect *e, va_list *ap);
void Effect_InitFreeze(struct Effect *e, va_list *ap);
void Effect_InitSlipTrail(struct Effect *e, va_list *ap);
void Effect_InitSlipShot(struct Effect *e, va_list *ap);
void Effect_InitSlip(struct Effect *e, va_list *ap);
void Effect_InitTrapThrow(struct Effect *e, va_list *ap);
void Effect_InitTrap(struct Effect *e, va_list *ap);
void Effect_InitSpin(struct Effect *e, va_list *ap);
void Effect_InitDust(struct Effect *e, va_list *ap);
void Effect_Setup(struct Effect *e, u8 type, va_list *ap);
void Effect_Set(struct Effect *e, u8 type, ...);
void Effect_Spawn(struct Game *game, u8 type, ...);
void Effect_SpawnLast(struct Game *game, u8 type, ...);
s16 Effect_MoveAlongRoute(struct Effect *e, u8 routeNo, u8 *routeIdx, struct Point *vel, const struct ActorData *params, struct Actor *target, s16 targetDist);
void Effect_UpdateItemBox(struct Effect *e);
void Effect_UpdatePanel(struct Effect *e);
void Effect_UpdateHoming(struct Effect *e, const struct ActorData *params, s32 mask);
void Effect_UpdateFreezeTrail(struct Effect *e);
void Effect_UpdateFreezeShot(struct Effect *e);
void Effect_UpdateFreeze(struct Effect *e);
void Effect_UpdateSlipTrail(struct Effect *e);
void Effect_UpdateSlipShot(struct Effect *e);
void Effect_UpdateSlip(struct Effect *e);
void Effect_UpdateTrapThrow(struct Effect *e);
void Effect_UpdateTrap(struct Effect *e);
void Effect_UpdateDust(struct Effect *e);
void Effect_UpdateSpin(struct Effect *e);
void Effect_Update(struct Effect *e);

#endif
