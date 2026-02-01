// Function: DrawBuySellInfo__9CShopMenuFv
// Entry: 8015173c
// Size: 2140 bytes

/* WARNING: Removing unreachable block (ram,0x80151f7c) */
/* WARNING: Removing unreachable block (ram,0x80151f74) */
/* WARNING: Removing unreachable block (ram,0x80151754) */
/* WARNING: Removing unreachable block (ram,0x8015174c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawBuySellInfo__9CShopMenuFv(CShopMenu *shopMenu)

{
  bool bVar1;
  undefined4 font;
  undefined4 uVar2;
  float fVar3;
  undefined4 *puVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  undefined4 uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined4 local_138;
  undefined auStack_134 [4];
  undefined4 local_130;
  undefined auStack_12c [4];
  undefined auStack_128 [4];
  undefined4 local_124;
  undefined auStack_120 [64];
  undefined auStack_e0 [64];
  double local_a0;
  undefined8 local_98;
  undefined8 local_90;
  double local_88;
  longlong local_80;
  undefined4 local_78;
  uint uStack_74;
  longlong local_70;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  undefined4 local_58;
  uint uStack_54;
  longlong local_50;
  undefined4 local_48;
  uint uStack_44;
  
  font = MenuPcs._248_4_;
  iVar7 = Game.game.m_gameWork.m_languageId - 1;
  DrawInit__5CFontFv((CFont *)MenuPcs._248_4_);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
  SetShadow__5CFontFi((CFont *)font,1);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)font);
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_128,0xff,0xff,0xff,0xff);
  local_124 = *puVar4;
  SetColor__5CFontF8_GXColor((CFont *)font,&local_124);
  puVar8 = (&PTR_s_Price_80214dc4)[iVar7 * 0x15];
  dVar12 = (double)GetWidth__5CFontFPc((CFont *)font,puVar8);
  dVar11 = (double)FLOAT_80332d7c;
  local_a0 = (double)(longlong)(int)(dVar11 - dVar12);
  DrawInit__5CFontFv((CFont *)font);
  local_98 = (double)CONCAT44(0x43300000,(int)(dVar11 - dVar12) ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_98 - DOUBLE_80332d20),(double)FLOAT_80332d80,&MenuPcs,font,puVar8
             ,0x13,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawInit__5CFontFv((CFont *)font);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)FLOAT_80332d7c,(double)FLOAT_80332d80,&MenuPcs,font,&DAT_80332d84,0x18,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  puVar8 = (&PTR_s_Money_80214db0)[iVar7 * 0x15];
  dVar11 = (double)GetWidth__5CFontFPc((CFont *)font,&DAT_80332d84);
  DrawInit__5CFontFv((CFont *)font);
  local_90 = (double)(longlong)(int)((double)FLOAT_80332d7c + dVar11);
  local_88 = (double)(CONCAT44(0x43300000,(int)((double)FLOAT_80332d7c + dVar11)) ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_88 - DOUBLE_80332d20),(double)FLOAT_80332d80,&MenuPcs,font,puVar8
             ,0x14,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawInit__5CFontFv((CFont *)font);
  SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
  SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
  puVar8 = (&PTR_DAT_80214da8)[iVar7 * 0x15];
  dVar11 = (double)GetWidth__5CFontFPc((CFont *)font,puVar8);
  iVar7 = *(int *)&shopMenu->field_0x28;
  if (iVar7 == -1) {
    bVar1 = false;
  }
  else {
    iVar6 = *(int *)&shopMenu->field_0x14;
    if (iVar6 == 0) {
      iVar9 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xbe6);
    }
    else if (iVar6 == 1) {
      iVar9 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xb6);
    }
    else if (iVar6 == 2) {
      if (*(int *)(&shopMenu->field_0x50 + iVar7 * 4) == -1) {
        iVar9 = -1;
      }
      else {
        iVar9 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                *(int *)(&shopMenu->field_0x50 + iVar7 * 4) * 2 + 0xb6);
      }
    }
    else {
      iVar9 = -1;
    }
    if (iVar9 < 1) {
      bVar1 = false;
    }
    else if (iVar6 == 0) {
      bVar1 = true;
    }
    else if (iVar6 == 2) {
      bVar1 = true;
      if ((*(uint *)(*(int *)&shopMenu->field_0x20 + ((int)(iVar9 - 0x191U) >> 5) * 4 + 0xc08) &
          1 << (iVar9 - 0x191U & 0x1f)) == 0) {
        bVar1 = false;
      }
    }
    else {
      cVar5 = EquipChk__8CMenuPcsFi(&MenuPcs,iVar7);
      if (cVar5 == '\0') {
        if (iVar9 < 0x9f) {
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
  uVar2 = MenuPcs._248_4_;
  if (bVar1) {
    iVar7 = *(int *)&shopMenu->field_0x28;
    if (iVar7 == -1) {
      iVar7 = 0;
    }
    else {
      iVar6 = *(int *)&shopMenu->field_0x14;
      if (iVar6 == 0) {
        iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xbe6);
      }
      else if (iVar6 == 1) {
        iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar7 * 2 + 0xb6);
      }
      else if (iVar6 == 2) {
        if (*(int *)(&shopMenu->field_0x50 + iVar7 * 4) == -1) {
          iVar7 = -1;
        }
        else {
          iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                  *(int *)(&shopMenu->field_0x50 + iVar7 * 4) * 2 + 0xb6);
        }
      }
      else {
        iVar7 = -1;
      }
      if (iVar6 == 0) {
        if (iVar7 < 1) {
          iVar7 = 0;
        }
        else {
          iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                  (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar7 * 0x48 + 0x20);
          iVar7 = iVar7 / 100 + (iVar7 >> 0x1f);
          iVar7 = iVar7 - (iVar7 >> 0x1f);
        }
      }
      else if (iVar6 == 1) {
        if (iVar7 < 1) {
          iVar7 = 0;
        }
        else {
          iVar7 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                  (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar7 * 0x48 + 0x20);
          iVar7 = iVar7 / 100 + (iVar7 >> 0x1f);
          local_88 = (double)(CONCAT44(0x43300000,iVar7 - (iVar7 >> 0x1f)) ^ 0x80000000);
          iVar7 = (int)(FLOAT_80332d60 * (float)(local_88 - DOUBLE_80332d20));
          local_90 = (double)(longlong)iVar7;
        }
      }
      else {
        iVar7 = -1;
      }
      iVar7 = *(int *)&shopMenu->field_0x44 * iVar7;
    }
  }
  else {
    iVar7 = 0;
  }
  dVar14 = (double)(float)((double)FLOAT_80332d88 - dVar11);
  dVar12 = dVar14 - (double)FLOAT_80332d5c;
  local_88 = (double)(longlong)(int)dVar12;
  SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
  SetScaleX__5CFontFf(FLOAT_80332d28,(CFont *)uVar2);
  SetScaleY__5CFontFf(FLOAT_80332d8c,(CFont *)uVar2);
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_12c,0xff,0xff,0xff,0xff);
  local_130 = *puVar4;
  SetColor__5CFontF8_GXColor((CFont *)uVar2,&local_130);
  DrawInit__5CFontFv((CFont *)uVar2);
  fVar3 = FLOAT_80332d64;
  *(byte *)(uVar2 + 0x24) = *(byte *)(uVar2 + 0x24) & 0xef | 0x10;
  SetMargin__5CFontFf(fVar3,(CFont *)uVar2);
  sprintf(auStack_e0,&DAT_80332d14,iVar7);
  dVar13 = (double)GetWidth__5CFontFPc((CFont *)uVar2,auStack_e0);
  local_90 = (double)CONCAT44(0x43300000,(int)dVar12 ^ 0x80000000);
  iVar7 = (int)((double)(float)(local_90 - DOUBLE_80332d20) - dVar13);
  local_98 = (double)(longlong)iVar7;
  local_a0 = (double)(CONCAT44(0x43300000,iVar7) ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_a0 - DOUBLE_80332d20),(double)FLOAT_80332d90,&MenuPcs,uVar2,
             auStack_e0,0x13,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  uVar2 = MenuPcs._248_4_;
  dVar13 = (double)(float)((double)FLOAT_80332d94 - dVar11);
  uVar10 = *(undefined4 *)(*(int *)&shopMenu->field_0x20 + 0x200);
  dVar11 = dVar13 - (double)FLOAT_80332d5c;
  local_80 = (longlong)(int)dVar11;
  SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
  SetScaleX__5CFontFf(FLOAT_80332d28,(CFont *)uVar2);
  SetScaleY__5CFontFf(FLOAT_80332d8c,(CFont *)uVar2);
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_134,0xff,0xff,0xff,0xff);
  local_138 = *puVar4;
  SetColor__5CFontF8_GXColor((CFont *)uVar2,&local_138);
  DrawInit__5CFontFv((CFont *)uVar2);
  fVar3 = FLOAT_80332d64;
  *(byte *)(uVar2 + 0x24) = *(byte *)(uVar2 + 0x24) & 0xef | 0x10;
  SetMargin__5CFontFf(fVar3,(CFont *)uVar2);
  sprintf(auStack_120,&DAT_80332d14,uVar10);
  dVar12 = (double)GetWidth__5CFontFPc((CFont *)uVar2,auStack_120);
  uStack_74 = (int)dVar11 ^ 0x80000000;
  local_78 = 0x43300000;
  local_68 = 0x43300000;
  uStack_64 = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80332d20) -
                    dVar12);
  local_70 = (longlong)(int)uStack_64;
  uStack_64 = uStack_64 ^ 0x80000000;
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80332d20),
             (double)FLOAT_80332d90,&MenuPcs,uVar2,auStack_120,0x14,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawInit__5CFontFv((CFont *)font);
  SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
  SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
  local_60 = (longlong)(int)dVar14;
  DrawInit__5CFontFv((CFont *)font);
  uStack_54 = (int)dVar14 ^ 0x80000000;
  local_58 = 0x43300000;
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20),
             (double)FLOAT_80332d98,&MenuPcs,font,puVar8,0x19,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawInit__5CFontFv((CFont *)font);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)FLOAT_80332d7c,(double)FLOAT_80332d98,&MenuPcs,font,&DAT_80332d84,0x1b,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawInit__5CFontFv((CFont *)font);
  local_50 = (longlong)(int)dVar13;
  local_48 = 0x43300000;
  uStack_44 = (int)dVar13 ^ 0x80000000;
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332d20),
             (double)FLOAT_80332d98,&MenuPcs,font,puVar8,0x19,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  return;
}

