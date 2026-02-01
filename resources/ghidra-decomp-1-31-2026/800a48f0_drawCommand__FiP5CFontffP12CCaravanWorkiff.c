// Function: drawCommand__FiP5CFontffP12CCaravanWorkiff
// Entry: 800a48f0
// Size: 844 bytes

/* WARNING: Removing unreachable block (ram,0x800a4c20) */
/* WARNING: Removing unreachable block (ram,0x800a4c18) */
/* WARNING: Removing unreachable block (ram,0x800a4c10) */
/* WARNING: Removing unreachable block (ram,0x800a4c08) */
/* WARNING: Removing unreachable block (ram,0x800a4c00) */
/* WARNING: Removing unreachable block (ram,0x800a4bf8) */
/* WARNING: Removing unreachable block (ram,0x800a4bf0) */
/* WARNING: Removing unreachable block (ram,0x800a4930) */
/* WARNING: Removing unreachable block (ram,0x800a4928) */
/* WARNING: Removing unreachable block (ram,0x800a4920) */
/* WARNING: Removing unreachable block (ram,0x800a4918) */
/* WARNING: Removing unreachable block (ram,0x800a4910) */
/* WARNING: Removing unreachable block (ram,0x800a4908) */
/* WARNING: Removing unreachable block (ram,0x800a4900) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawCommand__FiP5CFontffP12CCaravanWorkiff
               (double param_1,double param_2,double param_3,double param_4,int param_5,CFont *font,
               CCaravanWork *caravanWork,int param_8)

{
  float fVar1;
  bool bVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int32_t iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  undefined auStack_a8 [4];
  undefined4 local_a4;
  undefined4 local_a0;
  uint uStack_9c;
  undefined4 local_98;
  uint uStack_94;
  longlong local_90;
  
  if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
    iVar7 = Game.game.m_cFlatDataArr[1].m_table[4].index[param_8 + 0x1e];
  }
  else if (param_8 < 2) {
    iVar4 = 9;
    if (param_8 == 0) {
      iVar4 = 1;
    }
    iVar7 = Game.game.m_cFlatDataArr[1].m_table[4].index[iVar4];
  }
  else {
    iVar7 = _GetWeaponAttrib__12CCaravanWorkFi(caravanWork,param_8);
  }
  if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
    uVar6 = 7;
    if (param_8 == 2) {
      uVar6 = 4;
    }
    else if (param_8 < 2) {
      if (param_8 == 0) {
        uVar6 = 2;
      }
      else if (-1 < param_8) {
        uVar6 = 1;
      }
    }
    else if (param_8 == 4) {
      uVar6 = 7;
    }
    else if (param_8 < 4) {
      uVar6 = 6;
    }
    SetTlut__5CFontFi(font,uVar6);
  }
  else if (param_8 == 0) {
    SetTlut__5CFontFi(font,7);
  }
  else {
    SetTlut__5CFontFi(font,4);
  }
  dVar8 = (double)sin(param_3);
  dVar10 = (double)(FLOAT_80330ac4 * (float)dVar8);
  dVar8 = (double)sin(param_3);
  bVar2 = false;
  if ((param_5 == 0) || (param_5 == 3)) {
    bVar2 = true;
  }
  uStack_9c = 1;
  if (bVar2) {
    uStack_9c = 0xffffffff;
  }
  uStack_9c = uStack_9c ^ 0x80000000;
  local_a0 = 0x43300000;
  dVar8 = (double)((float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_80330a00) *
                  FLOAT_80330a40 * (float)dVar8);
  if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
    dVar8 = (double)(float)(dVar8 + (double)FLOAT_80330a28);
  }
  SetScale__5CFontFf((float)-(DOUBLE_80330ad0 * ABS(param_3) - DOUBLE_80330ac8),font);
  dVar9 = (double)GetWidth__5CFontFPc(font,iVar7);
  uStack_94 = (uint)*(ushort *)&font->field_0xa;
  local_98 = 0x43300000;
  fVar1 = (float)-(DOUBLE_80330ad8 * ABS(param_3) - DOUBLE_80330a98);
  dVar11 = (double)((float)((double)CONCAT44(0x43300000,uStack_94) - DOUBLE_80330ae0) * font->scaleY
                   );
  fVar3 = FLOAT_803309c0;
  if ((FLOAT_803309c0 <= fVar1) && (fVar3 = fVar1, FLOAT_803309cc < fVar1)) {
    fVar3 = FLOAT_803309cc;
  }
  iVar4 = (int)((float)((double)FLOAT_80330a34 * param_4) * fVar3);
  local_90 = (longlong)iVar4;
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_a8,0xff,0xff,0xff,iVar4);
  local_a4 = *puVar5;
  SetColor__5CFontF8_GXColor(font,&local_a4);
  SetPosX__5CFontFf((float)(dVar10 + -(double)(float)(dVar9 * (double)FLOAT_803309c4 -
                                                     (double)(float)((double)FLOAT_80330aa8 +
                                                                    param_1))),font);
  SetPosY__5CFontFf(FLOAT_80330a40 +
                    (float)(dVar8 + -(double)(float)(dVar11 * (double)FLOAT_803309c4 -
                                                    (double)(float)((double)FLOAT_803309ec + param_2
                                                                   ))),font);
  SetPosZ__5CFontFf(FLOAT_803309c0,font);
  Draw__5CFontFPc(font,iVar7);
  return;
}

