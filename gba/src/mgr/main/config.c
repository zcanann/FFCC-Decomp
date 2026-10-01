#include "global.h"
#include "main.h"
#include "obj.h"

const u8 gConfigLinkMode = 1;
const u8 gConfigRacerCount = 8;
const u8 gConfigLapCount = 3;

const s16 gSpeedEffectMaxSpeed[2] = { 960, -640 };
const s16 gSpeedEffectAccel[2] = { 20, -10 };
const s16 gPanelSlowThreshold = 40;
const s16 gPanelBoostThreshold = 61;
const u16 gSpeedEffectDurations[] = { 150, 120, 90, 90, 90, 90, 90, 120, 150, 180 };

const u8 gCharaTable[] = { 0, 1, 2, 3 };
const s16 gStartHeading = 0;
