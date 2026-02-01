// Function: ClrStageFlg__8GbaQueueFi
// Entry: 800cfa10
// Size: 116 bytes

void ClrStageFlg__8GbaQueueFi(GbaQueue *stageFlg,int param_2)

{
  byte bVar1;
  
  OSWaitSemaphore(stageFlg->accessSemaphores + param_2);
  bVar1 = (byte)(1 << param_2);
  stageFlg->field_0x44c = stageFlg->field_0x44c & ~bVar1;
  stageFlg->chgScouFlg = stageFlg->chgScouFlg | bVar1;
  OSSignalSemaphore(stageFlg->accessSemaphores + param_2);
  return;
}

