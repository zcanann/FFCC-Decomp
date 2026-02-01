// Function: DrawItemInfo__9CShopMenuFiiiiiiii
// Entry: 801507e0
// Size: 1640 bytes

/* WARNING: Removing unreachable block (ram,0x80150e34) */
/* WARNING: Removing unreachable block (ram,0x801507f0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawItemInfo__9CShopMenuFiiiiiiii
               (CShopMenu *shopMenu,int param_2,uint param_3,uint param_4,undefined4 param_5,
               uint param_6)

{
  uint uVar1;
  undefined2 uVar2;
  undefined4 font;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined *puVar9;
  double dVar10;
  undefined4 local_1c8;
  undefined auStack_1c4 [4];
  undefined auStack_1c0 [4];
  undefined4 local_1bc;
  undefined auStack_1b8 [64];
  char acStack_178 [256];
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  undefined4 local_58;
  uint uStack_54;
  longlong local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  font = MenuPcs._248_4_;
  if ((0 < param_2) && (param_2 < 0x9f)) {
    SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
    SetShadow__5CFontFi((CFont *)font,1);
    SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
    SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
    puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1c0,0xff,0xff,0xff,0xff);
    local_1bc = *puVar4;
    SetColor__5CFontF8_GXColor((CFont *)font,&local_1bc);
    DrawInit__5CFontFv((CFont *)font);
    puVar9 = (undefined *)0x0;
    uVar8 = (uint)Game.game.m_gameWork.m_languageId;
    iVar5 = GetEquipType__8CMenuPcsFi(&MenuPcs,param_2);
    if (iVar5 == 0) {
      iVar5 = 0;
      puVar9 = (&PTR_s_Strength_80214dd4)[(uVar8 - 1) * 0x15];
    }
    else {
      iVar5 = GetEquipType__8CMenuPcsFi(&MenuPcs,param_2);
      if (iVar5 == 3) {
        iVar5 = 2;
      }
      else {
        iVar5 = 1;
        puVar9 = (&PTR_s_Defence_80214dd8)[(uVar8 - 1) * 0x15];
      }
    }
    iVar6 = Game.game.unkCFlatData0[2] + param_2 * 0x48;
    uVar2 = *(undefined2 *)(iVar6 + 6);
    uVar8 = (uint)*(ushort *)(iVar6 + 8);
    if (puVar9 == (undefined *)0x0) {
      SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
      SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
      uVar7 = GetAttrStr__8CMenuPcsFi(&MenuPcs,uVar8);
      DrawInit__5CFontFv((CFont *)font);
      uStack_3c = param_3 + 0x40 ^ 0x80000000;
      local_40 = 0x43300000;
      uStack_44 = param_4 ^ 0x80000000;
      local_48 = 0x43300000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332d20),&MenuPcs,
                 font,uVar7,0x18,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      uVar7 = 9;
      if ((uVar8 == 0) || (8 < uVar8)) {
        if ((uVar8 == 0xb) || ((uVar8 == 0x11 || (uVar8 == 0x12)))) {
          sprintf(acStack_178,&DAT_80332d44,&DAT_80332d4c,uVar2);
        }
        else {
          if (((uVar8 != 9) && (uVar8 != 10)) && (uVar8 != 0xc)) {
            return;
          }
          sprintf(acStack_178,&DAT_80332d44,&DAT_80332d50,uVar2);
          uVar7 = 3;
        }
      }
      else {
        sprintf(acStack_178,&DAT_80332d40,&DAT_80332d38);
      }
      SetScaleX__5CFontFf(FLOAT_80332d28,(CFont *)font);
      dVar10 = (double)GetWidth__5CFontFPc((CFont *)font,acStack_178);
      DrawInit__5CFontFv((CFont *)font);
      uStack_3c = param_3 ^ 0x80000000;
      uStack_44 = param_4 ^ 0x80000000;
      local_40 = 0x43300000;
      local_48 = 0x43300000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20) +
                         (float)((double)FLOAT_80332d3c - dVar10)),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332d20),&MenuPcs,
                 font,acStack_178,uVar7,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
    }
    else {
      strcpy(acStack_178,puVar9);
      strcat(acStack_178,&DAT_80332d30);
      uStack_74 = param_3 + 0x40 ^ 0x80000000;
      local_78 = 0x43300000;
      dVar10 = (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80332d20);
      DrawInit__5CFontFv((CFont *)font);
      uStack_6c = param_4 ^ 0x80000000;
      local_70 = 0x43300000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                (dVar10,(double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80332d20),
                 &MenuPcs,font,acStack_178,0x18,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      uVar7 = MenuPcs._248_4_;
      uStack_64 = param_3 + 0x108 ^ 0x80000000;
      local_68 = 0x43300000;
      uVar1 = (uint)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80332d20);
      local_60 = (longlong)(int)uVar1;
      SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
      SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar7);
      puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1c4,0xff,0xff,0xff,0xff);
      local_1c8 = *puVar4;
      SetColor__5CFontF8_GXColor((CFont *)uVar7,&local_1c8);
      DrawInit__5CFontFv((CFont *)uVar7);
      fVar3 = FLOAT_80332d34;
      *(byte *)(uVar7 + 0x24) = *(byte *)(uVar7 + 0x24) & 0xef | 0x10;
      SetMargin__5CFontFf(fVar3,(CFont *)uVar7);
      sprintf(auStack_1b8,&DAT_80332d14,uVar2);
      dVar10 = (double)GetWidth__5CFontFPc((CFont *)uVar7,auStack_1b8);
      uStack_54 = uVar1 ^ 0x80000000;
      uStack_3c = param_4 ^ 0x80000000;
      local_58 = 0x43300000;
      local_40 = 0x43300000;
      local_48 = 0x43300000;
      uStack_44 = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20) -
                        dVar10);
      local_50 = (longlong)(int)uStack_44;
      uStack_44 = uStack_44 ^ 0x80000000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332d20),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20),&MenuPcs,
                 uVar7,auStack_1b8,0x1a,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      DrawInit__5CFontFv((CFont *)font);
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
      SetScale__5CFontFf(FLOAT_80332d28,(CFont *)font);
      if ((iVar5 == 1) && (uVar8 != 0)) {
        SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
        SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
        uVar7 = GetAttrStr__8CMenuPcsFi(&MenuPcs,uVar8);
        DrawInit__5CFontFv((CFont *)font);
        uStack_3c = param_3 + 0x40 ^ 0x80000000;
        local_40 = 0x43300000;
        uStack_44 = param_6 ^ 0x80000000;
        local_48 = 0x43300000;
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                  ((double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332d20),
                   &MenuPcs,font,uVar7,0x18,0x12);
        DrawInit__8CMenuPcsFv(&MenuPcs);
        SetScaleX__5CFontFf(FLOAT_80332d28,(CFont *)font);
        uVar7 = GetAttrStr__8CMenuPcsFi(&MenuPcs,uVar8);
        GetWidth__5CFontFPc((CFont *)font,uVar7);
        if ((uVar8 != 0) && (uVar8 < 9)) {
          strcpy(acStack_178,&DAT_80332d38);
          dVar10 = (double)GetWidth__5CFontFPc((CFont *)font,acStack_178);
          uStack_3c = param_3 ^ 0x80000000;
          local_40 = 0x43300000;
          dVar10 = (double)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20) +
                           (float)((double)FLOAT_80332d3c - dVar10));
          DrawInit__5CFontFv((CFont *)font);
          uStack_3c = param_6 ^ 0x80000000;
          local_40 = 0x43300000;
          DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                    (dVar10,(double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20
                                           ),&MenuPcs,font,acStack_178,9,0x12);
          DrawInit__8CMenuPcsFv(&MenuPcs);
        }
      }
    }
  }
  return;
}

