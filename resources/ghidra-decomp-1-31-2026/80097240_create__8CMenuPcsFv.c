// Function: create__8CMenuPcsFv
// Entry: 80097240
// Size: 592 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void create__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  CStage *pCVar1;
  char *pcVar2;
  CFileCHandle *fileHandle;
  CTextureSet *textureSet;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  CMenuPcs *pCVar7;
  undefined **ppuVar8;
  undefined auStack_1a8 [128];
  undefined auStack_128 [256];
  
  iVar5 = 0xc4000;
  if (FontMan._8_4_ != 0) {
    iVar5 = GetInternal22Size__8CFontManFv(&FontMan);
    iVar5 = 0xc4000 - iVar5;
  }
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,iVar5,s_CMenuPcs_801d9d3c,0);
  *(CStage **)&menuPcs->field_0xec = pCVar1;
  *(undefined4 *)&menuPcs->field_0x740 = 0xffffffff;
  memset(&menuPcs->field_0x14c,0,0x40);
  memset(&menuPcs->field_0x18c,0,0x1a4);
  pcVar2 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_1a8,s_dvd__smenu_gc22_fnt_801d9db4,pcVar2);
  loadFont__8CMenuPcsFiPcii(menuPcs,0,auStack_1a8,0,0);
  iVar5 = 0;
  ppuVar8 = &PTR_s_common_8032e7a0;
  pCVar7 = menuPcs;
  do {
    pcVar2 = GetLangString__5CGameFv(&Game.game);
    sprintf(auStack_128,s_dvd__smenu__s_tex_801d9d6c,pcVar2,*ppuVar8);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_128,0,0);
    if (fileHandle != (CFileCHandle *)0x0) {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      uVar3 = MapMng._0_4_;
      if (*(int *)&menuPcs->field_0x740 != 1) {
        uVar3 = *(undefined4 *)&menuPcs->field_0xec;
      }
      textureSet = (CTextureSet *)
                   __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                             ((CTextureSet *)0x24,MenuPcs._236_4_,s_p_menu_cpp_801d9d80,0x182);
      if (textureSet != (CTextureSet *)0x0) {
        textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
      }
      *(CTextureSet **)&pCVar7->field_0x14c = textureSet;
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                (*(CTextureSet **)&pCVar7->field_0x14c,File.m_readBuffer,uVar3,0,0,0,0);
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    }
    iVar5 = iVar5 + 1;
    pCVar7 = (CMenuPcs *)&pCVar7->field_0x4;
    ppuVar8 = ppuVar8 + 1;
  } while (iVar5 < 2);
  piVar6 = &DAT_8020ef9c;
  iVar5 = 0;
  pCVar7 = menuPcs;
  do {
    uVar3 = Find__11CTextureSetFPc(*(CTextureSet **)(&menuPcs->field_0x14c + *piVar6 * 4),piVar6[1])
    ;
    iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                      (*(int *)(&menuPcs->field_0x14c + *piVar6 * 4) + 8,uVar3);
    iVar5 = iVar5 + 1;
    piVar6 = piVar6 + 2;
    *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
    *(int *)&pCVar7->field_0x18c = iVar4;
    pCVar7 = (CMenuPcs *)&pCVar7->field_0x4;
  } while (iVar5 < 0x16);
  changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(menuPcs,0);
  return;
}

