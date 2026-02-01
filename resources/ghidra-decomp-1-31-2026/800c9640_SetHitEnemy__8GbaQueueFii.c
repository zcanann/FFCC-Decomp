// Function: SetHitEnemy__8GbaQueueFii
// Entry: 800c9640
// Size: 160 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetHitEnemy__8GbaQueueFii(GbaQueue *gbaQueue,int param_2,int param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  
  if (param_3 < 0) {
    uVar1 = 0xffff;
    uVar2 = 0xffff;
  }
  else {
    uVar1 = (undefined2)param_3;
    uVar2 = *(undefined2 *)(Game.game.m_scriptWork[2][0][param_3] + 0x1c);
  }
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  *(undefined2 *)(&gbaQueue->hitEInfo + param_2) = uVar1;
  *(undefined2 *)((int)&gbaQueue->hitEInfo + param_2 * 4 + 2) = uVar2;
  gbaQueue->chgHitFlg = gbaQueue->chgHitFlg | (byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

