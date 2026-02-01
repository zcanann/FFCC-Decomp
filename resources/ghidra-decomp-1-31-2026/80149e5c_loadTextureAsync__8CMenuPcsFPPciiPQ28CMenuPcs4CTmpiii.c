// Function: loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
// Entry: 80149e5c
// Size: 952 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(CMenuPcs *menuPcs)

{
  short sVar1;
  char *pcVar2;
  CTextureSet *textureSet;
  undefined4 uVar3;
  int iVar4;
  CMenuPcs *pCVar5;
  int iVar6;
  int *piVar7;
  undefined auStack_118 [260];
  
  DAT_8032eec0 = (uint)(-(int)*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0) |
                       (int)*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0)) >> 0x1f;
  if (Game.game.m_gameWork.m_menuStageMode == '\0') {
    if (menuPcs->field_0x859 == '\0') {
      return;
    }
    *(undefined4 *)&menuPcs->field_0xf0 = 0;
    menuPcs->field_0x859 = 0;
    menuPcs->field_0x85a = 0;
    return;
  }
  if (menuPcs->field_0x859 == '\0') {
    createSingleMenu__8CMenuPcsFv(menuPcs);
  }
  if (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == '\0') {
    return;
  }
  if (menuPcs->field_0x85a == '\0') {
    SingMenuInit__8CMenuPcsFv(menuPcs);
  }
  if (*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0) == '\0') {
    iVar6 = *(int *)&menuPcs->field_0x85c;
    if (iVar6 < 2) {
      if (*(int *)&menuPcs->field_0x860 == 0) {
        pcVar2 = GetLangString__5CGameFv(&Game.game);
        sprintf(auStack_118,s_dvd__smenu__s_tex_801de8e4,pcVar2,(&PTR_s_solo1_80214b18)[iVar6]);
        DAT_8032eeb8 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
        ReadASync__5CFileFPQ25CFile7CHandle(&File,DAT_8032eeb8);
        *(int *)&menuPcs->field_0x860 = *(int *)&menuPcs->field_0x860 + 1;
      }
      else if (*(int *)&menuPcs->field_0x860 == 1) {
        iVar4 = IsCompleted__5CFileFPQ25CFile7CHandle(&File,DAT_8032eeb8);
        if (iVar4 == 0) {
          DAT_8032eebc = 0;
          goto LAB_8014a104;
        }
        uVar3 = MenuPcs._236_4_;
        if (Game.game.m_gameWork.m_menuStageMode != '\0') {
          uVar3 = MenuPcs._244_4_;
        }
        textureSet = (CTextureSet *)
                     __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                               ((CTextureSet *)0x24,uVar3,s_singmenu_cpp_801de8d4,0x748);
        if (textureSet != (CTextureSet *)0x0) {
          textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
        }
        *(CTextureSet **)(&menuPcs->field_0x160 + iVar6 * 4) = textureSet;
        if (Game.game.m_gameWork.m_menuStageMode == '\0') {
          uVar3 = *(undefined4 *)&menuPcs->field_0xec;
        }
        else {
          uVar3 = *(undefined4 *)&menuPcs->field_0xf4;
        }
        Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                  (*(CTextureSet **)(&menuPcs->field_0x160 + iVar6 * 4),File.m_readBuffer,uVar3,0,0,
                   0,0);
        Close__5CFileFPQ25CFile7CHandle(&File,DAT_8032eeb8);
        DAT_8032eeb8 = (CFileCHandle *)0x0;
        *(undefined4 *)&menuPcs->field_0x860 = 0;
        *(int *)&menuPcs->field_0x85c = *(int *)&menuPcs->field_0x85c + 1;
      }
      if (*(int *)&menuPcs->field_0x85c < 2) {
        DAT_8032eebc = 0;
      }
      else {
        piVar7 = &DAT_80214b3c;
        iVar6 = 0;
        pCVar5 = menuPcs;
        do {
          uVar3 = Find__11CTextureSetFPc
                            (*(CTextureSet **)(&menuPcs->field_0x14c + *piVar7 * 4),piVar7[1]);
          iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                            (*(int *)(&menuPcs->field_0x14c + *piVar7 * 4) + 8,uVar3);
          iVar6 = iVar6 + 1;
          piVar7 = piVar7 + 2;
          *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
          *(int *)&pCVar5->field_0x240 = iVar4;
          pCVar5 = (CMenuPcs *)&pCVar5->field_0x4;
        } while (iVar6 < 0x33);
        DAT_8032eebc = 1;
      }
    }
    else {
      DAT_8032eebc = 1;
    }
  }
LAB_8014a104:
  if (*(short *)(*(int *)&menuPcs->field_0x850 + 6) != 0) {
    *(short *)&menuPcs->field_0x866 = *(short *)&menuPcs->field_0x866 + 1;
    *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 6) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 4) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  }
  if (*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0) == '\x01') {
    if (menuPcs->m_shopMenuPtr == (CShopMenu *)0x0) {
      CreateShopMenu__8CMenuPcsFv(menuPcs);
    }
    else {
      Calc__9CShopMenuFv(menuPcs->m_shopMenuPtr);
    }
  }
  else if (*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0) == '\x02') {
    if (menuPcs->m_shopMenuPtr == (CShopMenu *)0x0) {
      CreateSmithMenu__8CMenuPcsFv(menuPcs);
    }
    else {
      Calc__9CShopMenuFv(menuPcs->m_shopMenuPtr);
    }
  }
  if (DAT_8032eec0 == 0) {
    sVar1 = *(short *)&menuPcs->field_0x866;
    if (sVar1 == 1) {
      SingleCalcCtrl__8CMenuPcsFv(menuPcs);
    }
    else if (sVar1 < 1) {
      if (-1 < sVar1) {
        SingleCalcFadeIn__8CMenuPcsFv(menuPcs);
      }
    }
    else if (sVar1 < 3) {
      SingleCalcFadeOut__8CMenuPcsFv(menuPcs);
    }
  }
  return;
}

