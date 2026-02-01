// Function: GXBegin
// Entry: 801a24c4
// Size: 240 bytes

void GXBegin(byte param_1,byte param_2,undefined2 param_3)

{
  if (DAT_80333828[0x13d] != 0) {
    if ((DAT_80333828[0x13d] & 1U) != 0) {
      __GXSetSUTexRegs();
    }
    if ((DAT_80333828[0x13d] & 2U) != 0) {
      __GXUpdateBPMask();
    }
    if ((DAT_80333828[0x13d] & 4U) != 0) {
      __GXSetGenMode();
    }
    if ((DAT_80333828[0x13d] & 8U) != 0) {
      __GXSetVCD();
    }
    if ((DAT_80333828[0x13d] & 0x10U) != 0) {
      __GXSetVAT();
    }
    if ((DAT_80333828[0x13d] & 0x18U) != 0) {
      __GXCalculateVLim();
    }
    DAT_80333828[0x13d] = 0;
  }
  if (*DAT_80333828 == 0) {
    __GXSendFlushPrim();
  }
  DAT_cc008000._0_1_ = param_2 | param_1;
  DAT_cc008000._0_2_ = param_3;
  return;
}

