// Function: onChangeStat__10CGCharaObjFi
// Entry: 80112b1c
// Size: 168 bytes

void onChangeStat__10CGCharaObjFi(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 != 6) {
    if (5 < param_2) {
      if (param_2 == 9) {
        iVar1 = 0;
        do {
          setSta__10CGCharaObjFii(param_1,iVar1,0);
          iVar1 = iVar1 + 1;
        } while (iVar1 < 0x27);
        *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) | 2;
      }
      goto LAB_80112b9c;
    }
    if (param_2 != 2) goto LAB_80112b9c;
  }
  *(undefined4 *)(param_1 + 0x6a8) = 0;
  *(undefined4 *)(param_1 + 0x698) = 0;
  *(undefined4 *)(param_1 + 0x69c) = 0xffffffff;
LAB_80112b9c:
  *(byte *)(param_1 + 0x63c) = *(byte *)(param_1 + 0x63c) & 0x7f;
  return;
}

