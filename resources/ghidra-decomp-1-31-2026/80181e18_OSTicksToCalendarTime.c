// Function: OSTicksToCalendarTime
// Entry: 80181e18
// Size: 516 bytes

void OSTicksToCalendarTime(int param_1,uint param_2,int *param_3)

{
  int extraout_r4;
  int extraout_r4_00;
  int extraout_r4_01;
  int extraout_r4_02;
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  
  lVar6 = __mod2i(param_1,param_2,0,DAT_800000f8 >> 2);
  if (((uint)((ulonglong)lVar6 >> 0x20) ^ 0x80000000) < 0x80000000) {
    lVar6 = lVar6 + (ulonglong)(DAT_800000f8 >> 2);
  }
  iVar5 = (int)((ulonglong)lVar6 >> 0x20);
  uVar3 = (uint)lVar6;
  uVar7 = __div2i((int)((ulonglong)(lVar6 * 8) >> 0x20),(int)(lVar6 * 8),0,DAT_800000f8 / 500000);
  __mod2i((int)((ulonglong)uVar7 >> 0x20),(int)uVar7,0,1000);
  param_3[9] = extraout_r4;
  uVar7 = __div2i(iVar5,uVar3,0,DAT_800000f8 / 4000);
  __mod2i((int)((ulonglong)uVar7 >> 0x20),(int)uVar7,0,1000);
  param_3[8] = extraout_r4_00;
  param_1 = param_1 - ((uint)(param_2 < uVar3) + iVar5);
  uVar7 = __div2i(param_1,param_2 - uVar3,0,DAT_800000f8 >> 2);
  __div2i((int)((ulonglong)uVar7 >> 0x20),(int)uVar7,0,0x15180);
  iVar4 = extraout_r4_01 + 0xb2575;
  uVar7 = __div2i(param_1,param_2 - uVar3,0,DAT_800000f8 >> 2);
  __mod2i((int)((ulonglong)uVar7 >> 0x20),(int)uVar7,0,0x15180);
  iVar5 = extraout_r4_02;
  if (extraout_r4_02 < 0) {
    iVar4 = extraout_r4_01 + 0xb2574;
    iVar5 = extraout_r4_02 + 0x15180;
  }
  GetDates(iVar4,param_3);
  iVar4 = iVar5 / 0x3c + (iVar5 >> 0x1f);
  iVar2 = iVar4 - (iVar4 >> 0x1f);
  iVar1 = iVar2 / 0x3c + (iVar2 >> 0x1f);
  param_3[2] = iVar1 - (iVar1 >> 0x1f);
  param_3[1] = iVar2 + (iVar1 - (iVar1 >> 0x1f)) * -0x3c;
  *param_3 = iVar5 + (iVar4 - (iVar4 >> 0x1f)) * -0x3c;
  return;
}

