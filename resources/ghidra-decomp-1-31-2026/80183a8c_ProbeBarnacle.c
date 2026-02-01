// Function: ProbeBarnacle
// Entry: 80183a8c
// Size: 396 bytes

undefined4 ProbeBarnacle(int param_1,int param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 local_14;
  
  if (((param_1 != 2) && (param_2 == 0)) && (iVar6 = EXIAttach(param_1,0), iVar6 == 0)) {
    return 0;
  }
  uVar7 = EXILock(param_1,param_2,0);
  uVar1 = countLeadingZeros(uVar7);
  uVar1 = uVar1 >> 5;
  if (uVar1 == 0) {
    uVar7 = EXISelect(param_1,param_2,0);
    uVar1 = countLeadingZeros(uVar7);
    uVar1 = uVar1 >> 5;
    if (uVar1 == 0) {
      local_14 = 0x20011300;
      uVar7 = EXIImm(param_1,&local_14,4,1,0);
      uVar1 = countLeadingZeros(uVar7);
      uVar7 = EXISync(param_1);
      uVar2 = countLeadingZeros(uVar7);
      uVar7 = EXIImm(param_1,param_3,4,0,0);
      uVar3 = countLeadingZeros(uVar7);
      uVar7 = EXISync(param_1);
      uVar4 = countLeadingZeros(uVar7);
      uVar7 = EXIDeselect(param_1);
      uVar5 = countLeadingZeros(uVar7);
      uVar1 = (uVar1 | uVar2 | uVar3 | uVar4 | uVar5) >> 5;
    }
    EXIUnlock(param_1);
  }
  if ((param_1 != 2) && (param_2 == 0)) {
    EXIDetach(param_1);
  }
  if (uVar1 == 0) {
    if (*param_3 == -1) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
    }
  }
  else {
    uVar7 = 0;
  }
  return uVar7;
}

