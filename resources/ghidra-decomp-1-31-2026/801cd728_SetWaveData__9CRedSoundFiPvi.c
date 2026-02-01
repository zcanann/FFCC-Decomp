// Function: SetWaveData__9CRedSoundFiPvi
// Entry: 801cd728
// Size: 124 bytes

undefined4 SetWaveData__9CRedSoundFiPvi(CRedSound *redSound,int param_2,void *param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = GetAutoID__9CRedSoundFv();
  iVar2 = EntryStandbyID__9CRedSoundFi(redSound,uVar1);
  if (iVar2 != 0) {
    SetWaveData__10CRedDriverFiiPvi(&CRedDriver_8032f4c0,iVar2,param_2,param_3,param_4);
  }
  return uVar1;
}

