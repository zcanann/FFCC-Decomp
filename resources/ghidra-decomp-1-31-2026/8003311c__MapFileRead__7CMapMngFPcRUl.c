// Function: ?MapFileRead__7CMapMngFPcRUl
// Entry: 8003311c
// Size: 252 bytes

void _MapFileRead__7CMapMngFPcRUl(CMapMng *mapMng)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  CMapMng *pCVar5;
  
  iVar4 = 0;
  pCVar5 = mapMng;
  do {
    if ((*(CFileCHandle **)&pCVar5->field_0x22a2c != (CFileCHandle *)0x0) &&
       (iVar2 = IsCompleted__5CFileFPQ25CFile7CHandle
                          (&File,*(CFileCHandle **)&pCVar5->field_0x22a2c),
       pvVar1 = File.m_readBuffer, iVar2 != 0)) {
      iVar2 = GetLength__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&pCVar5->field_0x22a2c);
      CopyToAMemorySync__7CMemoryFPvPvUl
                (&Memory,pvVar1,*(undefined4 *)&mapMng->field_0x22998,iVar2 + 0x1fU & 0xffffffe0);
      *(int *)&pCVar5->field_0x229ac = iVar2;
      uVar3 = CheckSum__FPvi(pvVar1,iVar2);
      *(undefined4 *)&pCVar5->field_0x229ec = uVar3;
      *(int *)&mapMng->field_0x229a0 = *(int *)&mapMng->field_0x229a0 + 1;
      *(int *)&mapMng->field_0x22998 = *(int *)&mapMng->field_0x22998 + iVar2;
      Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&pCVar5->field_0x22a2c);
      *(undefined4 *)&pCVar5->field_0x22a2c = 0;
    }
    iVar4 = iVar4 + 1;
    pCVar5 = (CMapMng *)&pCVar5->field_0x4;
  } while (iVar4 < 0x10);
  return;
}

