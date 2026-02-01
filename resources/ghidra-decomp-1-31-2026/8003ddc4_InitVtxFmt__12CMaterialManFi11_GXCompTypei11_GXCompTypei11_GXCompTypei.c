// Function: InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
// Entry: 8003ddc4
// Size: 660 bytes

void InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
               (int param_1,uint param_2,undefined4 param_3,undefined param_4,undefined4 param_5,
               undefined param_6,undefined4 param_7,undefined param_8)

{
  if ((param_2 & 1) != 0) {
    GXSetVtxAttrFmt(0,9,1,param_3,param_4);
    GXSetVtxAttrFmt(0,10,0,param_5,param_6);
    GXSetVtxAttrFmt(0,0xb,1,5,0);
    GXSetVtxAttrFmt(0,0xd,1,param_7,param_8);
  }
  if ((param_2 & 2) != 0) {
    GXSetVtxAttrFmt(1,9,1,param_3,param_4);
    GXSetVtxAttrFmt(1,0x19,1,param_5,param_6);
    GXSetVtxAttrFmt(1,0xb,1,5,0);
    GXSetVtxAttrFmt(1,0xd,1,param_7,param_8);
  }
  if ((param_2 & 4) != 0) {
    GXSetVtxAttrFmt(2,9,1,param_3,param_4);
    GXSetVtxAttrFmt(2,10,0,param_5,param_6);
    GXSetVtxAttrFmt(2,0xb,1,5,0);
    GXSetVtxAttrFmt(2,0xd,1,param_7,param_8);
    GXSetVtxAttrFmt(2,0xe,1,param_7,param_8);
  }
  if ((param_2 & 8) != 0) {
    GXSetVtxAttrFmt(3,9,1,param_3,param_4);
    GXSetVtxAttrFmt(3,10,0,param_5,param_6);
    GXSetVtxAttrFmt(3,0xb,1,5,0);
  }
  if ((param_2 & 0x10) != 0) {
    GXSetVtxAttrFmt(4,9,1,param_3,param_4);
    GXSetVtxAttrFmt(4,0xb,1,5,0);
    GXSetVtxAttrFmt(4,0xd,1,param_7,param_8);
  }
  if ((param_2 & 0x20) != 0) {
    GXSetVtxAttrFmt(5,9,1,param_3,param_4);
  }
  if ((param_2 & 0x40) != 0) {
    GXSetVtxAttrFmt(6,9,1,param_3,param_4);
    GXSetVtxAttrFmt(6,0xb,1,5,0);
  }
  *(undefined4 *)(param_1 + 0x44) = 0xffffffff;
  return;
}

