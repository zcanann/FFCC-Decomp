// Function: CMakeFavorite__8GbaQueueFiUi
// Entry: 800cbf74
// Size: 580 bytes

void CMakeFavorite__8GbaQueueFiUi(GbaQueue *makeFavorite,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  OSSemaphore *osSemaphore;
  undefined local_48;
  undefined uStack_47;
  undefined uStack_46;
  undefined uStack_45;
  undefined2 local_44 [2];
  undefined local_40;
  undefined local_3f;
  undefined2 local_3e;
  short local_3c;
  undefined local_3a;
  undefined auStack_39 [17];
  undefined local_28;
  undefined auStack_27 [2];
  undefined auStack_25 [4];
  undefined local_21;
  
  uStack_45 = (undefined)param_3;
  uStack_46 = (undefined)(param_3 >> 8);
  uStack_47 = (undefined)(param_3 >> 0x10);
  if ((int)(param_3 >> 0x18) >> 6 == 0) {
    OSWaitSemaphore(makeFavorite->accessSemaphores + param_2);
    iVar1 = param_2 * 0x20;
    local_48 = (undefined)(param_3 >> 0x18);
    (&makeFavorite->field_0x2cb3)[iVar1] = local_48;
    *(undefined2 *)(&makeFavorite->field_0x2cb4 + iVar1) = 1;
    *(short *)(&makeFavorite->field_0x2cb6 + iVar1) = (short)(param_3 >> 8);
    memset(&makeFavorite->field_0x2ccd + iVar1,0,4);
    (&makeFavorite->field_0x2ccd)[iVar1] = uStack_45;
    OSSignalSemaphore(makeFavorite->accessSemaphores + param_2);
  }
  else {
    osSemaphore = makeFavorite->accessSemaphores + param_2;
    OSWaitSemaphore(osSemaphore);
    iVar1 = param_2 * 0x20;
    iVar2 = iVar1 + 0x2ccd;
    iVar4 = *(short *)(&makeFavorite->field_0x2cb4 + iVar1) * 3;
    *(short *)(&makeFavorite->field_0x2cb4 + iVar1) =
         *(short *)(&makeFavorite->field_0x2cb4 + iVar1) + 1;
    (&makeFavorite->field_0x2ccb)[iVar4 + iVar2 + -0x2ccd] = uStack_47;
    (&makeFavorite->field_0x2ccc)[iVar4 + iVar2 + -0x2ccd] = uStack_46;
    (&makeFavorite->field_0x2ccd)[iVar4 + iVar2 + -0x2ccd] = uStack_45;
    if (1 < *(short *)(&makeFavorite->field_0x2cb4 + iVar1)) {
      local_40 = (&makeFavorite->cmakeInfo)[iVar1];
      local_3f = (&makeFavorite->field_0x2cb3)[iVar1];
      local_3e = *(undefined2 *)(&makeFavorite->field_0x2cb4 + iVar1);
      local_3c = *(short *)(&makeFavorite->field_0x2cb6 + iVar1);
      local_3a = (&makeFavorite->field_0x2cb8)[iVar1];
      __copy(auStack_39,&makeFavorite->field_0x2cb9 + iVar1,0x11);
      local_28 = (&makeFavorite->field_0x2cca)[iVar1];
      __copy(auStack_27,&makeFavorite->field_0x2ccb + iVar1,2);
      __copy(auStack_25,&makeFavorite->field_0x2ccd + iVar1,4);
      local_21 = (&makeFavorite->field_0x2cd1)[iVar1];
    }
    OSSignalSemaphore(osSemaphore);
    if (1 < *(short *)(&makeFavorite->field_0x2cb4 + iVar1)) {
      local_44[0] = 0xffff;
      sVar3 = Crc16__6JoyBusFiPUcPUs(&Joybus,4,auStack_25,local_44);
      if (sVar3 == local_3c) {
        SendResult__6JoyBusFiiii(&Joybus,param_2,0,local_3f,0);
        OSWaitSemaphore(osSemaphore);
        (&makeFavorite->field_0x2cb3)[iVar1] = 0;
        *(undefined2 *)(&makeFavorite->field_0x2cb4 + iVar1) = 0;
        *(undefined2 *)(&makeFavorite->field_0x2cb6 + iVar1) = 0;
        OSSignalSemaphore(osSemaphore);
      }
      else {
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce
                    (&System,s__s__d___Error_CMakeFavorite___cr_801db3c0,s_gbaque_cpp_801db370,0xbdc
                    );
        }
        SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_3f,0);
      }
    }
  }
  return;
}

