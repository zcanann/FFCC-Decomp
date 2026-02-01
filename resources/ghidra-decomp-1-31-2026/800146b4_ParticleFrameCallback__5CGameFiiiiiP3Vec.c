// Function: ParticleFrameCallback__5CGameFiiiiiP3Vec
// Entry: 800146b4
// Size: 324 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ParticleFrameCallback__5CGameFiiiiiP3Vec
               (CGame *game,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
               undefined4 param_6)

{
  int iVar1;
  
  iVar1 = pppGetIfDt__8CPartMngFs(&PartMng,(short)param_2);
  *(byte *)(iVar1 + 7) = *(byte *)(iVar1 + 7) | (byte)(1 << param_5);
  if (param_5 == 0) {
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d60d4,param_3,param_4,param_2,param_6);
    }
  }
  else if (param_5 == 1) {
    *(byte *)(iVar1 + 7) = *(byte *)(iVar1 + 7) & 0xfd;
    pppEndPart__8CPartMngFi(&PartMng,param_2);
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d6114,param_3,param_4,param_2,param_6);
    }
  }
  else if ((param_5 == 3) &&
          (pppEndPart__8CPartMngFi(&PartMng,param_2), 2 < (uint)System.m_execParam)) {
    Printf__7CSystemFPce(&System,&DAT_801d6154,param_3,param_4,param_2,param_6);
  }
  return;
}

