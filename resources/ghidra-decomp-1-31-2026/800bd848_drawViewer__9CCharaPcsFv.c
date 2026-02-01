// Function: drawViewer__9CCharaPcsFv
// Entry: 800bd848
// Size: 1680 bytes

/* WARNING: Removing unreachable block (ram,0x800bdebc) */
/* WARNING: Removing unreachable block (ram,0x800bdeb4) */
/* WARNING: Removing unreachable block (ram,0x800bdeac) */
/* WARNING: Removing unreachable block (ram,0x800bdea4) */
/* WARNING: Removing unreachable block (ram,0x800bde9c) */
/* WARNING: Removing unreachable block (ram,0x800bd878) */
/* WARNING: Removing unreachable block (ram,0x800bd870) */
/* WARNING: Removing unreachable block (ram,0x800bd868) */
/* WARNING: Removing unreachable block (ram,0x800bd860) */
/* WARNING: Removing unreachable block (ram,0x800bd858) */

void drawViewer__9CCharaPcsFv(int param_1)

{
  float fVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined uVar5;
  uint uVar4;
  int iVar6;
  CTexture *texture;
  uint uVar7;
  int iVar8;
  int iVar9;
  void *pvVar10;
  uint uVar11;
  double dVar12;
  undefined8 uVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  Mtx MStack_1bc;
  undefined auStack_188 [48];
  Mtx MStack_158;
  Mtx MStack_128;
  Mtx MStack_f8;
  Mat4x4 MStack_c8;
  void *local_88;
  uint uStack_84;
  float local_80;
  void *pvStack_7c;
  
  if ((*(int *)(param_1 + 0x2b8) != 0) &&
     (iVar6 = GetSize__21CPtrArray<P8CTexture>Fv((CPtrArray *)(*(int *)(param_1 + 0x2b8) + 8)),
     iVar6 != 0)) {
    C_MTXOrtho(FLOAT_80330be8,FLOAT_80330bec,FLOAT_80330be8,FLOAT_80330bf0,FLOAT_80330be8,
               FLOAT_80330bf4,(Mtx *)&MStack_c8);
    GXSetProjection(&MStack_c8,1);
    PSMTXIdentity(&MStack_128);
    GXLoadPosMtxImm(&MStack_128,0);
    GXSetCurrentMtx(0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,0,0);
    GXSetZMode(0,7,0);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
    PSMTXIdentity(&MStack_128);
    GXLoadPosMtxImm(&MStack_128,0);
    GXSetCullMode(0);
    texture = (CTexture *)__vc__21CPtrArray<P8CTexture>FUl(*(int *)(param_1 + 0x2b8) + 8,0);
    SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,texture);
    uVar11 = texture->field94_0x64;
    pvVar10 = (void *)texture->field95_0x68;
    local_88 = (void *)0x43300000;
    local_80 = 176.0;
    uStack_84 = uVar11;
    pvStack_7c = pvVar10;
    PSMTXScale(FLOAT_80330bf8 / (float)((double)CONCAT44(0x43300000,uVar11) - DOUBLE_80330c10),
               FLOAT_80330bf8 / (float)((double)CONCAT44(0x43300000,pvVar10) - DOUBLE_80330c10),
               FLOAT_80330bf8,&MStack_f8);
    GXLoadTexMtxImm(&MStack_f8,0x1e,1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,3,0);
    GXSetVtxAttrFmt(0,0xd,1,3,1);
    GXBegin(0x80,0,4);
    DAT_cc008000._0_2_ = 0;
    uVar2 = (undefined2)(uVar11 << 1);
    DAT_cc008000._0_2_ = 0;
    uVar3 = (undefined2)((int)pvVar10 << 1);
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = (short)uVar11;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = uVar2;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = (short)uVar11;
    DAT_cc008000._0_2_ = (short)pvVar10;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = uVar2;
    DAT_cc008000._0_2_ = uVar3;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = (short)pvVar10;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = uVar3;
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_c8);
    GXSetProjection(&MStack_c8,0);
  }
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_158);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_c8);
  GXSetProjection(&MStack_c8,0);
  if (*(int *)(param_1 + 0x6f8) != 0) {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(1,3,1);
    GXSetCullMode(1);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    local_1cc = 0x80808020;
    GXLoadPosMtxImm(&MStack_158,0);
    dVar14 = (double)FLOAT_80330bfc;
    uVar11 = 0xfffffff6;
    dVar15 = (double)FLOAT_80330be8;
    dVar16 = (double)FLOAT_80330c00;
    dVar17 = (double)FLOAT_80330bf4;
    dVar12 = DOUBLE_80330be0;
    do {
      uVar5 = 0x20;
      if (uVar11 == 0) {
        uVar5 = 0x60;
      }
      local_1cc = CONCAT31(local_1cc._0_3_,uVar5);
      local_1d0 = local_1cc;
      GXSetChanMatColor(4,&local_1d0);
      GXBegin(0xa8,0,4);
      pvStack_7c = (void *)(uVar11 ^ 0x80000000);
      uVar11 = uVar11 + 1;
      local_80 = 176.0;
      fVar1 = (float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,pvStack_7c) - dVar12));
      DAT_cc008000 = fVar1;
      DAT_cc008000 = (float)dVar15;
      DAT_cc008000 = (float)dVar16;
      DAT_cc008000 = fVar1;
      DAT_cc008000 = (float)dVar15;
      DAT_cc008000 = (float)dVar17;
      DAT_cc008000 = (float)dVar17;
      DAT_cc008000 = (float)dVar15;
      DAT_cc008000 = fVar1;
      DAT_cc008000 = (float)dVar16;
      DAT_cc008000 = (float)dVar15;
      DAT_cc008000 = fVar1;
    } while ((int)uVar11 < 0xb);
  }
  uVar11 = 0;
  iVar6 = param_1;
  do {
    if (*(int *)(iVar6 + 400) != 0) {
      if (*(int *)(*(int *)(iVar6 + 400) + 0xb0) == 0) {
        Printf__8CGraphicFPce(&Graphic,s_no_texture____801da7e8);
      }
      else {
        DumpMapFile__7CSystemFPv((CSystem *)auStack_188);
        Reset__10CStopWatchFv(auStack_188);
        Start__10CStopWatchFv(auStack_188);
        SetFog__8CGraphicFii(&Graphic,0,0);
        local_1d4 = *(undefined4 *)(param_1 + 0xe8);
        SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_1d4);
        SetNumDiffuse__9CLightPcsFUl(&LightPcs,3);
        uVar7 = 0;
        iVar8 = param_1;
        iVar9 = param_1;
        do {
          local_1d8 = *(undefined4 *)(iVar9 + 0xf0);
          uVar4 = countLeadingZeros(2 - uVar7);
          SetDiffuse__9CLightPcsFUl8_GXColorP3Veci
                    (&LightPcs,uVar7,&local_1d8,iVar8 + 0x108,uVar4 >> 5 & 0xff);
          uVar7 = uVar7 + 1;
          iVar8 = iVar8 + 0xc;
          iVar9 = iVar9 + 4;
        } while (uVar7 < 3);
        PSMTXCopy((Mtx *)(*(int *)(iVar6 + 400) + 8),&MStack_1bc);
        local_1c8 = MStack_1bc.value[0][3];
        local_1c4 = MStack_1bc.value[1][3];
        local_1c0 = MStack_1bc.value[2][3];
        SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,&local_1c8,0xffffffff);
        Draw__Q26CChara6CModelFPA4_fii(*(CModel **)(iVar6 + 400),&MStack_158,0,0);
        DrawFur__Q26CChara6CModelFPA4_fi(*(CModel **)(iVar6 + 400),&MStack_158,0);
        Stop__10CStopWatchFv(auStack_188);
        dVar12 = (double)Get__10CStopWatchFv(auStack_188);
        Start__10CStopWatchFv(auStack_188);
        _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_chara_viewer_cpp_801da7f8,0x2a7);
        Stop__10CStopWatchFv(auStack_188);
        if (uVar11 == 0) {
          dVar14 = (double)Get__10CStopWatchFv(auStack_188);
          dVar14 = (double)(float)(dVar14 - dVar12);
          uVar13 = Get__10CStopWatchFv(auStack_188);
          Printf__8CGraphicFPce
                    (uVar13,dVar12,dVar14,&Graphic,s_GPU____f_5___C_____5f___G_____5f_801da80c);
        }
        __ct__10CStopWatchFPc(auStack_188,0xffffffff);
      }
    }
    uVar11 = uVar11 + 1;
    iVar6 = iVar6 + 4;
  } while (uVar11 < 2);
  return;
}

