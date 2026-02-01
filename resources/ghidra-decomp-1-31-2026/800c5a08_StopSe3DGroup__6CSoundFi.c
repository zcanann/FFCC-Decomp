// Function: StopSe3DGroup__6CSoundFi
// Entry: 800c5a08
// Size: 372 bytes

void StopSe3DGroup__6CSoundFi(CSound *sound,int param_2)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  
  uVar4 = 0;
  pbVar5 = &sound->field_0x2c;
  do {
    if ((((char)*pbVar5 < '\0') && (-1 < *(int *)(pbVar5 + 0x24))) &&
       (*(int *)(pbVar5 + 0x24) == param_2)) {
      iVar1 = *(int *)(pbVar5 + 4);
      if (iVar1 < 0) {
        Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
      }
      else {
        pbVar2 = &sound->field_0x2c;
        iVar6 = 0x20;
        do {
          if ((((((char)*pbVar2 < '\0') && (pbVar3 = pbVar2, *(int *)(pbVar2 + 4) == iVar1)) ||
               ((pbVar3 = pbVar2 + 0x28, (char)*pbVar3 < '\0' && (*(int *)(pbVar2 + 0x2c) == iVar1))
               )) || ((pbVar3 = pbVar2 + 0x50, (char)*pbVar3 < '\0' &&
                      (*(int *)(pbVar2 + 0x54) == iVar1)))) ||
             (((char)pbVar2[0x78] < '\0' &&
              (pbVar3 = pbVar2 + 0x78, *(int *)(pbVar2 + 0x7c) == iVar1)))) goto LAB_800c5b00;
          pbVar2 = pbVar2 + 0xa0;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        pbVar3 = (byte *)0x0;
LAB_800c5b00:
        if (pbVar3 != (byte *)0x0) {
          if (*(int *)(pbVar3 + 8) < 0) {
            Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
          }
          else {
            SeStop__9CRedSoundFi(&sound->m_redSound,*(int *)(pbVar3 + 8));
          }
          *pbVar3 = *pbVar3 & 0x7f;
        }
      }
      *pbVar5 = *pbVar5 & 0x7f;
    }
    uVar4 = uVar4 + 1;
    pbVar5 = pbVar5 + 0x28;
    if (0x7f < uVar4) {
      return;
    }
  } while( true );
}

