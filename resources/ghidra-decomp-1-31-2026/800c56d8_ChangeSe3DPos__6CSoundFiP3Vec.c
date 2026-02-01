// Function: ChangeSe3DPos__6CSoundFiP3Vec
// Entry: 800c56d8
// Size: 240 bytes

int ChangeSe3DPos__6CSoundFiP3Vec(CSound *sound,int param_2,Vec *position)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  if (param_2 < 0) {
    iVar1 = Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    pcVar2 = &sound->field_0x2c;
    iVar1 = 0;
    iVar4 = 0x20;
    do {
      if (((((*pcVar2 < '\0') && (pcVar3 = pcVar2, *(int *)(pcVar2 + 4) == param_2)) ||
           ((pcVar3 = pcVar2 + 0x28, *pcVar3 < '\0' && (*(int *)(pcVar2 + 0x2c) == param_2)))) ||
          ((pcVar3 = pcVar2 + 0x50, *pcVar3 < '\0' && (*(int *)(pcVar2 + 0x54) == param_2)))) ||
         ((pcVar2[0x78] < '\0' && (pcVar3 = pcVar2 + 0x78, *(int *)(pcVar2 + 0x7c) == param_2))))
      goto LAB_800c5798;
      iVar1 = iVar1 + 3;
      pcVar2 = pcVar2 + 0xa0;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    pcVar3 = (char *)0x0;
LAB_800c5798:
    if (pcVar3 != (char *)0x0) {
      *(float *)(pcVar3 + 0x18) = position->x;
      *(float *)(pcVar3 + 0x1c) = position->y;
      *(float *)(pcVar3 + 0x20) = position->z;
    }
  }
  return iVar1;
}

