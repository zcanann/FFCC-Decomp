// Function: pppSetBlendMode__FUc
// Entry: 80054440
// Size: 316 bytes

/* WARNING: Removing unreachable block (ram,0x80054480) */

void pppSetBlendMode__FUc(byte blendMode)

{
  if ((blendMode != 0xff) && (DAT_8032ed85 != blendMode)) {
    DAT_8032ed85 = blendMode;
    if (blendMode == 2) {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,4,1,5);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
      GXSetZCompLoc(1);
    }
    else if (blendMode < 2) {
      if (blendMode == 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
        GXSetZCompLoc(1);
      }
      else {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
        GXSetZCompLoc(1);
      }
    }
    else if (blendMode < 4) {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,6,5,5);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
      GXSetZCompLoc(1);
    }
  }
  return;
}

