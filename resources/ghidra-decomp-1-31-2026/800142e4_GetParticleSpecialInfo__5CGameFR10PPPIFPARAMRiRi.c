// Function: GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi
// Entry: 800142e4
// Size: 184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi
          (CGame *game,PPPIFPARAM *pppIFParam,int *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  if (pppIFParam->m_classId == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = intToClass__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,(int)pppIFParam->m_classId);
    *param_3 = pppIFParam->m_particleIndex;
    if (*param_3 == 0) {
      uVar1 = 0;
    }
    else {
      uVar3 = (**(code **)(*(int *)(iVar2 + 0x48) + 0xc))();
      if ((uVar3 & 0x6d) == 0x6d) {
        uVar1 = 1;
        *param_4 = *(undefined4 *)(*(int *)(iVar2 + 0x58) + 0x3b4);
      }
      else {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

