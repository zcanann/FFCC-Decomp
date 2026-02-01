// Function: Frame__6CSoundFv
// Entry: 800c7594
// Size: 776 bytes

void Frame__6CSoundFv(CSound *sound)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  int local_28;
  int local_24 [3];
  
  loadWaveFrame__6CSoundFv(sound);
  pbVar5 = &sound->field_0x2c;
  uVar4 = 0;
  do {
    if ((char)*pbVar5 < '\0') {
      calcVolumePan__6CSoundFPQ26CSound5CSe3DRiRi(sound,pbVar5,local_24,&local_28);
      if ((*pbVar5 >> 6 & 1) == 0) {
        iVar1 = SePlayState__9CRedSoundFi(&sound->m_redSound,*(undefined4 *)(pbVar5 + 8));
        if (iVar1 == 0) {
          *pbVar5 = *pbVar5 & 0x7f;
        }
        else {
          iVar1 = ReportSeLoop__9CRedSoundFi(&sound->m_redSound,*(undefined4 *)(pbVar5 + 8));
          if ((iVar1 != 0) &&
             (iVar1 = GetSeVolume__9CRedSoundFii(&sound->m_redSound,*(int *)(pbVar5 + 8),0),
             iVar1 == 0)) {
            iVar1 = GetSeVolume__9CRedSoundFii(&sound->m_redSound,*(int *)(pbVar5 + 8),1);
            if (iVar1 == 0) {
              if ((CFlat._4764_4_ & 0x400000) != 0) {
                Printf__7CSystemFPce(&System,&DAT_801db2b8,*(undefined4 *)(pbVar5 + 0xc));
              }
              SeStop__9CRedSoundFi(&sound->m_redSound,*(undefined4 *)(pbVar5 + 8));
              *pbVar5 = *pbVar5 & 0xbf | 0x40;
              goto LAB_800c783c;
            }
          }
          if ((char)pbVar5[2] != local_28) {
            if (*(int *)(pbVar5 + 8) < 0) {
              Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
            }
            else {
              SePan__9CRedSoundFiii(&sound->m_redSound,*(int *)(pbVar5 + 8),local_28,0x1e);
            }
            pbVar5[2] = (byte)local_28;
          }
          if ((char)pbVar5[1] != local_24[0]) {
            if (*(int *)(pbVar5 + 8) < 0) {
              Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
            }
            else {
              SeVolume__9CRedSoundFiii(&sound->m_redSound,*(int *)(pbVar5 + 8),local_24[0],0x1e);
            }
            pbVar5[1] = (byte)local_24[0];
          }
        }
      }
      else if (local_24[0] != 0) {
        if ((CFlat._4764_4_ & 0x400000) != 0) {
          Printf__7CSystemFPce(&System,&DAT_801db29c,*(undefined4 *)(pbVar5 + 0xc));
        }
        iVar1 = local_24[0];
        iVar2 = *(int *)(pbVar5 + 0xc);
        if (iVar2 < 0) {
          Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
          iVar2 = -1;
        }
        else if (iVar2 < 4000) {
          iVar3 = iVar2 / 1000 + (iVar2 >> 0x1f);
          iVar2 = SePlay__9CRedSoundFiiiii
                            (&sound->m_redSound,iVar3 - (iVar3 >> 0x1f),
                             iVar2 + (iVar3 - (iVar3 >> 0x1f)) * -1000,local_28,0,0);
          SeVolume__9CRedSoundFiii(&sound->m_redSound,iVar2,iVar1,0x1e);
        }
        else {
          iVar2 = SePlay__9CRedSoundFiiiii(&sound->m_redSound,-1,iVar2,local_28,0,0);
          SeVolume__9CRedSoundFiii(&sound->m_redSound,iVar2,iVar1,0x1e);
        }
        *(int *)(pbVar5 + 8) = iVar2;
        *pbVar5 = *pbVar5 & 0xbf;
      }
    }
LAB_800c783c:
    uVar4 = uVar4 + 1;
    pbVar5 = pbVar5 + 0x28;
    if (0x7f < uVar4) {
      iVar1 = *(int *)&sound->field_0x22b8;
      if (iVar1 != *(int *)&sound->field_0x22bc) {
        if (iVar1 < *(int *)&sound->field_0x22bc) {
          *(int *)&sound->field_0x22b8 = iVar1 + 1;
        }
        else {
          *(int *)&sound->field_0x22b8 = iVar1 + -1;
        }
      }
      MusicVolume__9CRedSoundFiii(&sound->m_redSound,-1,*(int *)&sound->field_0x22b8,0);
      return;
    }
  } while( true );
}

