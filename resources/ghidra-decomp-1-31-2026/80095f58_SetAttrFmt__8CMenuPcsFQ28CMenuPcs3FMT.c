// Function: SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT
// Entry: 80095f58
// Size: 496 bytes

void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs *menuPcs,int param_2)

{
  GXClearVtxDesc();
  if (param_2 == 1) {
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxAttrFmt(0,0xb,1,5,0);
    GXSetVtxAttrFmt(0,0xd,1,4,0);
    GXSetChanCtrl(0,0,0,1,0,2,2);
    GXSetChanCtrl(2,0,0,1,0,2,2);
  }
  else if (param_2 < 1) {
    if (-1 < param_2) {
      GXSetVtxDesc(9,1);
      GXSetVtxDesc(0xd,1);
      GXSetVtxAttrFmt(0,9,1,4,0);
      GXSetVtxAttrFmt(0,0xd,1,4,0);
      GXSetChanCtrl(0,0,0,0,0,2,2);
      GXSetChanCtrl(2,0,0,0,0,2,2);
    }
  }
  else if (param_2 < 3) {
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetChanCtrl(0,0,0,0,0,2,2);
    GXSetChanCtrl(2,0,0,0,0,2,2);
  }
  return;
}

