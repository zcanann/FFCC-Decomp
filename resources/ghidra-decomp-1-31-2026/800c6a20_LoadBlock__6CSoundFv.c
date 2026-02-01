// Function: LoadBlock__6CSoundFv
// Entry: 800c6a20
// Size: 624 bytes

void LoadBlock__6CSoundFv(CSound *sound)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  CFileCHandle *pCVar4;
  undefined auStack_318 [256];
  undefined auStack_218 [256];
  undefined auStack_118 [260];
  
  iVar2 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,0);
  if (iVar2 == -1) {
    pCVar4 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
    if (pCVar4 != (CFileCHandle *)0x0) {
      Close__5CFileFPQ25CFile7CHandle(&File,pCVar4);
      *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
      Printf__7CSystemFPce(&System,&DAT_801db190);
    }
    SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
    sprintf(auStack_218,s_dvd_sound_wave_wave_04d_wd_801db1bc,0);
    uVar3 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_218,0,0);
    *(undefined4 *)&(sound->m_redSound).field_0x8 = uVar3;
    pCVar4 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
    if (pCVar4 != (CFileCHandle *)0x0) {
      uVar3 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar4);
      *(undefined4 *)&sound->field_0x14 = uVar3;
      *(undefined4 *)&sound->field_0x18 = 0;
      *(undefined4 *)&sound->field_0x20 = 0;
      *(undefined4 *)&sound->field_0x1c = 0;
      *(undefined4 *)&sound->field_0x24 = 1;
      while( true ) {
        uVar1 = countLeadingZeros(*(undefined4 *)&(sound->m_redSound).field_0x8);
        if (uVar1 >> 5 != 0) break;
        loadWaveFrame__6CSoundFv(sound);
      }
    }
  }
  iVar2 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,500);
  if (iVar2 == -1) {
    pCVar4 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
    if (pCVar4 != (CFileCHandle *)0x0) {
      Close__5CFileFPQ25CFile7CHandle(&File,pCVar4);
      *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
      Printf__7CSystemFPce(&System,&DAT_801db190);
    }
    SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
    sprintf(auStack_318,s_dvd_sound_wave_wave_04d_wd_801db1bc,500);
    uVar3 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_318,0,0);
    *(undefined4 *)&(sound->m_redSound).field_0x8 = uVar3;
    pCVar4 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
    if (pCVar4 != (CFileCHandle *)0x0) {
      uVar3 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar4);
      *(undefined4 *)&sound->field_0x14 = uVar3;
      *(undefined4 *)&sound->field_0x18 = 0;
      *(undefined4 *)&sound->field_0x20 = 0;
      *(undefined4 *)&sound->field_0x1c = 1;
      *(undefined4 *)&sound->field_0x24 = 1;
      while( true ) {
        uVar1 = countLeadingZeros(*(undefined4 *)&(sound->m_redSound).field_0x8);
        if (uVar1 >> 5 != 0) break;
        loadWaveFrame__6CSoundFv(sound);
      }
    }
  }
  iVar2 = 0;
  do {
    sprintf(auStack_118,s_dvd_sound_se_block_se_03d_seb_801db25c,iVar2);
    pCVar4 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
    if (pCVar4 != (CFileCHandle *)0x0) {
      Read__5CFileFPQ25CFile7CHandle(&File,pCVar4);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar4);
      SetSeBlockData__9CRedSoundFiPv(&sound->m_redSound,iVar2,File.m_readBuffer);
      Close__5CFileFPQ25CFile7CHandle(&File,pCVar4);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return;
}

