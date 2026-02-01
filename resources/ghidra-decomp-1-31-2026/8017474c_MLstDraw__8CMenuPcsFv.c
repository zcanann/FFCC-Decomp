// Function: MLstDraw__8CMenuPcsFv
// Entry: 8017474c
// Size: 1436 bytes

/* WARNING: Removing unreachable block (ram,0x80174ccc) */
/* WARNING: Removing unreachable block (ram,0x80174cc4) */
/* WARNING: Removing unreachable block (ram,0x80174cbc) */
/* WARNING: Removing unreachable block (ram,0x80174cb4) */
/* WARNING: Removing unreachable block (ram,0x80174cac) */
/* WARNING: Removing unreachable block (ram,0x80174ca4) */
/* WARNING: Removing unreachable block (ram,0x80174784) */
/* WARNING: Removing unreachable block (ram,0x8017477c) */
/* WARNING: Removing unreachable block (ram,0x80174774) */
/* WARNING: Removing unreachable block (ram,0x8017476c) */
/* WARNING: Removing unreachable block (ram,0x80174764) */
/* WARNING: Removing unreachable block (ram,0x8017475c) */

void MLstDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  uint uVar2;
  short sVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  short *psVar7;
  CFont *font;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double in_f31;
  double dVar13;
  undefined auStack_e0 [4];
  undefined4 local_dc;
  undefined auStack_d8 [4];
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_b8;
  uint uStack_b4;
  undefined4 local_b0;
  uint uStack_ac;
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  longlong local_90;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  psVar7 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  for (iVar6 = 0; iVar6 < **(short **)&menuPcs->field_0x850; iVar6 = iVar6 + 1) {
    if (-1 < *(int *)(psVar7 + 0xe)) {
      uStack_b4 = (int)*psVar7 ^ 0x80000000;
      uStack_ac = (int)psVar7[1] ^ 0x80000000;
      local_b8 = 0x43300000;
      dVar11 = (double)(float)((double)CONCAT44(0x43300000,uStack_b4) - DOUBLE_80333408);
      dVar10 = (double)FLOAT_803333d0;
      local_b0 = 0x43300000;
      dVar9 = (double)*(float *)(psVar7 + 8);
      dVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_ac) - DOUBLE_80333408);
      local_a8 = (double)CONCAT44(0x43300000,(int)psVar7[2] ^ 0x80000000);
      dVar13 = (double)(float)(local_a8 - DOUBLE_80333408);
      local_a0 = (double)CONCAT44(0x43300000,(int)psVar7[3] ^ 0x80000000);
      dVar8 = (double)(float)(local_a0 - DOUBLE_80333408);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(int *)(psVar7 + 0xe));
      local_98 = (double)(longlong)(int)((double)FLOAT_803333d4 * dVar9);
      local_cc = CONCAT31(0xffffff,(char)(int)((double)FLOAT_803333d4 * dVar9));
      local_d0 = local_cc;
      GXSetChanMatColor(4,&local_d0);
      if ((sVar3 == 1) && (iVar6 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
        local_98 = (double)(CONCAT44(0x43300000,(int)psVar7[3]) ^ 0x80000000);
        dVar11 = (double)(float)(dVar11 + DOUBLE_803333d8);
        dVar10 = (double)(float)(dVar10 + (double)(float)(local_98 - DOUBLE_80333408));
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,dVar12,dVar13,dVar8,(double)FLOAT_803333d0,dVar10,
                 (double)*(float *)(psVar7 + 10),(double)*(float *)(psVar7 + 10),&MenuPcs,0);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x5c);
      local_98 = (double)(CONCAT44(0x43300000,(int)*psVar7) ^ 0x80000000);
      in_f31 = (double)FLOAT_803333e0;
      dVar9 = local_98 - DOUBLE_80333408;
      dVar11 = (double)FLOAT_803333d0;
      local_a0 = (double)CONCAT44(0x43300000,(int)psVar7[1] - 6U ^ 0x80000000);
      if ((sVar3 == 1) && (iVar6 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
        local_98 = (double)(CONCAT44(0x43300000,(int)psVar7[3]) ^ 0x80000000);
        dVar11 = (double)(float)(dVar11 + (double)(float)(local_98 - DOUBLE_80333408));
      }
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)-(in_f31 * DOUBLE_803333e8 - dVar9),
                 (double)(float)(local_a0 - DOUBLE_80333408),(double)FLOAT_803333e0,
                 (double)FLOAT_803333e0,(double)FLOAT_803333d0,dVar11,
                 (double)*(float *)(psVar7 + 10),(double)*(float *)(psVar7 + 10),&MenuPcs,0);
    }
    psVar7 = psVar7 + 0x20;
  }
  font = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_803333f0,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_803333f0,font);
  DrawInit__5CFontFv(font);
  dVar11 = (double)FLOAT_803333d4;
  psVar7 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  dVar12 = (double)FLOAT_803333f4;
  dVar9 = DOUBLE_80333408;
  for (iVar6 = 0; iVar6 < **(short **)&menuPcs->field_0x850; iVar6 = iVar6 + 1) {
    local_98 = (double)(longlong)(int)(dVar11 * (double)*(float *)(psVar7 + 8));
    puVar5 = (undefined4 *)
             __ct__6CColorFUcUcUcUc
                       (auStack_d8,0xff,0xff,0xff,(int)(dVar11 * (double)*(float *)(psVar7 + 8)));
    local_d4 = *puVar5;
    SetColor__5CFontF8_GXColor(font,&local_d4);
    uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar6 + 0x2e);
    GetWidth__5CFontFPc(font,uVar4);
    local_a0 = (double)(CONCAT44(0x43300000,*psVar7 + 0x28) ^ 0x80000000);
    local_a8 = (double)(CONCAT44(0x43300000,psVar7[1] + 3) ^ 0x80000000);
    dVar8 = (double)(float)(local_a0 - dVar9);
    dVar10 = (double)(float)(local_a8 - dVar9);
    if ((sVar3 == 1) && (iVar6 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
      dVar8 = (double)(float)(dVar8 + DOUBLE_803333d8);
    }
    SetPosX__5CFontFf((float)dVar8,font);
    SetPosY__5CFontFf((float)(dVar10 - dVar12),font);
    Draw__5CFontFPc(font,uVar4);
    psVar7 = psVar7 + 0x20;
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  if (sVar3 == 1) {
    local_b0 = 0x43300000;
    psVar7 = (short *)(*(int *)&menuPcs->field_0x850 +
                      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8);
    iVar6 = (int)System.m_frameCounter >> 0x1f;
    uStack_ac = (int)psVar7[3] - 0x20U ^ 0x80000000;
    uStack_b4 = (int)psVar7[1] ^ 0x80000000;
    local_b8 = 0x43300000;
    local_98 = (double)CONCAT44(0x43300000,(int)*psVar7 - 0x38U ^ 0x80000000);
    local_a0 = (double)CONCAT44(0x43300000,
                                (iVar6 * 8 | System.m_frameCounter * 0x20000000 + iVar6 >> 0x1d) -
                                iVar6 ^ 0x80000000);
    iVar6 = (int)(((double)CONCAT44(0x43300000,uStack_ac) - DOUBLE_80333408) * DOUBLE_803333e8 +
                 ((double)CONCAT44(0x43300000,uStack_b4) - DOUBLE_80333408));
    local_90 = (longlong)iVar6;
    iVar1 = (int)((float)(local_98 - DOUBLE_80333408) + (float)(local_a0 - DOUBLE_80333408));
    local_a8 = (double)(longlong)iVar1;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_803333f0,menuPcs,iVar1,iVar6);
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
  uVar2 = (uint)(FLOAT_803333d4 * *(float *)(*(int *)&menuPcs->field_0x850 + 0x18));
  local_90 = (longlong)(int)uVar2;
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_e0,0xff,0xff,0xff,uVar2 & 0xff);
  local_dc = *puVar5;
  local_a0 = (double)(longlong)(int)FLOAT_80333400;
  local_98 = (double)(longlong)
                     (int)-(float)(in_f31 * (double)FLOAT_803333fc - (double)FLOAT_803333f8);
  DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,sVar3 + 0x25c);
  return;
}

