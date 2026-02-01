// Function: Draw__5CWindFv
// Entry: 800d9b2c
// Size: 564 bytes

void Draw__5CWindFv(byte *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined auStack_68 [4];
  undefined auStack_64 [4];
  CVector CStack_60;
  CVector CStack_54;
  Mtx MStack_48;
  longlong local_18;
  
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_48);
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
  if ((CFlat._4764_4_ & 0x800000) != 0) {
    iVar4 = 0;
    do {
      if ((int)((uint)*param_1 << 0x18) < 0) {
        if (*(int *)(param_1 + 0x1c) == 1) {
          uVar2 = __ct__6CColorFUcUcUcUc(auStack_64,0xff,0xff,0,0xff);
          uVar3 = __ct__7CVectorFfff(*(float *)(param_1 + 4),FLOAT_80330ef0,*(float *)(param_1 + 8),
                                     &CStack_54);
          DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                    ((double)*(float *)(param_1 + 0x30),&Graphic,&MStack_48,uVar3,uVar2);
        }
        else {
          iVar1 = (int)(FLOAT_80330f1c * (FLOAT_80330ef8 - *(float *)(param_1 + 0x38)));
          local_18 = (longlong)iVar1;
          uVar2 = __ct__6CColorFUcUcUcUc(auStack_68,0xff,0xff,0x80,iVar1);
          uVar3 = __ct__7CVectorFfff(*(float *)(param_1 + 4),FLOAT_80330ef0,*(float *)(param_1 + 8),
                                     &CStack_60);
          DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                    ((double)*(float *)(param_1 + 0x30),&Graphic,&MStack_48,uVar3,uVar2);
        }
      }
      iVar4 = iVar4 + 1;
      param_1 = param_1 + 100;
    } while (iVar4 < 0x20);
  }
  return;
}

