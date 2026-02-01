// Function: PlaySe3D__6CSoundFiP3Vecffi
// Entry: 800c5e2c
// Size: 496 bytes

undefined4
PlaySe3D__6CSoundFiP3Vecffi
          (double param_1,double param_2,CSound *sound,int param_4,undefined4 *param_5,uint param_6)

{
  byte *pbVar1;
  int iVar2;
  int local_28;
  uint local_24 [4];
  
  if (param_4 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    pbVar1 = &sound->field_0x2c;
    iVar2 = 0x80;
    do {
      if (-1 < (char)*pbVar1) {
        *pbVar1 = *pbVar1 & 0x7f | 0x80;
        *pbVar1 = *pbVar1 & 0xbf;
        *(int *)(pbVar1 + 0xc) = param_4;
        iVar2 = *(int *)&sound->field_0x28;
        *(int *)&sound->field_0x28 = iVar2 + 1;
        *(int *)(pbVar1 + 4) = iVar2;
        *(float *)(pbVar1 + 0x10) = (float)param_1;
        *(float *)(pbVar1 + 0x14) = (float)param_2;
        *(undefined4 *)(pbVar1 + 0x18) = *param_5;
        *(undefined4 *)(pbVar1 + 0x1c) = param_5[1];
        *(undefined4 *)(pbVar1 + 0x20) = param_5[2];
        pbVar1[3] = 0xff;
        calcVolumePan__6CSoundFPQ26CSound5CSe3DRiRi(sound,pbVar1,local_24,&local_28);
        pbVar1[1] = (byte)local_24[0];
        pbVar1[2] = (byte)local_28;
        pbVar1[0x24] = 0xff;
        pbVar1[0x25] = 0xff;
        pbVar1[0x26] = 0xff;
        pbVar1[0x27] = 0xff;
        if (param_4 < 0) {
          Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
          iVar2 = -1;
        }
        else if (param_4 < 4000) {
          iVar2 = param_4 / 1000 + (param_4 >> 0x1f);
          iVar2 = SePlay__9CRedSoundFiiiii
                            (&sound->m_redSound,iVar2 - (iVar2 >> 0x1f),
                             param_4 + (iVar2 - (iVar2 >> 0x1f)) * -1000,local_28,
                             local_24[0] & ~((int)(-param_6 | param_6) >> 0x1f),0);
          if (param_6 != 0) {
            SeVolume__9CRedSoundFiii(&sound->m_redSound,iVar2,local_24[0],param_6);
          }
        }
        else {
          iVar2 = SePlay__9CRedSoundFiiiii
                            (&sound->m_redSound,-1,param_4,local_28,
                             local_24[0] & ~((int)(-param_6 | param_6) >> 0x1f),0);
          if (param_6 != 0) {
            SeVolume__9CRedSoundFiii(&sound->m_redSound,iVar2,local_24[0],param_6);
          }
        }
        *(int *)(pbVar1 + 8) = iVar2;
        return *(undefined4 *)(pbVar1 + 4);
      }
      pbVar1 = pbVar1 + 0x28;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return 0xffffffff;
}

