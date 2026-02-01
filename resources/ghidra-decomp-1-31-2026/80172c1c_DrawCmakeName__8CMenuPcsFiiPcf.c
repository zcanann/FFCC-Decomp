// Function: DrawCmakeName__8CMenuPcsFiiPcf
// Entry: 80172c1c
// Size: 732 bytes

/* WARNING: Removing unreachable block (ram,0x80172edc) */
/* WARNING: Removing unreachable block (ram,0x80172ed4) */
/* WARNING: Removing unreachable block (ram,0x80172c34) */
/* WARNING: Removing unreachable block (ram,0x80172c2c) */

void DrawCmakeName__8CMenuPcsFiiPcf
               (double param_1,CMenuPcs *menuPcs,int param_3,int param_4,undefined4 param_5)

{
  uint uVar1;
  int iVar2;
  float fVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  CFont *font;
  int iVar6;
  double dVar7;
  double dVar8;
  undefined4 local_80;
  undefined4 local_7c;
  undefined auStack_78 [4];
  undefined4 local_74;
  double local_70;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  double local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  iVar6 = 300;
  uVar1 = (uint)-((double)FLOAT_80333364 * DOUBLE_80333298 - DOUBLE_80333288);
  local_70 = (double)(longlong)(int)uVar1;
  if (param_3 != 0) {
    iVar6 = 0x130;
  }
  font = *(CFont **)&menuPcs->field_0xf8;
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  fVar3 = FLOAT_80333258;
  font->renderFlags = font->renderFlags & 0xef | 0x10;
  SetMargin__5CFontFf(fVar3,font);
  dVar8 = (double)(float)((double)FLOAT_80333240 * param_1);
  iVar2 = (int)((double)FLOAT_80333240 * param_1);
  local_68 = (longlong)iVar2;
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_78,0xff,0xff,0xff,iVar2);
  local_74 = *puVar4;
  SetColor__5CFontF8_GXColor(font,&local_74);
  SetTlut__5CFontFi(font,6);
  dVar7 = (double)GetWidth__5CFontFPc(font,param_5);
  uStack_5c = uVar1 ^ 0x80000000;
  local_60 = 0x43300000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_803332d0),font);
  local_58 = (double)(CONCAT44(0x43300000,iVar6 + -4) ^ 0x80000000);
  SetPosY__5CFontFf((float)(local_58 - DOUBLE_803332d0),font);
  Draw__5CFontFPc(font,param_5);
  font->renderFlags = font->renderFlags & 0xef;
  DrawInit__8CMenuPcsFv(menuPcs);
  if (param_4 != 0) {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_58 = (double)(longlong)(int)dVar8;
    local_80 = CONCAT31(0xffffff,(char)(int)dVar8);
    local_7c = local_80;
    GXSetChanMatColor(4,&local_7c);
    uVar5 = 0x39;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar5 = 0x60;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
    uStack_5c = uVar1 ^ 0x80000000;
    local_60 = 0x43300000;
    uStack_4c = iVar6 - 0x10U ^ 0x80000000;
    local_50 = 0x43300000;
    iVar6 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_803332d0) + dVar7)
    ;
    local_68 = (longlong)iVar6;
    iVar2 = (int)System.m_frameCounter >> 0x1f;
    local_48 = 0x43300000;
    uStack_44 = ((iVar2 * 8 | (uint)(((int)System.m_frameCounter >> 1) * 0x20000000 + iVar2) >> 0x1d
                 ) - iVar2) * 0x20 ^ 0x80000000;
    local_70 = (double)(CONCAT44(0x43300000,iVar6) ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_70 - DOUBLE_803332d0),
               (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_803332d0),
               (double)FLOAT_803332dc,(double)FLOAT_803332b0,
               (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_803332d0),
               (double)FLOAT_80333254,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  return;
}

