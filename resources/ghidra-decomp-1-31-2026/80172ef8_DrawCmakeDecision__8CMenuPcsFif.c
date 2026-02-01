// Function: DrawCmakeDecision__8CMenuPcsFif
// Entry: 80172ef8
// Size: 864 bytes

/* WARNING: Removing unreachable block (ram,0x8017323c) */
/* WARNING: Removing unreachable block (ram,0x80173234) */
/* WARNING: Removing unreachable block (ram,0x80172f10) */
/* WARNING: Removing unreachable block (ram,0x80172f08) */

void DrawCmakeDecision__8CMenuPcsFif(double param_1,CMenuPcs *menuPcs,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  CFont *font;
  double dVar6;
  undefined4 local_80;
  undefined4 local_7c;
  undefined auStack_78 [4];
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  longlong local_68;
  longlong local_60;
  longlong local_58;
  longlong local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar6 = (double)(float)((double)FLOAT_80333240 * param_1);
  iVar1 = (int)((double)FLOAT_80333240 * param_1);
  local_68 = (longlong)iVar1;
  local_6c = CONCAT31(0xffffff,(char)iVar1);
  local_70 = local_6c;
  GXSetChanMatColor(4,&local_70);
  uVar5 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar5 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333368,(double)FLOAT_803332a4,(double)FLOAT_803332b0,
             (double)FLOAT_803332dc,(double)FLOAT_8033334c,(double)FLOAT_80333284,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_8033336c,(double)FLOAT_803332a4,(double)FLOAT_803332b0,
             (double)FLOAT_803332dc,(double)FLOAT_8033334c,(double)FLOAT_80333284,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
  if (param_3 != 0) {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_68 = (longlong)(int)dVar6;
    local_80 = CONCAT31(0xffffff,(char)(int)dVar6);
    local_7c = local_80;
    GXSetChanMatColor(4,&local_7c);
    uVar5 = 0x3d;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar5 = 100;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_80333370,(double)FLOAT_80333358,(double)FLOAT_803332b0,
               (double)FLOAT_803332b0,(double)FLOAT_8033324c,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80333258,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  SetTlut__5CFontFi(font,7);
  local_68 = (longlong)(int)dVar6;
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_78,0xff,0xff,0xff,(int)dVar6);
  local_74 = *puVar4;
  SetColor__5CFontF8_GXColor(font,&local_74);
  uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,0x29);
  dVar6 = (double)GetWidth__5CFontFPc(font,uVar5);
  iVar1 = (int)DOUBLE_80333388;
  local_58 = (longlong)iVar1;
  local_48 = 0x43300000;
  uVar2 = (uint)((double)(float)((double)FLOAT_80333380 - dVar6) * DOUBLE_80333298 + DOUBLE_80333378
                );
  local_60 = (longlong)(int)uVar2;
  uStack_44 = uVar2 ^ 0x80000000;
  local_50 = local_60;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_803332d0),font);
  uStack_3c = iVar1 - 4U ^ 0x80000000;
  local_40 = 0x43300000;
  SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_803332d0),font);
  Draw__5CFontFPc(font,uVar5);
  DrawInit__8CMenuPcsFv(menuPcs);
  if (param_3 != 0) {
    iVar3 = (int)System.m_frameCounter >> 0x1f;
    DrawCursor__8CMenuPcsFiif
              (param_1,menuPcs,
               (uVar2 - 0x20) +
               ((iVar3 * 8 | System.m_frameCounter * 0x20000000 + iVar3 >> 0x1d) - iVar3),iVar1);
  }
  return;
}

