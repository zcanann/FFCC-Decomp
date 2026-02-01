// Function: ?getItemPdt__10CGCharaObjFiiRiRiRi
// Entry: 8010caf0
// Size: 216 bytes

uint _getItemPdt__10CGCharaObjFiiRiRiRi(int param_1)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  
  bVar2 = false;
  iVar4 = *(int *)(param_1 + 0xf8);
  if ((iVar4 != 0) && (*(int *)(iVar4 + 0x168) != 0)) {
    bVar2 = true;
  }
  if (bVar2) {
    iVar4 = *(int *)(iVar4 + 0x168);
    if (*(int *)(iVar4 + 0xd0) == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = (uint)(FLOAT_80331964 + (*(float *)(iVar4 + 0xc0) - *(float *)(iVar4 + 0xbc)));
      if (uVar3 == 1) {
        uVar3 = 1;
      }
      else {
        uVar1 = (uint)*(float *)(param_1 + 0x4a0);
        if (FLOAT_80331988 <= *(float *)(param_1 + 0x4c8)) {
          uVar3 = ((int)uVar1 >> 0x1f) + ((uint)(uVar3 <= uVar1) - ((int)uVar3 >> 0x1f)) & 0xff;
        }
        else {
          uVar3 = countLeadingZeros(uVar1 - ((int)uVar1 / (int)uVar3) * uVar3);
          uVar3 = (1 << (uVar3 & 0x1f) | 1U >> 0x20 - (uVar3 & 0x1f)) & 1;
        }
      }
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

