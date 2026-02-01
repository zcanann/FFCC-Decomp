// Function: Realloc__6CSoundFi
// Entry: 800c7a28
// Size: 1192 bytes

void Realloc__6CSoundFi(CSound *sound,int param_2)

{
  bool bVar1;
  CFileCHandle *pCVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined auStack_318 [256];
  undefined auStack_218 [256];
  undefined auStack_118 [260];
  
  pCVar2 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
  if (pCVar2 != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,pCVar2);
    *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
    Printf__7CSystemFPce(&System,&DAT_801db190);
  }
  SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
  bVar1 = false;
  if (*(int *)&sound->field_0x22a0 != 0) {
    iVar4 = StreamPlayState__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x2298);
    if (iVar4 != 0) {
      bVar1 = true;
    }
  }
  if (bVar1) {
    StreamStop__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x2298);
  }
  if (*(CFileCHandle **)&sound->field_0x2290 != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
    *(undefined4 *)&sound->field_0x2290 = 0;
  }
  *(undefined4 *)&sound->field_0x22a0 = 0;
  SeStop__9CRedSoundFi(&sound->m_redSound,0xffffffff);
  ClearSeSepData__9CRedSoundFi(&sound->m_redSound,-1);
  ClearWaveData__9CRedSoundFi(&sound->m_redSound,-3);
  *(undefined4 *)&sound->field_0x28 = 10000000;
  memset(&sound->field_0x2c,0,0x1400);
  memset(&sound->field_0x22c0,0xff,8);
  memset(&sound->field_0x22c8,0xff,8);
  ClearWaveBank__9CRedSoundFi(&sound->m_redSound,500);
  ClearWaveBank__9CRedSoundFi(&sound->m_redSound,0);
  iVar4 = 0;
  do {
    SetSeBlockData__9CRedSoundFiPv(&sound->m_redSound,iVar4,(void *)0x0);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 4);
  End__9CRedSoundFv(&sound->m_redSound);
  uVar6 = 0x800000;
  if (param_2 != 0) {
    uVar6 = 0x200000;
  }
  uVar5 = 0x800000;
  if (param_2 != 0) {
    uVar5 = 0xe00000;
  }
  Init__9CRedSoundFPviii
            (&sound->m_redSound,*(undefined4 *)&(sound->m_redSound).field_0x4,0x80000,uVar5,uVar6);
  ReportPrint__9CRedSoundFi
            (&sound->m_redSound,
             (-*(uint *)&sound->field_0x22d4 | *(uint *)&sound->field_0x22d4) >> 0x1f);
  uVar6 = GetSoundMode__9CRedSoundFv(&sound->m_redSound);
  uVar3 = countLeadingZeros(uVar6);
  uVar3 = countLeadingZeros(uVar3 >> 5);
  SetSoundMode__9CRedSoundFi(&sound->m_redSound,uVar3 >> 5);
  MusicMasterVolume__9CRedSoundFi((int)&sound->m_redSound,*(int *)&sound->field_0x22b0);
  SeMasterVolume__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x22b4);
  SetReverb__9CRedSoundFii(&sound->m_redSound,1,4);
  SetReverbDepth__9CRedSoundFiii(&sound->m_redSound,1,0x40,0xf);
  *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
  *(undefined4 *)&sound->field_0x2290 = 0;
  *(undefined4 *)&sound->field_0x22a0 = 0;
  memset(&sound->field_0x22c0,0xff,8);
  memset(&sound->field_0x22c8,0xff,8);
  *(undefined4 *)&sound->field_0x22d0 = 0;
  if (param_2 == 0) {
    iVar4 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,0);
    if (iVar4 == -1) {
      pCVar2 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
      if (pCVar2 != (CFileCHandle *)0x0) {
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
        Printf__7CSystemFPce(&System,&DAT_801db190);
      }
      SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
      sprintf(auStack_218,s_dvd_sound_wave_wave_04d_wd_801db1bc,0);
      uVar6 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_218,0,0);
      *(undefined4 *)&(sound->m_redSound).field_0x8 = uVar6;
      pCVar2 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
      if (pCVar2 != (CFileCHandle *)0x0) {
        uVar6 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        *(undefined4 *)&sound->field_0x14 = uVar6;
        *(undefined4 *)&sound->field_0x18 = 0;
        *(undefined4 *)&sound->field_0x20 = 0;
        *(undefined4 *)&sound->field_0x1c = 0;
        *(undefined4 *)&sound->field_0x24 = 1;
        while( true ) {
          uVar3 = countLeadingZeros(*(undefined4 *)&(sound->m_redSound).field_0x8);
          if (uVar3 >> 5 != 0) break;
          loadWaveFrame__6CSoundFv(sound);
        }
      }
    }
    iVar4 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,500);
    if (iVar4 == -1) {
      pCVar2 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
      if (pCVar2 != (CFileCHandle *)0x0) {
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
        Printf__7CSystemFPce(&System,&DAT_801db190);
      }
      SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
      sprintf(auStack_318,s_dvd_sound_wave_wave_04d_wd_801db1bc,500);
      uVar6 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_318,0,0);
      *(undefined4 *)&(sound->m_redSound).field_0x8 = uVar6;
      pCVar2 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
      if (pCVar2 != (CFileCHandle *)0x0) {
        uVar6 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        *(undefined4 *)&sound->field_0x14 = uVar6;
        *(undefined4 *)&sound->field_0x18 = 0;
        *(undefined4 *)&sound->field_0x20 = 0;
        *(undefined4 *)&sound->field_0x1c = 1;
        *(undefined4 *)&sound->field_0x24 = 1;
        while( true ) {
          uVar3 = countLeadingZeros(*(undefined4 *)&(sound->m_redSound).field_0x8);
          if (uVar3 >> 5 != 0) break;
          loadWaveFrame__6CSoundFv(sound);
        }
      }
    }
    iVar4 = 0;
    do {
      sprintf(auStack_118,s_dvd_sound_se_block_se_03d_seb_801db25c,iVar4);
      pCVar2 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
      if (pCVar2 != (CFileCHandle *)0x0) {
        Read__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar2);
        SetSeBlockData__9CRedSoundFiPv(&sound->m_redSound,iVar4,File.m_readBuffer);
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar2);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
  }
  return;
}

