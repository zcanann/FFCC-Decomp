// Function: pppRenderYmDeformationShp
// Entry: 8008eec8
// Size: 2904 bytes

/* WARNING: Removing unreachable block (ram,0x8008fa04) */
/* WARNING: Removing unreachable block (ram,0x8008f9fc) */
/* WARNING: Removing unreachable block (ram,0x8008eee0) */
/* WARNING: Removing unreachable block (ram,0x8008eed8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmDeformationShp(pppYmDeformationShp *pppYmDeformationShp,int param_2,int param_3)

{
  float fVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  ushort uVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  ushort uVar10;
  double dVar11;
  double dVar12;
  undefined4 local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_104;
  float local_100;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  Mtx MStack_b4;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  local_150 = 0;
  puVar7 = &pppYmDeformationShp->field_0x80 + *(int *)(*(int *)(param_3 + 0xc) + 8);
  if (*(int *)(param_2 + 4) != 0xffff) {
    iVar5 = *(int *)(*(int *)(param_3 + 0xc) + 4);
    iVar4 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      (pppEnvStPtr->m_mapMeshPtr[*(int *)(param_2 + 4)],
                       pppEnvStPtr->m_materialSetPtr,&local_150);
    PSMTXIdentity(&MStack_b4);
    pppSetBlendMode__FUc(1);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (*(float *)(param_2 + 0x2c),(pppCVector *)(&pppYmDeformationShp->field_0x88 + iVar5),
               (pppFMATRIX *)&pppYmDeformationShp->field_0x40,*(byte *)(param_2 + 0x31),0,0,0,1,1,0)
    ;
    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,1,7,0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
    SetVtxFmt_POS_TEX0_TEX1__5CUtilFv(&DAT_8032ec70);
    GXLoadTexObj(iVar4 + 0x28,1);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(0,1,1);
    GXSetTevIndWarp(0,0,1,0,1);
    if ((*(short *)(puVar7 + 0xc) == 0) || (*(short *)(puVar7 + 0xc) == 0x168)) {
      *(undefined2 *)(puVar7 + 0xc) = 1;
    }
    local_80 = 0x43300000;
    uStack_7c = (int)*(short *)(puVar7 + 0xc) ^ 0x80000000;
    PSMTXRotRad(FLOAT_803305f0 * (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600),
                &local_114,0x7a);
    local_13c = *(float *)(puVar7 + 0x10);
    local_14c = local_114 * local_13c;
    local_148 = local_110 * local_13c;
    local_140 = local_104 * local_13c;
    local_13c = local_100 * local_13c;
    local_144 = FLOAT_803305f4;
    local_138 = FLOAT_803305f4;
    GXSetIndTexMtx(1,&local_14c,1);
    if (*(char *)(param_2 + 0x26) == '\0') {
      uStack_7c = (uint)*(byte *)(param_2 + 8);
      local_80 = 0x43300000;
      fVar1 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330608);
      if (*(char *)(param_2 + 0x28) == '\0') {
        local_e4 = -fVar1;
        local_dc = FLOAT_803305f4;
        local_d0 = FLOAT_803305f4;
        local_c4 = FLOAT_803305f4;
        local_b8 = FLOAT_803305f4;
        local_e0 = fVar1;
        local_d8 = fVar1;
        local_d4 = fVar1;
        local_cc = fVar1;
        local_c8 = local_e4;
        local_c0 = local_e4;
        local_bc = local_e4;
      }
      else if (*(char *)(param_2 + 0x28) == '\x01') {
        local_e4 = -fVar1;
        local_e0 = FLOAT_803305f4;
        local_d4 = FLOAT_803305f4;
        local_c8 = FLOAT_803305f4;
        local_bc = FLOAT_803305f4;
        local_dc = local_e4;
        local_d8 = fVar1;
        local_d0 = local_e4;
        local_cc = fVar1;
        local_c4 = fVar1;
        local_c0 = local_e4;
        local_b8 = fVar1;
      }
      local_134 = FLOAT_803305f4;
      local_130 = FLOAT_803305f4;
      local_12c = FLOAT_803305f8;
      local_128 = FLOAT_803305f4;
      local_124 = FLOAT_803305f8;
      local_120 = FLOAT_803305f8;
      local_11c = FLOAT_803305f4;
      local_118 = FLOAT_803305f8;
      RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
                ((_pppPObject *)pppYmDeformationShp,puVar7,&local_e4,&local_134);
    }
    else {
      bVar2 = *(byte *)(param_2 + 8);
      uVar9 = (uint)bVar2;
      bVar3 = *(byte *)(param_2 + 0x27);
      uStack_7c = uVar9 << 1 ^ 0x80000000;
      uVar8 = (uint)(short)(ushort)bVar3;
      uStack_74 = uVar9 - uVar8 ^ 0x80000000;
      local_130 = (FLOAT_803305f8 /
                  (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600)) *
                  (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
      dVar11 = (double)local_130;
      if (*(char *)(param_2 + 0x28) == '\0') {
        uStack_7c = -uVar8 ^ 0x80000000;
        uStack_54 = uVar8 ^ 0x80000000;
        uStack_74 = -uVar9 ^ 0x80000000;
        local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_e0 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_70 = 0x43300000;
        local_d8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_68 = 0x43300000;
        local_d4 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_60 = 0x43300000;
        local_cc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_58 = 0x43300000;
        local_c8 = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330600);
        local_50 = 0x43300000;
        local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_48 = 0x43300000;
        local_bc = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330600);
        local_dc = FLOAT_803305f4;
        local_d0 = FLOAT_803305f4;
        local_c4 = FLOAT_803305f4;
        local_b8 = FLOAT_803305f4;
        uStack_6c = uStack_7c;
        uStack_64 = uStack_7c;
        uStack_5c = uStack_7c;
        uStack_4c = uStack_74;
        uStack_44 = uStack_54;
      }
      else if (*(char *)(param_2 + 0x28) == '\x01') {
        uStack_64 = -uVar8 ^ 0x80000000;
        uStack_7c = uVar8 ^ 0x80000000;
        uStack_74 = -uVar9 ^ 0x80000000;
        local_48 = 0x43300000;
        local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_50 = 0x43300000;
        local_dc = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
        local_58 = 0x43300000;
        local_d8 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
        local_60 = 0x43300000;
        local_d0 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
        local_68 = 0x43300000;
        local_cc = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
        local_70 = 0x43300000;
        local_c4 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_b8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_e0 = FLOAT_803305f4;
        local_d4 = FLOAT_803305f4;
        local_c8 = FLOAT_803305f4;
        local_bc = FLOAT_803305f4;
        uStack_6c = uStack_7c;
        uStack_5c = uStack_64;
        uStack_54 = uStack_64;
        uStack_4c = uStack_64;
        uStack_44 = uStack_74;
      }
      local_78 = 0x43300000;
      local_80 = 0x43300000;
      local_120 = (float)((double)FLOAT_803305f8 - dVar11);
      dVar12 = (double)local_120;
      local_134 = FLOAT_803305f4;
      local_11c = FLOAT_803305f4;
      local_12c = local_130;
      local_128 = local_130;
      local_124 = local_130;
      local_118 = local_120;
      RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
                ((_pppPObject *)pppYmDeformationShp,puVar7,&local_e4,&local_134);
      uVar6 = (ushort)bVar3;
      uVar10 = (ushort)bVar2;
      if (*(char *)(param_2 + 0x28) == '\0') {
        uStack_7c = (int)(short)uVar6 ^ 0x80000000;
        uStack_74 = (int)(short)uVar10 ^ 0x80000000;
        uStack_5c = -uVar8 ^ 0x80000000;
        local_48 = 0x43300000;
        local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_50 = 0x43300000;
        local_e0 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
        local_58 = 0x43300000;
        local_d8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_60 = 0x43300000;
        local_d4 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
        local_68 = 0x43300000;
        local_cc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_70 = 0x43300000;
        local_c8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_78 = 0x43300000;
        local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_80 = 0x43300000;
        local_bc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_dc = FLOAT_803305f4;
        local_d0 = FLOAT_803305f4;
        local_c4 = FLOAT_803305f4;
        local_b8 = FLOAT_803305f4;
        uStack_6c = uStack_7c;
        uStack_64 = uStack_7c;
        uStack_54 = uStack_7c;
        uStack_4c = uStack_5c;
        uStack_44 = uStack_74;
      }
      else if (*(char *)(param_2 + 0x28) == '\x01') {
        uStack_7c = (int)(short)(ushort)bVar3 ^ 0x80000000;
        uStack_74 = (int)(short)uVar10 ^ 0x80000000;
        uStack_5c = -uVar8 ^ 0x80000000;
        local_48 = 0x43300000;
        local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_50 = 0x43300000;
        local_dc = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
        local_58 = 0x43300000;
        local_d8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_60 = 0x43300000;
        local_d0 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
        local_68 = 0x43300000;
        local_cc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_70 = 0x43300000;
        local_c4 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_78 = 0x43300000;
        local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
        local_80 = 0x43300000;
        local_b8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
        local_e0 = FLOAT_803305f4;
        local_d4 = FLOAT_803305f4;
        local_c8 = FLOAT_803305f4;
        local_bc = FLOAT_803305f4;
        uStack_6c = uStack_7c;
        uStack_64 = uStack_7c;
        uStack_54 = uStack_7c;
        uStack_4c = uStack_5c;
        uStack_44 = uStack_74;
      }
      local_130 = (float)dVar11;
      local_134 = FLOAT_803305f8;
      local_12c = (float)dVar12;
      local_128 = (float)dVar11;
      local_124 = (float)dVar12;
      local_120 = (float)dVar12;
      local_11c = FLOAT_803305f8;
      local_118 = (float)dVar12;
      RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
                ((_pppPObject *)pppYmDeformationShp,puVar7,&local_e4,&local_134);
      if (*(char *)(param_2 + 0x26) == '\x01') {
        if (*(char *)(param_2 + 0x28) == '\0') {
          uStack_74 = -uVar9 ^ 0x80000000;
          uStack_64 = (int)(short)uVar10 ^ 0x80000000;
          uStack_7c = -uVar8 ^ 0x80000000;
          local_48 = 0x43300000;
          local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_50 = 0x43300000;
          local_e0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_58 = 0x43300000;
          local_d8 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
          local_60 = 0x43300000;
          local_d4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_68 = 0x43300000;
          local_cc = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
          local_70 = 0x43300000;
          local_c8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_78 = 0x43300000;
          local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_80 = 0x43300000;
          local_bc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_dc = FLOAT_803305f4;
          local_d0 = FLOAT_803305f4;
          local_c4 = FLOAT_803305f4;
          local_b8 = FLOAT_803305f4;
          uStack_6c = uStack_7c;
          uStack_5c = uStack_74;
          uStack_54 = uStack_64;
          uStack_4c = uStack_74;
          uStack_44 = uStack_74;
        }
        else if (*(char *)(param_2 + 0x28) == '\x01') {
          uStack_74 = -uVar9 ^ 0x80000000;
          uStack_64 = (int)(short)uVar10 ^ 0x80000000;
          uStack_7c = -uVar8 ^ 0x80000000;
          local_48 = 0x43300000;
          local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_50 = 0x43300000;
          local_dc = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_58 = 0x43300000;
          local_d8 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
          local_60 = 0x43300000;
          local_d0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_68 = 0x43300000;
          local_cc = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330600);
          local_70 = 0x43300000;
          local_c4 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_78 = 0x43300000;
          local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_80 = 0x43300000;
          local_b8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_e0 = FLOAT_803305f4;
          local_d4 = FLOAT_803305f4;
          local_c8 = FLOAT_803305f4;
          local_bc = FLOAT_803305f4;
          uStack_6c = uStack_7c;
          uStack_5c = uStack_74;
          uStack_54 = uStack_64;
          uStack_4c = uStack_74;
          uStack_44 = uStack_74;
        }
        local_134 = FLOAT_803305f4;
        local_130 = FLOAT_803305f4;
        local_12c = FLOAT_803305f8;
        local_128 = FLOAT_803305f4;
        local_124 = FLOAT_803305f8;
        local_120 = (float)dVar11;
        local_11c = FLOAT_803305f4;
        local_118 = (float)dVar11;
        RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
                  ((_pppPObject *)pppYmDeformationShp,puVar7,&local_e4,&local_134);
        if (*(char *)(param_2 + 0x28) == '\0') {
          uStack_7c = (int)(short)uVar10 ^ 0x80000000;
          uStack_74 = -uVar9 ^ 0x80000000;
          uStack_5c = (int)(short)uVar6 ^ 0x80000000;
          local_48 = 0x43300000;
          local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_50 = 0x43300000;
          local_e0 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
          local_58 = 0x43300000;
          local_d8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_60 = 0x43300000;
          local_d4 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
          local_68 = 0x43300000;
          local_cc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_70 = 0x43300000;
          local_c8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_78 = 0x43300000;
          local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_80 = 0x43300000;
          local_bc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_dc = FLOAT_803305f4;
          local_d0 = FLOAT_803305f4;
          local_c4 = FLOAT_803305f4;
          local_b8 = FLOAT_803305f4;
          uStack_6c = uStack_7c;
          uStack_64 = uStack_7c;
          uStack_54 = uStack_7c;
          uStack_4c = uStack_5c;
          uStack_44 = uStack_74;
        }
        else if (*(char *)(param_2 + 0x28) == '\x01') {
          uStack_7c = (int)(short)uVar10 ^ 0x80000000;
          uStack_74 = -uVar9 ^ 0x80000000;
          uStack_5c = (int)(short)uVar6 ^ 0x80000000;
          local_48 = 0x43300000;
          local_e4 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_50 = 0x43300000;
          local_dc = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
          local_58 = 0x43300000;
          local_d8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_60 = 0x43300000;
          local_d0 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330600);
          local_68 = 0x43300000;
          local_cc = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_70 = 0x43300000;
          local_c4 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_78 = 0x43300000;
          local_c0 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80330600);
          local_80 = 0x43300000;
          local_b8 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330600);
          local_e0 = FLOAT_803305f4;
          local_d4 = FLOAT_803305f4;
          local_c8 = FLOAT_803305f4;
          local_bc = FLOAT_803305f4;
          uStack_6c = uStack_7c;
          uStack_64 = uStack_7c;
          uStack_54 = uStack_7c;
          uStack_4c = uStack_5c;
          uStack_44 = uStack_74;
        }
        local_130 = (float)dVar12;
        local_134 = FLOAT_803305f4;
        local_12c = FLOAT_803305f8;
        local_128 = (float)dVar12;
        local_124 = FLOAT_803305f8;
        local_120 = FLOAT_803305f8;
        local_11c = FLOAT_803305f4;
        local_118 = FLOAT_803305f8;
        RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
                  ((_pppPObject *)pppYmDeformationShp,puVar7,&local_e4,&local_134);
      }
    }
    DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1,0);
  }
  return;
}

