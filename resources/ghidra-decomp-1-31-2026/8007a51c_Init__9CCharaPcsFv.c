// Function: Init__9CCharaPcsFv
// Entry: 8007a51c
// Size: 1124 bytes

/* WARNING: Removing unreachable block (ram,0x8007a964) */
/* WARNING: Removing unreachable block (ram,0x8007a95c) */
/* WARNING: Removing unreachable block (ram,0x8007a954) */
/* WARNING: Removing unreachable block (ram,0x8007a53c) */
/* WARNING: Removing unreachable block (ram,0x8007a534) */
/* WARNING: Removing unreachable block (ram,0x8007a52c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Init__9CCharaPcsFv(CCharaPcs *charaPcs)

{
  float fVar1;
  float fVar2;
  byte bVar4;
  undefined4 uVar3;
  CStage *pCVar5;
  byte *pbVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  CCharaPcs *pCVar10;
  CCharaPcs *pCVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  undefined local_b8;
  undefined local_b7;
  undefined local_b6;
  undefined local_b5;
  undefined auStack_b4 [4];
  undefined4 local_b0;
  undefined auStack_ac [4];
  undefined local_a8;
  undefined local_a7;
  undefined local_a6;
  undefined local_a5;
  CVector CStack_a4;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  undefined4 local_70;
  uint uStack_6c;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  longlong local_58;
  
  pCVar5 = CreateStage__7CMemoryFUlPci(&Memory,0x38000,s_CCharaPcs_801d9a1c,0);
  *(CStage **)&charaPcs->field_0xc0 = pCVar5;
  pCVar5 = CreateStage__7CMemoryFUlPci(&Memory,0x380000,s_CCharaPcs_amem_801d9a28,2);
  *(CStage **)&charaPcs->field_0xc4 = pCVar5;
  pCVar5 = CreateStage__7CMemoryFUlPci(&Memory,0x70000,s_CCharaPcs_amemw_801d9a38,2);
  *(CStage **)&charaPcs->field_0xc8 = pCVar5;
  Chara._8284_4_ = *(undefined4 *)&charaPcs->field_0xc4;
  SetStage__36CPtrArray<PQ29CCharaPcs10CLoadModel>FPQ27CMemory6CStage
            ((CPtrArray *)&charaPcs->field_0x50,*(undefined4 *)&charaPcs->field_0xc0);
  SetDefaultSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl((CPtrArray *)&charaPcs->field_0x50,0x80)
  ;
  SetGrow__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fi((CPtrArray *)&charaPcs->field_0x50,0);
  SetStage__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FPQ27CMemory6CStage
            ((CPtrArray *)&charaPcs->field_0x6c,*(undefined4 *)&charaPcs->field_0xc0);
  SetDefaultSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&charaPcs->field_0x6c,0x200);
  SetGrow__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fi((CPtrArray *)&charaPcs->field_0x6c,0);
  SetStage__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FPQ27CMemory6CStage
            ((CPtrArray *)&charaPcs->field_0x88,*(undefined4 *)&charaPcs->field_0xc0);
  SetDefaultSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl
            ((CPtrArray *)&charaPcs->field_0x88,0x100);
  SetGrow__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fi((CPtrArray *)&charaPcs->field_0x88,0);
  SetStage__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FPQ27CMemory6CStage
            ((CPtrArray *)&charaPcs->loadPdtArray,*(CStage **)&charaPcs->field_0xc0);
  SetDefaultSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl((CPtrArray *)&charaPcs->loadPdtArray,0x80);
  SetGrow__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fi((CPtrArray *)&charaPcs->loadPdtArray,0);
  fVar2 = FLOAT_803302a4;
  fVar1 = FLOAT_80330288;
  iVar12 = 0;
  iVar13 = 2;
  pCVar10 = charaPcs;
  pCVar11 = charaPcs;
  do {
    pCVar10->field_0xe8 = 0x3f;
    pCVar10->field_0xe9 = 0x3f;
    pCVar10->field_0xea = 0x3f;
    pCVar10->field_0xeb = 0xff;
    if (iVar12 == 0) {
      uVar8 = countLeadingZeros(0);
      bVar4 = -((byte)(uVar8 >> 5) & 1) & 0x3f;
      uVar8 = countLeadingZeros(1);
      pCVar11->field_0xf0 = bVar4;
      pCVar11->field_0xf1 = bVar4;
      uVar9 = countLeadingZeros(2);
      pCVar11->field_0xf2 = bVar4;
      bVar4 = -((byte)(uVar8 >> 5) & 1) & 0x3f;
      pCVar11->field_0xf3 = 0xff;
      *(float *)&charaPcs->field_0x108 = fVar1;
      *(float *)&charaPcs->field_0x10c = fVar1;
      *(float *)&charaPcs->field_0x110 = fVar2;
      pCVar11->field_0xf4 = bVar4;
      pCVar11->field_0xf5 = bVar4;
      pCVar11->field_0xf6 = bVar4;
      bVar4 = -((byte)(uVar9 >> 5) & 1) & 0x3f;
      pCVar11->field_0xf7 = 0xff;
      *(float *)&charaPcs->field_0x114 = fVar1;
      *(float *)&charaPcs->field_0x118 = fVar1;
      *(float *)&charaPcs->field_0x11c = fVar2;
      pCVar11->field_0xf8 = bVar4;
      pCVar11->field_0xf9 = bVar4;
      pCVar11->field_0xfa = bVar4;
      pCVar11->field_0xfb = 0xff;
      *(float *)&charaPcs->field_0x120 = fVar1;
      *(float *)&charaPcs->field_0x124 = fVar1;
      *(float *)&charaPcs->field_0x128 = fVar2;
    }
    else {
      uVar8 = countLeadingZeros(0);
      bVar4 = -((byte)(uVar8 >> 5) & 1) & 0x3f;
      uVar8 = countLeadingZeros(1);
      pCVar11->field_0xf0 = bVar4;
      pCVar11->field_0xf1 = bVar4;
      uVar9 = countLeadingZeros(2);
      pCVar11->field_0xf2 = bVar4;
      bVar4 = -((byte)(uVar8 >> 5) & 1) & 0x3f;
      pCVar11->field_0xf3 = 0xff;
      pCVar11->field_0xf4 = bVar4;
      pCVar11->field_0xf5 = bVar4;
      pCVar11->field_0xf6 = bVar4;
      bVar4 = -((byte)(uVar9 >> 5) & 1) & 0x3f;
      pCVar11->field_0xf7 = 0xff;
      pCVar11->field_0xf8 = bVar4;
      pCVar11->field_0xf9 = bVar4;
      pCVar11->field_0xfa = bVar4;
      pCVar11->field_0xfb = 0xff;
    }
    pCVar10 = (CCharaPcs *)&pCVar10->field_0x4;
    pCVar11 = (CCharaPcs *)&pCVar11->field_0xc;
    iVar12 = iVar12 + 1;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  uVar8 = 0;
  dVar14 = (double)FLOAT_80330308;
  pCVar10 = charaPcs;
  dVar15 = DOUBLE_803302b0;
  dVar16 = DOUBLE_803302b8;
  do {
    pbVar6 = (byte *)__ct__6CColorFUcUcUcUc(auStack_ac,0xff,0xff,0xff,0xff);
    __ct__6CColorFv(&local_b8);
    uStack_8c = uVar8 ^ 0x80000000;
    uStack_94 = (uint)*pbVar6;
    local_90 = 0x43300000;
    local_98 = 0x43300000;
    fVar1 = (float)((double)(float)((double)CONCAT44(0x43300000,uStack_8c) - dVar16) * dVar14);
    local_80 = 0x43300000;
    local_70 = 0x43300000;
    local_60 = 0x43300000;
    iVar12 = (int)((float)((double)CONCAT44(0x43300000,uStack_94) - dVar15) * fVar1);
    local_88 = (longlong)iVar12;
    local_b8 = (undefined)iVar12;
    uStack_7c = (uint)pbVar6[1];
    iVar12 = (int)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar15) * fVar1);
    local_78 = (longlong)iVar12;
    local_b7 = (undefined)iVar12;
    uStack_6c = (uint)pbVar6[2];
    iVar12 = (int)((float)((double)CONCAT44(0x43300000,uStack_6c) - dVar15) * fVar1);
    local_68 = (longlong)iVar12;
    local_b6 = (undefined)iVar12;
    uStack_5c = (uint)pbVar6[3];
    iVar12 = (int)((float)((double)CONCAT44(0x43300000,uStack_5c) - dVar15) * fVar1);
    local_58 = (longlong)iVar12;
    local_b5 = (undefined)iVar12;
    __ct__6CColorFR6CColor(&local_a8,&local_b8);
    uVar8 = uVar8 + 1;
    pCVar10->field_0x12c = local_a8;
    pCVar10->field_0x12d = local_a7;
    pCVar10->field_0x12e = local_a6;
    pCVar10->field_0x12f = local_a5;
    pCVar10 = (CCharaPcs *)&pCVar10->field_0x4;
  } while ((int)uVar8 < 5);
  *(undefined4 *)&charaPcs->field_0xe4 = 0;
  *(undefined4 *)&charaPcs->field_0x24 = 0;
  puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_b4,0,0,0x40,0x40);
  fVar2 = FLOAT_80330324;
  fVar1 = FLOAT_80330288;
  uVar3 = *puVar7;
  local_b0._0_1_ = (undefined)((uint)uVar3 >> 0x18);
  local_b0._1_1_ = (undefined)((uint)uVar3 >> 0x10);
  charaPcs->field_0x18c = local_b0._0_1_;
  local_b0._2_1_ = (undefined)((uint)uVar3 >> 8);
  charaPcs->field_0x18d = local_b0._1_1_;
  local_b0._3_1_ = (undefined)uVar3;
  charaPcs->field_0x18e = local_b0._2_1_;
  charaPcs->field_0x18f = (undefined)local_b0;
  local_b0 = uVar3;
  puVar7 = (undefined4 *)__ct__7CVectorFfff(fVar1,fVar2,fVar1,&CStack_a4);
  fVar1 = FLOAT_80330328;
  *(undefined4 *)&charaPcs->field_0x17c = *puVar7;
  *(undefined4 *)&charaPcs->field_0x180 = puVar7[1];
  *(undefined4 *)&charaPcs->field_0x184 = puVar7[2];
  *(float *)&charaPcs->field_0x188 = fVar1;
  *(undefined4 *)&charaPcs->field_0x44 = 0x80;
  *(undefined4 *)&charaPcs->field_0x48 = 100;
  return;
}

