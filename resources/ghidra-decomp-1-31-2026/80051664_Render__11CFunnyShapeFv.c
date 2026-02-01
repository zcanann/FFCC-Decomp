// Function: Render__11CFunnyShapeFv
// Entry: 80051664
// Size: 772 bytes

/* WARNING: Removing unreachable block (ram,0x80051940) */
/* WARNING: Removing unreachable block (ram,0x80051938) */
/* WARNING: Removing unreachable block (ram,0x8005167c) */
/* WARNING: Removing unreachable block (ram,0x80051674) */

void Render__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  CFunnyShape *pCVar4;
  double dVar5;
  double dVar6;
  undefined4 local_50;
  undefined4 local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  
  if ((funnyShape->field_0x60d4 != '\0') && (*(int *)(funnyShape->UnkBuff2 + 0xc) != 0)) {
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxAttrFmt(0,0xb,1,5,0);
    GXSetVtxAttrFmt(0,0xd,1,4,0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,2,3);
    GXLoadTexObj(*(undefined4 *)&funnyShape->field_0x6014,0);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,1,0,2,1);
    GXSetChanCtrl(2,0,0,1,0,0,2);
    GXSetNumTevStages(1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,8,10,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,4,5,7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,1,1,0)
    ;
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0);
    GXSetZMode(1,3,0);
    uVar1 = DAT_8032fd60;
    local_50 = DAT_8032fd60;
    GXSetChanAmbColor(0,&local_50);
    local_4c = uVar1;
    GXSetChanMatColor(0,&local_4c);
    if ((*(uint *)funnyShape->UnkBuff3 & 0x80) == 0) {
      iVar3 = 1;
    }
    else {
      iVar3 = (int)*(short *)(funnyShape->UnkBuff3 + 0x28);
    }
    dVar5 = (double)FLOAT_8032fd9c;
    dVar6 = (double)FLOAT_8032fda0;
    pCVar4 = funnyShape;
    for (iVar2 = 0; iVar2 < iVar3; iVar2 = iVar2 + 1) {
      local_48 = (float)(dVar5 + (double)*(float *)(pCVar4->m_maybeTexture + 8));
      local_44 = (float)(dVar6 + (double)*(float *)(pCVar4->m_maybeTexture + 0xc));
      local_40 = local_48;
      local_3c = local_44;
      RenderShape__11CFunnyShapeFP16FS_tagOAN3_SHAPE5Vec2df
                ((double)*(float *)(pCVar4->m_maybeTexture + 0x28),funnyShape,
                 *(int *)(funnyShape->UnkBuff2 + 0xc) +
                 (int)*(short *)(*(int *)(funnyShape->UnkBuff2 + 0xc) + 0x10 +
                                *(short *)(pCVar4->m_maybeTexture + 0x14) * 8),&local_48);
      pCVar4 = (CFunnyShape *)(pCVar4->m_maybeTexture + 0x30);
    }
  }
  return;
}

