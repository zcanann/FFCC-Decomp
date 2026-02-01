// Function: __AXNextFrame
// Entry: 80191fc0
// Size: 1708 bytes

void __AXNextFrame(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  int local_18 [3];
  
  puVar2 = DAT_8032f22c;
  DAT_8032f230 = 0x1a9;
  local_18[0] = __AXGetStudio();
  *DAT_8032f22c = 0;
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = (short)local_18[0];
  DAT_8032f22c = DAT_8032f22c + 1;
  DAT_8032f230 = DAT_8032f230 + 0x2e44;
  uVar3 = (undefined2)param_1;
  uVar1 = (undefined2)((uint)param_1 >> 0x10);
  if (DAT_8032f238 == 1) {
    *DAT_8032f22c = 0x11;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = uVar1;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = uVar3;
    DAT_8032f22c = DAT_8032f22c + 1;
    DAT_8032f230 = DAT_8032f230 + 0x5e6;
  }
  else if ((DAT_8032f238 < 1) && (-1 < DAT_8032f238)) {
    *DAT_8032f22c = 7;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = uVar1;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = uVar3;
    DAT_8032f22c = DAT_8032f22c + 1;
    DAT_8032f230 = DAT_8032f230 + 0x546;
  }
  local_18[0] = __AXGetPBs();
  *DAT_8032f22c = 2;
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = (short)local_18[0];
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = 3;
  DAT_8032f22c = DAT_8032f22c + 1;
  if (DAT_8032f238 == 2) {
    __AXGetAuxAInput(local_18);
    if (local_18[0] != 0) {
      *DAT_8032f22c = 0x13;
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxAInputDpl2(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxAOutput(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxAOutputDpl2R(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxAOutputDpl2Ls(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxAOutputDpl2Rs(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      DAT_8032f230 = DAT_8032f230 + 0xded;
    }
    *DAT_8032f22c = 0x10;
    DAT_8032f22c = DAT_8032f22c + 1;
    __AXGetAuxBForDPL2(local_18);
    *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = (short)local_18[0];
    DAT_8032f22c = DAT_8032f22c + 1;
    __AXGetAuxBOutputDPL2(local_18);
    *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = (short)local_18[0];
    DAT_8032f22c = DAT_8032f22c + 1;
    DAT_8032f230 = DAT_8032f230 + 0xded;
  }
  else {
    __AXGetAuxAInput(local_18);
    if (local_18[0] != 0) {
      *DAT_8032f22c = 4;
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxAOutput(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      DAT_8032f230 = DAT_8032f230 + 0xded;
    }
    __AXGetAuxBInput(local_18);
    if (local_18[0] != 0) {
      *DAT_8032f22c = 5;
      DAT_8032f22c = DAT_8032f22c + 1;
      DAT_8032f230 = DAT_8032f230 + 0xded;
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
      __AXGetAuxBOutput(local_18);
      *DAT_8032f22c = (short)((uint)local_18[0] >> 0x10);
      DAT_8032f22c = DAT_8032f22c + 1;
      *DAT_8032f22c = (short)local_18[0];
      DAT_8032f22c = DAT_8032f22c + 1;
    }
  }
  if (DAT_8032f234 != 0) {
    *DAT_8032f22c = 0x12;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = 0x8000;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = 10;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = 0x8021;
    DAT_8032f22c = DAT_8032f22c + 1;
    *DAT_8032f22c = 0x7e00;
    DAT_8032f22c = DAT_8032f22c + 1;
    DAT_8032f230 = DAT_8032f230 + 3000;
  }
  *DAT_8032f22c = 0xe;
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = uVar1;
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = uVar3;
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = (short)((uint)param_2 >> 0x10);
  DAT_8032f22c = DAT_8032f22c + 1;
  *DAT_8032f22c = (short)param_2;
  DAT_8032f22c = DAT_8032f22c + 1;
  DAT_8032f230 = DAT_8032f230 + 10000;
  *DAT_8032f22c = 0xf;
  DAT_8032f22c = DAT_8032f22c + 1;
  DAT_8032f230 = DAT_8032f230 + 2;
  DCFlushRange(puVar2,0x300);
  return;
}

