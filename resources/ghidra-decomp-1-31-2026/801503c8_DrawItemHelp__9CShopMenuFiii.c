// Function: DrawItemHelp__9CShopMenuFiii
// Entry: 801503c8
// Size: 1048 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawItemHelp__9CShopMenuFiii(CShopMenu *shopMenu,int param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  char cVar4;
  void *ptr;
  undefined4 *puVar3;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  double dVar11;
  undefined auStack_48 [4];
  undefined4 local_44;
  longlong local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  iVar2 = *(int *)&shopMenu->field_0x14;
  iVar5 = *(int *)&shopMenu->field_0x28;
  if (iVar2 == 0) {
    iVar10 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xbe6);
  }
  else if (iVar2 == 1) {
    iVar10 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xb6);
  }
  else if (iVar2 == 2) {
    if (*(int *)(&shopMenu->field_0x50 + iVar5 * 4) == -1) {
      iVar10 = -1;
    }
    else {
      iVar10 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                               *(int *)(&shopMenu->field_0x50 + iVar5 * 4) * 2 + 0xb6);
    }
  }
  else {
    iVar10 = -1;
  }
  uVar7 = (uint)Game.game.m_gameWork.m_languageId;
  if (0 < iVar10) {
    if (iVar5 == -1) {
      bVar1 = false;
    }
    else {
      if (iVar2 == 0) {
        iVar8 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xbe6);
      }
      else if (iVar2 == 1) {
        iVar8 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xb6);
      }
      else if (iVar2 == 2) {
        if (*(int *)(&shopMenu->field_0x50 + iVar5 * 4) == -1) {
          iVar8 = -1;
        }
        else {
          iVar8 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                  *(int *)(&shopMenu->field_0x50 + iVar5 * 4) * 2 + 0xb6);
        }
      }
      else {
        iVar8 = -1;
      }
      if (iVar8 < 1) {
        bVar1 = false;
      }
      else if (iVar2 == 0) {
        bVar1 = true;
      }
      else if (iVar2 == 2) {
        bVar1 = true;
        if ((*(uint *)(*(int *)&shopMenu->field_0x20 + ((int)(iVar8 - 0x191U) >> 5) * 4 + 0xc08) &
            1 << (iVar8 - 0x191U & 0x1f)) == 0) {
          bVar1 = false;
        }
      }
      else {
        cVar4 = EquipChk__8CMenuPcsFi(&MenuPcs,iVar5);
        if (cVar4 == '\0') {
          if (iVar8 < 0x9f) {
            bVar1 = false;
          }
          else {
            bVar1 = true;
          }
        }
        else {
          bVar1 = false;
        }
      }
    }
    if (bVar1) {
      puVar9 = (undefined *)Game.game.m_cFlatDataArr[1].m_table[6].index[iVar10];
    }
    else {
      puVar9 = (&PTR_s_Cannot_be_crafted_here__80214de0)[(uVar7 - 1) * 0x15];
    }
    uVar6 = MenuPcs._236_4_;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      uVar6 = MenuPcs._244_4_;
    }
    ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x200,uVar6,s_shopmenu_cpp_801ded8c,0xbff);
    if ((ptr == (void *)0x0) && (System.m_execParam != 0)) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801ded9c,s_shopmenu_cpp_801ded8c,0xc01);
    }
    memset(ptr,0,0x200);
    MakeAgbString__4CMesFPcPcii(ptr,puVar9,0,1);
    uVar6 = MenuPcs._248_4_;
    SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
    SetShadow__5CFontFi((CFont *)uVar6,1);
    SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)uVar6);
    SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)uVar6);
    puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_48,0xff,0xff,0xff,0xff);
    local_44 = *puVar3;
    SetColor__5CFontF8_GXColor((CFont *)uVar6,&local_44);
    DrawInit__5CFontFv((CFont *)uVar6);
    dVar11 = (double)GetWidth__5CFontFPc((CFont *)uVar6,ptr);
    local_40 = (longlong)(int)dVar11;
    local_38 = 0x43300000;
    uVar7 = param_3 - (int)dVar11 / 2;
    uStack_34 = uVar7 + 1 ^ 0x80000000;
    SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80332d20),
                      (CFont *)uVar6);
    uStack_2c = param_4 - 3U ^ 0x80000000;
    local_30 = 0x43300000;
    SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80332d20),
                      (CFont *)uVar6);
    SetTlut__5CFontFi((CFont *)uVar6,0x12);
    Draw__5CFontFPc((CFont *)uVar6,ptr);
    uStack_24 = uVar7 ^ 0x80000000;
    local_28 = 0x43300000;
    SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80332d20),
                      (CFont *)uVar6);
    uStack_1c = param_4 - 4U ^ 0x80000000;
    local_20 = 0x43300000;
    SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80332d20),
                      (CFont *)uVar6);
    SetTlut__5CFontFi((CFont *)uVar6,7);
    Draw__5CFontFPc((CFont *)uVar6,ptr);
    __dla__FPv(ptr);
  }
  return;
}

