// Function: GetTmpArtifactData__8GbaQueueFiPUc
// Entry: 800c9e50
// Size: 480 bytes

undefined4 GetTmpArtifactData__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined2 local_108;
  undefined2 local_106;
  undefined2 local_104;
  undefined2 local_102;
  char local_100;
  char local_ff;
  char local_fe;
  char local_fd;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined2 local_ec;
  char local_ea;
  char local_e9;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined auStack_e0 [3];
  char local_dd;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined2 local_cc;
  undefined4 local_ca;
  undefined4 local_c6 [32];
  undefined4 local_46;
  undefined4 local_42;
  undefined4 local_3e;
  undefined4 local_3a;
  undefined4 local_36;
  undefined4 local_32;
  undefined local_2e;
  undefined local_2d;
  undefined local_2c;
  undefined local_2b;
  undefined local_2a;
  undefined auStack_29 [21];
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  iVar5 = param_2 * 0xdc;
  local_100 = gbaQueue->compatibilityStr[iVar5 + -4];
  local_ff = gbaQueue->compatibilityStr[iVar5 + -3];
  local_fe = gbaQueue->compatibilityStr[iVar5 + -2];
  local_fd = gbaQueue->compatibilityStr[iVar5 + -1];
  local_fc = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5);
  local_f8 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 4);
  local_f4 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 8);
  local_f0 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0xc);
  local_ec = *(undefined2 *)(gbaQueue->compatibilityStr + iVar5 + 0x10);
  local_ea = gbaQueue->compatibilityStr[iVar5 + 0x12];
  local_e9 = gbaQueue->compatibilityStr[iVar5 + 0x13];
  local_e8 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x14);
  local_e4 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x18);
  __copy(auStack_e0,gbaQueue->compatibilityStr + iVar5 + 0x1c,3);
  local_dd = gbaQueue->compatibilityStr[iVar5 + 0x1f];
  puVar4 = &local_ca;
  pcVar3 = gbaQueue->compatibilityStr + iVar5 + 0x32;
  local_dc = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x20);
  local_d8 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x24);
  local_d4 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x28);
  local_d0 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x2c);
  local_cc = *(undefined2 *)(gbaQueue->compatibilityStr + iVar5 + 0x30);
  local_ca = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x32);
  iVar6 = 0x10;
  do {
    pcVar1 = pcVar3 + 4;
    pcVar3 = pcVar3 + 8;
    uVar2 = *(undefined4 *)pcVar3;
    puVar4[1] = *(undefined4 *)pcVar1;
    puVar4 = puVar4 + 2;
    *puVar4 = uVar2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  local_46 = *(undefined4 *)(&gbaQueue->field_0x50e + iVar5);
  local_42 = *(undefined4 *)(&gbaQueue->field_0x512 + iVar5);
  local_3e = *(undefined4 *)(&gbaQueue->field_0x516 + iVar5);
  local_3a = *(undefined4 *)(&gbaQueue->field_0x51a + iVar5);
  local_36 = *(undefined4 *)(&gbaQueue->field_0x51e + iVar5);
  local_32 = *(undefined4 *)(&gbaQueue->field_0x522 + iVar5);
  local_2e = (&gbaQueue->bonus)[iVar5];
  local_2d = (&gbaQueue->field_0x527)[iVar5];
  local_2c = (&gbaQueue->field_0x528)[iVar5];
  local_2b = (&gbaQueue->field_0x529)[iVar5];
  local_2a = (&gbaQueue->itemUse)[iVar5];
  __copy(auStack_29,&gbaQueue->field_0x52b + iVar5,4);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  local_108 = CONCAT11(local_46._1_1_,local_46._0_1_);
  local_106 = CONCAT11((undefined)local_46,local_46._2_1_);
  local_104 = CONCAT11(local_42._1_1_,local_42._0_1_);
  local_102 = CONCAT11((undefined)local_42,local_42._2_1_);
  memcpy(param_3,&local_108,8);
  return 8;
}

