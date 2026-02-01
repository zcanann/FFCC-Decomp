// Function: loadWaveFrame__6CSoundFv
// Entry: 800c70e4
// Size: 668 bytes

void loadWaveFrame__6CSoundFv(CSound *sound)

{
  bool bVar1;
  uint32_t uVar2;
  undefined4 uVar3;
  int iVar4;
  CFileCHandle *fileHandle;
  int iVar5;
  uint uVar6;
  undefined auStack_18 [4];
  uint local_14 [3];
  
  fileHandle = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
  if (fileHandle != (CFileCHandle *)0x0) {
    if (*(int *)&sound->field_0x20 == 0) {
      uVar6 = 0x100000;
      if (*(uint *)&sound->field_0x14 < 0x100000) {
        uVar6 = *(uint *)&sound->field_0x14;
      }
      uVar2 = *(uint32_t *)&sound->field_0x18;
      fileHandle->mFileSize = uVar6;
      fileHandle->mCurrentOffset = uVar2;
      ReadASync__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&(sound->m_redSound).field_0x8);
      if (*(int *)&sound->field_0x24 != 0) {
        SyncCompleted__5CFileFPQ25CFile7CHandle
                  (&File,*(CFileCHandle **)&(sound->m_redSound).field_0x8);
      }
      *(uint *)&sound->field_0x14 = *(int *)&sound->field_0x14 - uVar6;
      *(uint *)&sound->field_0x18 = *(int *)&sound->field_0x18 + uVar6;
      *(undefined4 *)&sound->field_0x20 = 1;
    }
    else if ((*(int *)&sound->field_0x20 == 1) &&
            (iVar4 = IsCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle), iVar4 != 0)) {
      SetWaveData__9CRedSoundFiPvi
                (&sound->m_redSound,*(int *)&sound->field_0x1c,File.m_readBuffer,
                 *(int *)(*(int *)&(sound->m_redSound).field_0x8 + 0xa0));
      do {
        iVar4 = ReportStandby__9CRedSoundFi(&Sound.m_redSound,0);
      } while (iVar4 != 0);
      *(undefined4 *)&sound->field_0x20 = 0;
      if (*(int *)&sound->field_0x14 == 0) {
        Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&(sound->m_redSound).field_0x8);
        *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
      }
      else {
        Reset__Q25CFile7CHandleFv(*(CFileCHandle **)&(sound->m_redSound).field_0x8);
      }
    }
  }
  bVar1 = false;
  if (*(int *)&sound->field_0x22a0 != 0) {
    iVar4 = StreamPlayState__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x2298);
    if (iVar4 != 0) {
      bVar1 = true;
    }
  }
  if ((bVar1) && (*(CFileCHandle **)&sound->field_0x2290 != (CFileCHandle *)0x0)) {
    if (*(int *)&sound->field_0x22a8 == 0) {
      GetStreamPlayPoint__9CRedSoundFiPiPi
                (&sound->m_redSound,*(undefined4 *)&sound->field_0x2298,local_14,auStack_18);
      local_14[0] = local_14[0] >> 0x10;
      if (*(uint *)&sound->field_0x229c != local_14[0]) {
        iVar4 = 0x10000;
        if (*(int *)&sound->field_0x22a4 < 0x10000) {
          iVar4 = *(int *)&sound->field_0x22a4;
        }
        if (iVar4 != 0) {
          uVar3 = *(undefined4 *)&sound->field_0x2294;
          iVar5 = *(int *)&sound->field_0x2290;
          *(int *)(iVar5 + 0xa0) = iVar4;
          *(undefined4 *)(iVar5 + 0xa4) = uVar3;
          ReadASync__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
          *(int *)&sound->field_0x2294 = *(int *)&sound->field_0x2294 + iVar4;
          *(int *)&sound->field_0x22a4 = *(int *)&sound->field_0x22a4 - iVar4;
          *(uint *)&sound->field_0x229c = local_14[0];
          *(undefined4 *)&sound->field_0x22a8 = 1;
        }
      }
    }
    else {
      iVar4 = IsCompleted__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
      if (iVar4 != 0) {
        memcpy((void *)(*(int *)&sound->field_0x228c + (1 - *(int *)&sound->field_0x229c) * 0x10000)
               ,File.m_readBuffer,0x10000);
        *(undefined4 *)&sound->field_0x22a8 = 0;
        if (*(int *)&sound->field_0x22a4 == 0) {
          Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
          *(undefined4 *)&sound->field_0x2290 = 0;
        }
        else {
          Reset__Q25CFile7CHandleFv(*(CFileCHandle **)&sound->field_0x2290);
        }
      }
    }
  }
  return;
}

