// Function: InsertAlarm
// Entry: 8017c1dc
// Size: 592 bytes

void InsertAlarm(OSAlarm *osAlarm,undefined4 param_2,uint param_3,uint param_4,void *param_5)

{
  ulonglong uVar1;
  uint32_t uVar2;
  uint uVar3;
  OSAlarm *pOVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  undefined8 uVar9;
  longlong lVar10;
  
  if (0x80000000 <
      (uint)(*(int *)((int)&osAlarm->period + 4) != 0) + (*(uint *)&osAlarm->period ^ 0x80000000)) {
    uVar9 = __OSGetSystemTime();
    uVar3 = (uint)((ulonglong)uVar9 >> 0x20);
    uVar5 = (uint)uVar9;
    param_3 = *(uint *)&osAlarm->start;
    param_4 = *(uint *)((int)&osAlarm->start + 4);
    if ((param_3 ^ 0x80000000) < (uint)(param_4 < uVar5) + (uVar3 ^ 0x80000000)) {
      iVar7 = *(int *)&osAlarm->period;
      uVar6 = *(uint *)((int)&osAlarm->period + 4);
      lVar10 = __div2i(uVar3 - ((uVar5 < param_4) + param_3),uVar5 - param_4,iVar7,uVar6);
      uVar1 = lVar10 + 1;
      uVar3 = uVar6 * (int)uVar1;
      bVar8 = CARRY4(param_4,uVar3);
      param_4 = param_4 + uVar3;
      param_3 = param_3 + iVar7 * (int)uVar1 +
                          (int)((ulonglong)uVar6 * (uVar1 & 0xffffffff) >> 0x20) +
                          uVar6 * (int)(uVar1 >> 0x20) + (uint)bVar8;
    }
  }
  osAlarm->handler = param_5;
  *(uint *)((int)&osAlarm->fire + 4) = param_4;
  *(uint *)&osAlarm->fire = param_3;
  pOVar4 = (OSAlarm *)OSAlarm_8032ef60.handler;
  while( true ) {
    if (pOVar4 == (OSAlarm *)0x0) {
      osAlarm->next = (OSAlarm *)0x0;
      uVar2 = OSAlarm_8032ef60.tag;
      bVar8 = OSAlarm_8032ef60.tag == 0;
      pOVar4 = osAlarm;
      osAlarm->prev = (OSAlarm *)OSAlarm_8032ef60.tag;
      OSAlarm_8032ef60.tag = (uint32_t)pOVar4;
      if (bVar8) {
        OSAlarm_8032ef60.handler = osAlarm;
        OSAlarm_8032ef60.tag = (uint32_t)osAlarm;
        uVar9 = __OSGetSystemTime();
        uVar3 = *(uint *)((int)&osAlarm->fire + 4);
        uVar5 = uVar3 - (uint)uVar9;
        uVar3 = *(int *)&osAlarm->fire -
                ((uint)(uVar3 < (uint)uVar9) + (int)((ulonglong)uVar9 >> 0x20)) ^ 0x80000000;
        if (uVar3 < 0x80000000) {
          PPCMtdec(0);
        }
        else if (uVar3 < (uVar5 < 0x80000000) + 0x80000000) {
          PPCMtdec(uVar5);
        }
        else {
          PPCMtdec(0x7fffffff);
        }
      }
      else {
        *(OSAlarm **)(uVar2 + 0x14) = osAlarm;
      }
      return;
    }
    if ((param_3 ^ 0x80000000) <
        (uint)(param_4 < *(uint *)((int)&pOVar4->fire + 4)) + (*(uint *)&pOVar4->fire ^ 0x80000000))
    break;
    pOVar4 = pOVar4->next;
  }
  osAlarm->prev = pOVar4->prev;
  pOVar4->prev = osAlarm;
  osAlarm->next = pOVar4;
  if (osAlarm->prev != (OSAlarm *)0x0) {
    osAlarm->prev->next = osAlarm;
    return;
  }
  OSAlarm_8032ef60.handler = osAlarm;
  uVar9 = __OSGetSystemTime();
  uVar3 = *(uint *)((int)&osAlarm->fire + 4);
  uVar5 = uVar3 - (uint)uVar9;
  uVar3 = *(int *)&osAlarm->fire - ((uint)(uVar3 < (uint)uVar9) + (int)((ulonglong)uVar9 >> 0x20)) ^
          0x80000000;
  if (uVar3 < 0x80000000) {
    PPCMtdec(0);
    return;
  }
  if (uVar3 < (uVar5 < 0x80000000) + 0x80000000) {
    PPCMtdec(uVar5);
    return;
  }
  PPCMtdec(0x7fffffff);
  return;
}

