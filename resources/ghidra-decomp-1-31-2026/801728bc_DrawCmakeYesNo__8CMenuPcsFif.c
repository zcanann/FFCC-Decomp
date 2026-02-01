// Function: DrawCmakeYesNo__8CMenuPcsFif
// Entry: 801728bc
// Size: 864 bytes

/* WARNING: Removing unreachable block (ram,0x80172c00) */
/* WARNING: Removing unreachable block (ram,0x80172bf8) */
/* WARNING: Removing unreachable block (ram,0x801728d4) */
/* WARNING: Removing unreachable block (ram,0x801728cc) */

void DrawCmakeYesNo__8CMenuPcsFif(double param_1,CMenuPcs *menuPcs,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  CFont *font;
  double dVar6;
  undefined auStack_80 [4];
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  longlong local_70;
  undefined4 local_68;
  undefined *puStack_64;
  longlong local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  undefined *puStack_4c;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar6 = (double)(float)((double)FLOAT_80333240 * param_1);
  iVar1 = (int)((double)FLOAT_80333240 * param_1);
  local_70 = (longlong)iVar1;
  local_74 = CONCAT31(0xffffff,(char)iVar1);
  local_78 = local_74;
  GXSetChanMatColor(4,&local_78);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3a);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333348,(double)FLOAT_803332a4,(double)FLOAT_803332b0,
             (double)FLOAT_803332dc,(double)FLOAT_8033334c,(double)FLOAT_80333284,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333350,(double)FLOAT_803332a4,(double)FLOAT_803332b0,
             (double)FLOAT_803332dc,(double)FLOAT_8033334c,(double)FLOAT_80333284,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
  if (param_3 != 0) {
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3d);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_80333354,(double)FLOAT_80333358,(double)FLOAT_8033324c,
               (double)FLOAT_803332b0,(double)FLOAT_80333254,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80333258,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  SetTlut__5CFontFi(font,7);
  local_70 = (longlong)(int)dVar6;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_80,0xff,0xff,0xff,(int)dVar6);
  local_7c = *puVar3;
  SetColor__5CFontF8_GXColor(font,&local_7c);
  uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,1);
  dVar6 = (double)GetWidth__5CFontFPc(font,uVar4);
  puStack_64 = &DAT_800001d0;
  local_68 = 0x43300000;
  local_58 = 0x43300000;
  uVar2 = (uint)((float)((double)FLOAT_803332b0 - dVar6) * FLOAT_8033335c +
                (float)(4503601774854608.0 - DOUBLE_803332d0));
  local_60 = (longlong)(int)uVar2;
  uStack_54 = uVar2 ^ 0x80000000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_803332d0),font);
  SetPosY__5CFontFf(FLOAT_80333360,font);
  Draw__5CFontFPc(font,uVar4);
  uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,2);
  dVar6 = (double)GetWidth__5CFontFPc(font,uVar4);
  puStack_4c = &DAT_80000218;
  local_50 = 0x43300000;
  local_40 = 0x43300000;
  uVar5 = (uint)((float)((double)FLOAT_803332b0 - dVar6) * FLOAT_8033335c +
                (float)(4.50360177485468e+15 - DOUBLE_803332d0));
  local_48 = (longlong)(int)uVar5;
  uStack_3c = uVar5 ^ 0x80000000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_803332d0),font);
  SetPosY__5CFontFf(FLOAT_80333360,font);
  Draw__5CFontFPc(font,uVar4);
  DrawInit__8CMenuPcsFv(menuPcs);
  if (param_3 != 0) {
    if (param_3 == 1) {
      uVar5 = uVar2;
    }
    iVar1 = (int)System.m_frameCounter >> 0x1f;
    DrawCursor__8CMenuPcsFiif
              (param_1,menuPcs,
               (uVar5 - 0x24) +
               ((iVar1 * 8 | System.m_frameCounter * 0x20000000 + iVar1 >> 0x1d) - iVar1),0x175);
  }
  return;
}

