// Function: loadFont__8CMenuPcsFiPcii
// Entry: 80096d98
// Size: 840 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadFont__8CMenuPcsFiPcii
               (CMenuPcs *menuPcs,int param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  CFileCHandle *fileHandle;
  CFont *font;
  int iVar2;
  int iVar3;
  CStage *stage;
  
  stage = (CStage *)0x0;
  if (param_2 == 1) {
    stage = *(CStage **)&menuPcs->field_0xf0;
  }
  else if (param_2 < 1) {
    if (-1 < param_2) {
      stage = *(CStage **)&menuPcs->field_0xec;
    }
  }
  else if (param_2 < 3) {
    stage = PartMng.m_pppEnvSt.m_stagePtr;
  }
  if ((param_4 == 0) && ((int)(-FontMan._8_4_ | FontMan._8_4_) < 0)) {
    *(undefined4 *)&menuPcs->field_0xf8 = FontMan._8_4_;
    *(int *)(*(int *)&menuPcs->field_0xf8 + 4) = *(int *)(*(int *)&menuPcs->field_0xf8 + 4) + 1;
  }
  else {
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_3,0,0);
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    font = (CFont *)__nw__5CFontFUlPQ27CMemory6CStagePci
                              (0x1440,MenuPcs._236_4_,s_p_menu_cpp_801d9d80,0xf8);
    if (font != (CFont *)0x0) {
      font = (CFont *)__ct__5CFontFv(font);
    }
    *(CFont **)(&menuPcs->field_0xf8 + param_4 * 4) = font;
    Create__5CFontFPvPQ27CMemory6CStage
              (*(CFont **)(&menuPcs->field_0xf8 + param_4 * 4),File.m_readBuffer,stage);
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  }
  if (param_5 < 2) {
    iVar1 = param_4 * 4;
    iVar3 = 0;
    do {
      iVar2 = 0;
      do {
        SetTlutColor__5CFontFii8_GXColor(*(CFont **)(&menuPcs->field_0xf8 + iVar1),iVar2);
        SetTlutColor__5CFontFii8_GXColor(*(CFont **)(&menuPcs->field_0xf8 + iVar1),iVar2 + 0x1c);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x1c);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x10);
    FlushTlutColor__5CFontFv(*(CFont **)(&menuPcs->field_0xf8 + iVar1));
  }
  return;
}

