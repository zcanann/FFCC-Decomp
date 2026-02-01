// Function: loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
// Entry: 80096b94
// Size: 516 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
               (CMenuPcs *menuPcs,undefined4 *param_2,int param_3,int param_4,int *param_5,
               int param_6,int param_7,int param_8)

{
  char *pcVar1;
  CFileCHandle *fileHandle;
  CTextureSet *textureSet;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined auStack_148 [268];
  
  for (iVar4 = 0; iVar4 < param_4; iVar4 = iVar4 + 1) {
    pcVar1 = GetLangString__5CGameFv(&Game.game);
    sprintf(auStack_148,s_dvd__smenu__s_tex_801d9d6c,pcVar1,*param_2);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_148,0,0);
    if (fileHandle != (CFileCHandle *)0x0) {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      uVar2 = MapMng._0_4_;
      if ((*(int *)&menuPcs->field_0x740 != 1) && (param_8 != 3)) {
        if ((Game.game.m_gameWork.m_menuStageMode == '\0') || (param_8 == 0)) {
          uVar2 = *(undefined4 *)&menuPcs->field_0xec;
        }
        else if (param_8 == 1) {
          uVar2 = *(undefined4 *)&menuPcs->field_0xf0;
        }
        else {
          uVar2 = *(undefined4 *)&menuPcs->field_0xf4;
        }
      }
      textureSet = (CTextureSet *)
                   __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                             ((CTextureSet *)0x24,MenuPcs._236_4_,s_p_menu_cpp_801d9d80,0x182);
      if (textureSet != (CTextureSet *)0x0) {
        textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
      }
      iVar3 = (iVar4 + param_3) * 4;
      *(CTextureSet **)(&menuPcs->field_0x14c + iVar3) = textureSet;
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                (*(CTextureSet **)(&menuPcs->field_0x14c + iVar3),File.m_readBuffer,uVar2,0,0,0,0);
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    }
    param_2 = param_2 + 1;
  }
  for (iVar4 = 0; iVar4 < param_7; iVar4 = iVar4 + 1) {
    uVar2 = Find__11CTextureSetFPc
                      (*(CTextureSet **)(&menuPcs->field_0x14c + *param_5 * 4),param_5[1]);
    iVar3 = __vc__21CPtrArray<P8CTexture>FUl
                      (*(int *)(&menuPcs->field_0x14c + *param_5 * 4) + 8,uVar2);
    param_5 = param_5 + 2;
    *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
    *(int *)(&menuPcs->field_0x18c + (iVar4 + param_6) * 4) = iVar3;
  }
  return;
}

