// Function: __mod2i
// Entry: 801b0340
// Size: 268 bytes

undefined8 __mod2i(uint param_1,uint param_2,int param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  bool bVar12;
  
  bVar1 = (int)param_1 < 0;
  if (bVar1) {
    bVar11 = param_2 != 0;
    param_2 = -param_2;
    param_1 = -(bVar11 + param_1);
  }
  if (param_3 < 0) {
    bVar11 = param_4 != 0;
    param_4 = -param_4;
    param_3 = -((uint)bVar11 + param_3);
  }
  iVar2 = countLeadingZeros(param_1);
  iVar8 = countLeadingZeros(param_2);
  if (param_1 == 0) {
    iVar2 = iVar8 + 0x20;
  }
  iVar8 = countLeadingZeros(param_3);
  iVar10 = countLeadingZeros(param_4);
  if (param_3 == 0) {
    iVar8 = iVar10 + 0x20;
  }
  if (iVar2 <= iVar8) {
    iVar10 = 0x40 - (iVar8 + 1);
    iVar8 = iVar2 + iVar10;
    iVar10 = (0x40 - iVar2) - iVar10;
    if (iVar10 < 0x20) {
      uVar6 = param_2 >> iVar10 | param_1 << 0x20 - iVar10;
      uVar5 = param_1 >> iVar10;
    }
    else {
      uVar6 = param_1 >> iVar10 + -0x20;
      uVar5 = 0;
    }
    if (iVar8 < 0x20) {
      uVar3 = param_1 << iVar8 | param_2 >> 0x20 - iVar8;
      uVar4 = param_2 << iVar8;
    }
    else {
      uVar3 = param_2 << iVar8 + -0x20;
      uVar4 = 0;
    }
    bVar11 = false;
    param_1 = uVar5;
    param_2 = uVar6;
    do {
      bVar12 = CARRY4(uVar4,(uint)bVar11);
      uVar5 = uVar4 + bVar11;
      bVar11 = CARRY4(uVar4,uVar5);
      uVar4 = uVar4 + uVar5;
      uVar5 = (uint)(bVar12 || bVar11);
      bVar12 = CARRY4(uVar3,uVar5);
      uVar5 = uVar3 + uVar5;
      bVar11 = CARRY4(uVar3,uVar5);
      uVar3 = uVar3 + uVar5;
      uVar5 = (uint)(bVar12 || bVar11);
      uVar6 = param_2 + uVar5;
      uVar7 = param_2 + uVar6;
      uVar5 = param_1 * 2 + (uint)(CARRY4(param_2,uVar5) || CARRY4(param_2,uVar6));
      uVar6 = (uint)(uVar7 < param_4) + param_3;
      uVar9 = uVar5 - uVar6;
      param_1 = uVar5;
      param_2 = uVar7;
      if (-1 < (int)uVar9) {
        param_1 = uVar9;
        param_2 = uVar7 - param_4;
      }
      bVar11 = -1 < (int)uVar9 || uVar6 <= uVar5;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  if (bVar1) {
    return CONCAT44(-((param_2 != 0) + param_1),-param_2);
  }
  return CONCAT44(param_1,param_2);
}

