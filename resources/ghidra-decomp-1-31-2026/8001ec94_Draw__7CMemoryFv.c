// Function: Draw__7CMemoryFv
// Entry: 8001ec94
// Size: 764 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Draw__7CMemoryFv(int param_1)

{
  int iVar1;
  CStage *stage;
  int iVar2;
  int iVar3;
  int iVar4;
  CStage *pCVar5;
  int iVar6;
  int iVar7;
  Mtx MStack_198;
  Mtx MStack_168;
  undefined auStack_128 [260];
  
  if (*(int *)(param_1 + 0x7798) != 0) {
    C_MTXOrtho(FLOAT_8032f7dc,FLOAT_8032f7fc,FLOAT_8032f7dc,FLOAT_8032f800,FLOAT_8032f7dc,
               FLOAT_8032f804,&MStack_168);
    GXSetProjection(&MStack_168,1);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(0,3,0);
    GXSetCullMode(0);
    GXSetNumTevStages(1);
    GXSetTevDirect(0);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,1,0,2,1);
    GXSetChanCtrl(2,0,0,1,0,2,2);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxAttrFmt(0,0xb,1,5,0);
    PSMTXIdentity(&MStack_198);
    GXLoadPosMtxImm(&MStack_198,0);
    GXLoadTexMtxImm(&MStack_198,0x1e,1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    iVar7 = 0;
    do {
      if (iVar7 == 1) {
        InitDebugString__8CGraphicFv(&Graphic);
      }
      pCVar5 = (CStage *)(param_1 + 4);
      iVar6 = 0x20;
      iVar4 = 0;
      iVar3 = 0;
      iVar2 = 0;
      do {
        if (((iVar2 != 1) || (iVar1 = OSGetConsoleSimulatedMemSize(), iVar1 == 0x3000000)) &&
           (iVar2 != 2)) {
          for (stage = *(CStage **)&pCVar5->field_0x4; stage != pCVar5;
              stage = *(CStage **)&stage->field_0x4) {
            if (iVar7 == 0) {
              drawHeapBar__Q27CMemory6CStageFi(stage,iVar6);
            }
            else {
              drawHeapTitle__Q27CMemory6CStageFi(stage,iVar6);
              if (iVar2 == 0) {
                iVar4 = iVar4 + ((uint)(*(int *)&stage->field_0xc - *(int *)&stage->field_0x8) >> 10
                                );
                iVar3 = iVar3 + ((uint)(*(int *)(*(int *)&stage->field_0x4 + 8) -
                                       *(int *)&stage->field_0xc) >> 10);
              }
            }
            iVar6 = iVar6 + 0xc;
          }
        }
        iVar2 = iVar2 + 1;
        pCVar5 = pCVar5 + 0x22;
      } while (iVar2 < 3);
      if (iVar7 == 1) {
        sprintf(auStack_128,s_USE__d_UNUSE__d_801d6bdc,iVar4,iVar3);
        DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,0x10,(short)iVar6,auStack_128,8);
        sprintf(auStack_128,s_AMEM_ANIM__d_801d6bec,
                ((int)Chara._8308_4_ >> 10) +
                (uint)((int)Chara._8308_4_ < 0 && (Chara._8308_4_ & 0x3ff) != 0));
        DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,0x10,(short)iVar6 + 0xc,auStack_128,8);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 2);
  }
  return;
}

