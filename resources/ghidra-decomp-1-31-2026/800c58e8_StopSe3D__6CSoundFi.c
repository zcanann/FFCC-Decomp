// Function: StopSe3D__6CSoundFi
// Entry: 800c58e8
// Size: 288 bytes

void StopSe3D__6CSoundFi(CSound *sound,int param_2)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    pbVar2 = &sound->field_0x2c;
    iVar1 = 0;
    iVar4 = 0x20;
    do {
      if ((((((char)*pbVar2 < '\0') && (pbVar3 = pbVar2, *(int *)(pbVar2 + 4) == param_2)) ||
           ((pbVar3 = pbVar2 + 0x28, (char)*pbVar3 < '\0' && (*(int *)(pbVar2 + 0x2c) == param_2))))
          || ((pbVar3 = pbVar2 + 0x50, (char)*pbVar3 < '\0' && (*(int *)(pbVar2 + 0x54) == param_2))
             )) || (((char)pbVar2[0x78] < '\0' &&
                    (pbVar3 = pbVar2 + 0x78, *(int *)(pbVar2 + 0x7c) == param_2))))
      goto LAB_800c59ac;
      iVar1 = iVar1 + 3;
      pbVar2 = pbVar2 + 0xa0;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    pbVar3 = (byte *)0x0;
LAB_800c59ac:
    if (pbVar3 != (byte *)0x0) {
      if (*(int *)(pbVar3 + 8) < 0) {
        Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130,iVar1);
      }
      else {
        SeStop__9CRedSoundFi(&sound->m_redSound,*(int *)(pbVar3 + 8));
      }
      *pbVar3 = *pbVar3 & 0x7f;
    }
  }
  return;
}

