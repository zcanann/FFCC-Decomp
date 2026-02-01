// Function: ChangeSe3DPitch__6CSoundFiii
// Entry: 800c55f0
// Size: 232 bytes

void ChangeSe3DPitch__6CSoundFiii(CSound *sound,int param_2,int param_3,int param_4)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    pcVar1 = &sound->field_0x2c;
    iVar3 = 0x20;
    do {
      if (((((*pcVar1 < '\0') && (pcVar2 = pcVar1, *(int *)(pcVar1 + 4) == param_2)) ||
           ((pcVar2 = pcVar1 + 0x28, *pcVar2 < '\0' && (*(int *)(pcVar1 + 0x2c) == param_2)))) ||
          ((pcVar2 = pcVar1 + 0x50, *pcVar2 < '\0' && (*(int *)(pcVar1 + 0x54) == param_2)))) ||
         ((pcVar1[0x78] < '\0' && (pcVar2 = pcVar1 + 0x78, *(int *)(pcVar1 + 0x7c) == param_2))))
      goto LAB_800c56b0;
      pcVar1 = pcVar1 + 0xa0;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    pcVar2 = (char *)0x0;
LAB_800c56b0:
    if (pcVar2 != (char *)0x0) {
      SePitch__9CRedSoundFiii(&sound->m_redSound,*(int *)(pcVar2 + 8),param_3 << 8,param_4);
    }
  }
  return;
}

