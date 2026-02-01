// Function: createBattle__8CMenuPcsFv
// Entry: 8009460c
// Size: 880 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void createBattle__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  char *pcVar1;
  CFileCHandle *fileHandle;
  CTextureSet *textureSet;
  undefined4 uVar2;
  int iVar3;
  CRingMenu *ringMenu;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  CMenuPcs *pCVar8;
  undefined **ppuVar9;
  int iVar10;
  undefined2 local_1b8;
  undefined uStack_1b6;
  undefined uStack_1b5;
  undefined auStack_1b4 [128];
  undefined auStack_134 [268];
  
  ppuVar9 = &PTR_s_shibuya_8020f23c;
  iVar10 = 0;
  pCVar8 = menuPcs;
  do {
    pcVar1 = GetLangString__5CGameFv(&Game.game);
    sprintf(auStack_134,s_dvd__smenu__s_tex_801d9d6c,pcVar1,*ppuVar9);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_134,0,0);
    if (fileHandle != (CFileCHandle *)0x0) {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      uVar2 = MapMng._0_4_;
      if (*(int *)&menuPcs->field_0x740 != 1) {
        uVar2 = *(undefined4 *)&menuPcs->field_0xec;
      }
      textureSet = (CTextureSet *)
                   __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                             ((CTextureSet *)0x24,MenuPcs._236_4_,s_p_menu_cpp_801d9d80,0x182);
      if (textureSet != (CTextureSet *)0x0) {
        textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
      }
      *(CTextureSet **)&pCVar8->field_0x154 = textureSet;
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                (*(CTextureSet **)&pCVar8->field_0x154,File.m_readBuffer,uVar2,0,0,0,0);
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    }
    iVar10 = iVar10 + 1;
    pCVar8 = (CMenuPcs *)&pCVar8->field_0x4;
    ppuVar9 = ppuVar9 + 1;
  } while (iVar10 < 2);
  piVar7 = &DAT_8020f260;
  iVar10 = 0;
  pCVar8 = menuPcs;
  do {
    uVar2 = Find__11CTextureSetFPc(*(CTextureSet **)(&menuPcs->field_0x14c + *piVar7 * 4),piVar7[1])
    ;
    iVar3 = __vc__21CPtrArray<P8CTexture>FUl
                      (*(int *)(&menuPcs->field_0x14c + *piVar7 * 4) + 8,uVar2);
    iVar10 = iVar10 + 1;
    piVar7 = piVar7 + 2;
    *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
    *(int *)&pCVar8->field_0x1e4 = iVar3;
    pCVar8 = (CMenuPcs *)&pCVar8->field_0x4;
  } while (iVar10 < 10);
  iVar10 = 0;
  pCVar8 = menuPcs;
  do {
    iVar3 = __nw__FUlPQ27CMemory6CStagePci(0x3dfc,MenuPcs._236_4_,s_p_menu_cpp_801d9d80,0x48b);
    if (iVar3 != 0) {
      iVar3 = __ct__8CMesMenuFv();
    }
    *(int *)&pCVar8->field_0x10c = iVar3;
    iVar3 = *(int *)&pCVar8->field_0x10c;
    *(int *)(iVar3 + 0x18) = iVar10;
    *(int *)(iVar3 + 0x1c) = iVar10;
    (**(code **)(**(int **)&pCVar8->field_0x10c + 0xc))();
    iVar10 = iVar10 + 1;
    pCVar8 = (CMenuPcs *)&pCVar8->field_0x4;
  } while (iVar10 < 0xc);
  iVar10 = 0;
  pCVar8 = menuPcs;
  do {
    ringMenu = (CRingMenu *)
               __nw__FUlPQ27CMemory6CStagePci(0x520,MenuPcs._236_4_,s_p_menu_cpp_801d9d80,0x492);
    if (ringMenu != (CRingMenu *)0x0) {
      ringMenu = (CRingMenu *)__ct__9CRingMenuFv(ringMenu);
    }
    *(CRingMenu **)&pCVar8->field_0x13c = ringMenu;
    *(int *)(*(int *)&pCVar8->field_0x13c + 8) = iVar10;
    (**(code **)(**(int **)&pCVar8->field_0x13c + 0xc))();
    iVar10 = iVar10 + 1;
    pCVar8 = (CMenuPcs *)&pCVar8->field_0x4;
  } while (iVar10 < 4);
  pcVar1 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_1b4,s_dvd__smenu_gc23_fnt_801d9d8c,pcVar1);
  loadFont__8CMenuPcsFiPcii(menuPcs,0,auStack_1b4,1,1);
  iVar10 = 0;
  do {
    uVar4 = GetTlutColor__8CTextureFi(*(CTexture **)&menuPcs->field_0x1ec,iVar10);
    uVar6 = uVar4 >> 8 & 0xff;
    uVar5 = uVar4 >> 0x10 & 0xff;
    iVar3 = (((uVar4 >> 0x18) + uVar5 + uVar6) / 3) * 2;
    _local_1b8 = CONCAT22(CONCAT11((char)((ulonglong)
                                          ((longlong)(int)((uVar4 >> 0x18) + iVar3) * 0x55555556) >>
                                         0x20),
                                   (char)((ulonglong)((longlong)(int)(uVar5 + iVar3) * 0x55555556)
                                         >> 0x20)),
                          CONCAT11((char)((ulonglong)((longlong)(int)(uVar6 + iVar3) * 0x55555556)
                                         >> 0x20),(char)uVar4));
    iVar3 = *(int *)(*(int *)&menuPcs->field_0x1ec + 0x60);
    if (iVar3 == 9) {
      uVar2 = 0x100;
    }
    else if (iVar3 == 8) {
      uVar2 = 0x10;
    }
    else {
      uVar2 = 0;
    }
    SetExternalTlutColor__8CTextureFPviiR8_GXColor(&menuPcs->field_0x340,uVar2,iVar10,&local_1b8);
    iVar10 = iVar10 + 1;
  } while (iVar10 < 0x100);
  FlushExternalTlut__8CTextureFPv(*(CTexture **)&menuPcs->field_0x1ec,&menuPcs->field_0x340);
  *(undefined2 *)&menuPcs->field_0x864 = 0;
  return;
}

