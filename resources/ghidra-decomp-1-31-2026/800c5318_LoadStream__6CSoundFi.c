// Function: LoadStream__6CSoundFi
// Entry: 800c5318
// Size: 404 bytes

void LoadStream__6CSoundFi(CSound *sound,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined auStack_118 [268];
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    bVar1 = false;
    if (*(int *)&sound->field_0x22a0 != 0) {
      iVar2 = StreamPlayState__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x2298);
      if (iVar2 != 0) {
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
    sprintf(auStack_118,s_dvd_sound_stream_str_04d_str_801db110,param_2);
    uVar3 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
    *(undefined4 *)&sound->field_0x2290 = uVar3;
    iVar2 = *(int *)&sound->field_0x2290;
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0xa0) = 0x20000;
      *(undefined4 *)(iVar2 + 0xa4) = 0;
      Read__5CFileFPQ25CFile7CHandle(&File,*(undefined4 *)&sound->field_0x2290);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
      memcpy(*(void **)&sound->field_0x228c,File.m_readBuffer,0x20000);
      *(undefined4 *)&sound->field_0x2294 = 0x20000;
      *(undefined4 *)&sound->field_0x229c = 0;
      iVar2 = GetLength__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
      *(int *)&sound->field_0x22a4 = iVar2 + -0x20000;
      *(undefined4 *)&sound->field_0x22a8 = 0;
      *(int *)&sound->field_0x22ac = param_2;
      Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
      *(undefined4 *)&sound->field_0x2290 = 0;
    }
  }
  return;
}

