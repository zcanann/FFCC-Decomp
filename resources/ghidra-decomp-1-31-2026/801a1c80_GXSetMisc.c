// Function: GXSetMisc
// Entry: 801a1c80
// Size: 148 bytes

void GXSetMisc(int param_1,int param_2)

{
  undefined2 *puVar1;
  uint uVar2;
  
  puVar1 = DAT_80333828;
  if (param_1 == 2) {
    *(char *)((int)DAT_80333828 + 0x4f1) = '\x01' - (param_2 == 0);
    return;
  }
  if (1 < param_1) {
    if (3 < param_1) {
      return;
    }
    *(char *)(DAT_80333828 + 0x279) = '\x01' - (param_2 == 0);
    return;
  }
  if (param_1 == 0) {
    return;
  }
  if (param_1 < 0) {
    return;
  }
  DAT_80333828[2] = (short)param_2;
  uVar2 = countLeadingZeros((uint)(ushort)puVar1[2]);
  *puVar1 = (short)(uVar2 >> 5);
  puVar1[1] = 1;
  if (puVar1[2] == 0) {
    return;
  }
  *(uint *)(puVar1 + 0x27a) = *(uint *)(puVar1 + 0x27a) | 8;
  return;
}

