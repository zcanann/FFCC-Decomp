// Function: changeVtxFmt__11CDbgMenuPcsFi
// Entry: 8012c7ac
// Size: 300 bytes

void changeVtxFmt__11CDbgMenuPcsFi(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x2a68) != param_2) {
    if (param_2 == 1) {
      GXClearVtxDesc();
      GXSetVtxDesc(9,1);
      GXSetVtxDesc(0xb,1);
      GXSetVtxAttrFmt(1,9,1,4,0);
      GXSetVtxAttrFmt(1,0xb,1,5,0);
      GXSetChanCtrl(4,0,0,1,0,2,1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    }
    else if ((param_2 < 1) && (-1 < param_2)) {
      GXSetChanCtrl(4,0,0,0,0,2,1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
    }
    *(int *)(param_1 + 0x2a68) = param_2;
  }
  return;
}

