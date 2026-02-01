// Function: GetDates
// Entry: 80181c7c
// Size: 412 bytes

void GetDates(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = param_1 + 6;
  iVar5 = iVar7 / 7 + (iVar7 >> 0x1f);
  iVar3 = param_1 / 0x16d + (param_1 >> 0x1f);
  uVar6 = iVar3 - (iVar3 >> 0x1f);
  iVar3 = uVar6 * 0x16d;
  *(int *)(param_2 + 0x18) = iVar7 + (iVar5 - (iVar5 >> 0x1f)) * -7;
  while( true ) {
    if ((int)uVar6 < 1) {
      iVar5 = 0;
    }
    else {
      iVar5 = uVar6 - 1;
      iVar7 = iVar5 / 400 + (iVar5 >> 0x1f);
      iVar5 = iVar5 / 100 + (iVar5 >> 0x1f);
      uVar4 = uVar6 + 3;
      iVar5 = (iVar7 - (iVar7 >> 0x1f)) +
              ((((int)uVar4 >> 2) + (uint)((int)uVar4 < 0 && (uVar4 & 3) != 0)) -
              (iVar5 - (iVar5 >> 0x1f)));
    }
    if (iVar3 + iVar5 <= param_1) break;
    iVar3 = iVar3 + -0x16d;
    uVar6 = uVar6 - 1;
  }
  *(uint *)(param_2 + 0x14) = uVar6;
  param_1 = param_1 - (iVar3 + iVar5);
  *(int *)(param_2 + 0x1c) = param_1;
  bVar2 = true;
  bVar1 = false;
  if ((uVar6 == (((int)uVar6 >> 2) + (uint)((int)uVar6 < 0 && (uVar6 & 3) != 0)) * 4) &&
     (iVar3 = (int)uVar6 / 100 + ((int)uVar6 >> 0x1f), uVar6 + (iVar3 - (iVar3 >> 0x1f)) * -100 != 0
     )) {
    bVar1 = true;
  }
  if ((!bVar1) &&
     (iVar3 = (int)uVar6 / 400 + ((int)uVar6 >> 0x1f), uVar6 + (iVar3 - (iVar3 >> 0x1f)) * -400 != 0
     )) {
    bVar2 = false;
  }
  if (bVar2) {
    iVar3 = -0x7fde8e80;
  }
  else {
    iVar3 = -0x7fde8eb0;
  }
  iVar7 = 0xc;
  iVar5 = 0x30;
  do {
    iVar5 = iVar5 + -4;
    iVar7 = iVar7 + -1;
  } while (param_1 < *(int *)(iVar3 + iVar5));
  *(int *)(param_2 + 0x10) = iVar7;
  *(int *)(param_2 + 0xc) = (param_1 - *(int *)(iVar3 + iVar5)) + 1;
  return;
}

