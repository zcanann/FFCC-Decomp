// Function: GetPlayerPos__8GbaQueueFiPUi
// Entry: 800ce9ac
// Size: 568 bytes

void GetPlayerPos__8GbaQueueFiPUi(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined local_398;
  undefined local_397;
  char local_396;
  char local_395;
  undefined local_394;
  char local_393;
  char local_392;
  char local_391;
  undefined local_390;
  char local_38f;
  char local_38e;
  char local_38d;
  undefined auStack_38c [54];
  undefined2 local_356;
  undefined2 local_354;
  char cStack_279;
  char cStack_277;
  char cStack_19d;
  char cStack_19b;
  char cStack_c1;
  char cStack_bf;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  memcpy(auStack_38c,&gbaQueue->field_0x454,0x370);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  memset(&local_398,0,0xc);
  if (gbaQueue->field_0x2d56 != '\0') {
    param_2 = 0;
  }
  puVar2 = auStack_38c;
  local_398 = 0x11;
  local_394 = 0x51;
  uVar1 = 0;
  local_390 = 0x91;
  iVar3 = 0;
  iVar5 = 2;
  do {
    if (iVar3 == param_2) {
      uVar1 = uVar1 | 1 << iVar3 & 0xffU;
    }
    else if ((((puVar2[3] != '\0') &&
              (-0x51 < (int)*(short *)(puVar2 + 0x36) - (int)(short)(&local_356)[param_2 * 0x6e]))
             && ((int)*(short *)(puVar2 + 0x36) - (int)(short)(&local_356)[param_2 * 0x6e] < 0x51))
            && ((-0x41 < (int)*(short *)(puVar2 + 0x38) - (int)(short)(&local_354)[param_2 * 0x6e]
                && ((int)*(short *)(puVar2 + 0x38) - (int)(short)(&local_354)[param_2 * 0x6e] < 0x41
                   )))) {
      uVar1 = uVar1 | 1 << iVar3 & 0xffU;
    }
    iVar4 = iVar3 + 1;
    if (iVar4 == param_2) {
      uVar1 = uVar1 | 1 << iVar4 & 0xffU;
    }
    else if (((puVar2[0xdf] != '\0') &&
             (-0x51 < (int)*(short *)(puVar2 + 0x112) - (int)(short)(&local_356)[param_2 * 0x6e]))
            && (((int)*(short *)(puVar2 + 0x112) - (int)(short)(&local_356)[param_2 * 0x6e] < 0x51
                && ((-0x41 < (int)*(short *)(puVar2 + 0x114) -
                             (int)(short)(&local_354)[param_2 * 0x6e] &&
                    ((int)*(short *)(puVar2 + 0x114) - (int)(short)(&local_354)[param_2 * 0x6e] <
                     0x41)))))) {
      uVar1 = uVar1 | 1 << iVar4 & 0xffU;
    }
    puVar2 = puVar2 + 0x1b8;
    iVar3 = iVar3 + 2;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  local_38e = (char)(&local_356)[param_2 * 0x6e];
  local_396 = (char)local_356 - local_38e;
  local_393 = cStack_279 - local_38e;
  local_391 = cStack_19d - local_38e;
  local_38e = cStack_c1 - local_38e;
  local_38d = (char)(&local_354)[param_2 * 0x6e];
  local_395 = (char)local_354 - local_38d;
  local_392 = cStack_277 - local_38d;
  local_38f = cStack_19b - local_38d;
  local_397 = (undefined)uVar1;
  local_38d = cStack_bf - local_38d;
  memcpy(param_3,&local_398,0xc);
  return;
}

