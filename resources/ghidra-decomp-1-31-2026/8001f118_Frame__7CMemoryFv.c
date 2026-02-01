// Function: Frame__7CMemoryFv
// Entry: 8001f118
// Size: 128 bytes

void Frame__7CMemoryFv(int param_1)

{
  bool bVar1;
  ushort uVar3;
  uint uVar2;
  
  bVar1 = false;
  if (Pad._452_4_ == 0) {
    if (Pad._448_4_ == -1) goto LAB_8001f140;
  }
  bVar1 = true;
LAB_8001f140:
  if (bVar1) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._54_2_;
  }
  if ((uVar3 & 0x200) == 0) {
    return;
  }
  uVar2 = countLeadingZeros(*(undefined4 *)(param_1 + 0x7798));
  *(uint *)(param_1 + 0x7798) = uVar2 >> 5 & 0xff;
  return;
}

