// Function: Flip__8CGraphicFv
// Entry: 800191d8
// Size: 424 bytes

void Flip__8CGraphicFv(CGraphic *graphic)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (*(int *)&graphic->field_0xc != 0) {
    if (*(int *)&graphic->field_0x71f0 != 0) {
      VISetBlack(0);
      *(undefined4 *)&graphic->field_0x71f0 = 0;
    }
    if (System.m_scenegraphStepMode != 1) {
      iVar2 = VIGetRetraceCount();
      if ((uint)(iVar2 - *(int *)&graphic->field_0x71f4) < 2) {
        *(undefined4 *)&graphic->field_0x7350 = 0;
        while (iVar2 = VIGetRetraceCount(), (uint)(iVar2 - *(int *)&graphic->field_0x71f4) < 2) {
          VIWaitForRetrace();
        }
      }
      else {
        *(undefined4 *)&graphic->field_0x7350 = 1;
      }
    }
    GXSetZMode(1,3,1);
    GXCopyDisp(*(undefined4 *)&graphic->field_0x71e4,1);
    *(char **)&graphic->field_0x7368 = s_graphic_cpp_801d6348;
    *(undefined4 *)&graphic->field_0x736c = 0x26d;
    *(undefined4 *)&graphic->field_0x7364 = 1;
    GXSetDrawDone();
    GXWaitDrawDone();
    *(undefined4 *)&graphic->field_0x7364 = 0;
    *(int *)&graphic->field_0x7370 = *(int *)&graphic->field_0x7370 + 1;
    VIFlush();
    *(int *)&graphic->field_0x734c = 1 - *(int *)&graphic->field_0x734c;
    GXInitFifoBase(&graphic->field_0x724c + *(int *)&graphic->field_0x734c * 0x80,
                   *(undefined4 *)&graphic->field_0x10,0x60000);
    GXInitFifoLimits(&graphic->field_0x724c + *(int *)&graphic->field_0x734c * 0x80,0x5c000,0x50000)
    ;
    GXSetCPUFifo(&graphic->field_0x724c + *(int *)&graphic->field_0x734c * 0x80);
    GXSetGPFifo(&graphic->field_0x724c + *(int *)&graphic->field_0x734c * 0x80);
  }
  uVar3 = VIGetRetraceCount();
  *(undefined4 *)&graphic->field_0x71f4 = uVar3;
  if (System.m_scenegraphStepMode == 1) {
    uVar1 = countLeadingZeros(System.m_frameCounter & 3);
    uVar1 = uVar1 >> 5 & 0xff;
  }
  else {
    uVar1 = 1;
  }
  *(uint *)&graphic->field_0xc = uVar1;
  return;
}

