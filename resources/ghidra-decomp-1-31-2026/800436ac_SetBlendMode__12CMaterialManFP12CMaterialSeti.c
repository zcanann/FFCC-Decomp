// Function: SetBlendMode__12CMaterialManFP12CMaterialSeti
// Entry: 800436ac
// Size: 844 bytes

/* WARNING: Removing unreachable block (ram,0x8004377c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetBlendMode__12CMaterialManFP12CMaterialSeti
               (CMaterialMan *materialMan,CMaterialSet *materialSet,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  
  iVar2 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,param_3);
  cVar4 = *(char *)(iVar2 + 0xa1);
  if ((Game.game.m_currentSceneId == 3) && (MapMng._141704_1_ == '\0')) {
    cVar4 = '\0';
  }
  cVar3 = *(char *)(iVar2 + 0xa0);
  if (materialMan->field_0x207 != -1) {
    if (cVar3 == '\0') {
      cVar3 = '\x05';
    }
    else if (cVar3 == '\x04') {
      cVar3 = '\x01';
    }
  }
  if ((materialMan->field_0x205 != cVar3) || (materialMan->field_0x206 != cVar4)) {
    materialMan->field_0x205 = cVar3;
    materialMan->field_0x206 = cVar4;
    bVar1 = materialMan->field_0x205;
    if (bVar1 == 3) {
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (0,3,3,3,3);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,4,1,5);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
      GXSetZCompLoc(1);
      SetFog__8CGraphicFii(&Graphic,(uint)(byte)materialMan->field_0x206,1);
    }
    else if (bVar1 < 3) {
      if (bVar1 == 1) {
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (0,0,1,2,3);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
        GXSetZCompLoc(1);
        SetFog__8CGraphicFii(&Graphic,(uint)(byte)materialMan->field_0x206,0);
      }
      else if (bVar1 == 0) {
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (0,0,1,2,3);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,5,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,0xc0,0,7,0xff);
        GXSetZCompLoc(0);
        SetFog__8CGraphicFii(&Graphic,(uint)(byte)materialMan->field_0x206,0);
      }
      else {
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (0,0,1,2,3);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
        GXSetZCompLoc(1);
        SetFog__8CGraphicFii(&Graphic,(uint)(byte)materialMan->field_0x206,1);
      }
    }
    else if (bVar1 == 5) {
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (0,0,1,2,3);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0xff);
      GXSetZCompLoc(0);
      SetFog__8CGraphicFii(&Graphic,(uint)(byte)materialMan->field_0x206,0);
    }
    else if (bVar1 < 5) {
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (0,0,1,2,3);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,1,5,5);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
      GXSetZCompLoc(1);
      SetFog__8CGraphicFii(&Graphic,(uint)(byte)materialMan->field_0x206,0);
    }
  }
  return;
}

