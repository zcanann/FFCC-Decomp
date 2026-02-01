// Function: GetArtifactData__8GbaQueueFiPUc
// Entry: 800ca5d4
// Size: 468 bytes

undefined4 GetArtifactData__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  uint local_108;
  uint local_104;
  uint local_100;
  char local_fc;
  char local_fb;
  char local_fa;
  char local_f9;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined2 local_e8;
  char local_e6;
  char local_e5;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined auStack_dc [3];
  char local_d9;
  undefined4 local_d8;
  uint local_d4;
  uint local_d0;
  uint local_cc;
  undefined2 local_c8;
  undefined4 local_c6;
  undefined4 local_c2 [32];
  undefined4 local_42;
  undefined4 local_3e;
  undefined4 local_3a;
  undefined4 local_36;
  undefined4 local_32;
  undefined4 local_2e;
  undefined local_2a;
  undefined local_29;
  undefined local_28;
  undefined local_27;
  undefined local_26;
  undefined auStack_25 [17];
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  iVar5 = param_2 * 0xdc;
  local_fc = gbaQueue->compatibilityStr[iVar5 + -4];
  local_fb = gbaQueue->compatibilityStr[iVar5 + -3];
  local_fa = gbaQueue->compatibilityStr[iVar5 + -2];
  local_f9 = gbaQueue->compatibilityStr[iVar5 + -1];
  local_f8 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5);
  local_f4 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 4);
  local_f0 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 8);
  local_ec = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0xc);
  local_e8 = *(undefined2 *)(gbaQueue->compatibilityStr + iVar5 + 0x10);
  local_e6 = gbaQueue->compatibilityStr[iVar5 + 0x12];
  local_e5 = gbaQueue->compatibilityStr[iVar5 + 0x13];
  local_e4 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x14);
  local_e0 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x18);
  __copy(auStack_dc,gbaQueue->compatibilityStr + iVar5 + 0x1c,3);
  local_d9 = gbaQueue->compatibilityStr[iVar5 + 0x1f];
  puVar4 = &local_c6;
  pcVar3 = gbaQueue->compatibilityStr + iVar5 + 0x32;
  local_d8 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x20);
  local_d4 = *(uint *)(gbaQueue->compatibilityStr + iVar5 + 0x24);
  local_d0 = *(uint *)(gbaQueue->compatibilityStr + iVar5 + 0x28);
  local_cc = *(uint *)(gbaQueue->compatibilityStr + iVar5 + 0x2c);
  local_c8 = *(undefined2 *)(gbaQueue->compatibilityStr + iVar5 + 0x30);
  local_c6 = *(undefined4 *)(gbaQueue->compatibilityStr + iVar5 + 0x32);
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
  local_42 = *(undefined4 *)(&gbaQueue->field_0x50e + iVar5);
  local_3e = *(undefined4 *)(&gbaQueue->field_0x512 + iVar5);
  local_3a = *(undefined4 *)(&gbaQueue->field_0x516 + iVar5);
  local_36 = *(undefined4 *)(&gbaQueue->field_0x51a + iVar5);
  local_32 = *(undefined4 *)(&gbaQueue->field_0x51e + iVar5);
  local_2e = *(undefined4 *)(&gbaQueue->field_0x522 + iVar5);
  local_2a = (&gbaQueue->bonus)[iVar5];
  local_29 = (&gbaQueue->field_0x527)[iVar5];
  local_28 = (&gbaQueue->field_0x528)[iVar5];
  local_27 = (&gbaQueue->field_0x529)[iVar5];
  local_26 = (&gbaQueue->itemUse)[iVar5];
  __copy(auStack_25,&gbaQueue->field_0x52b + iVar5,4);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  local_108 = local_d4 << 0x18 | (local_d4 >> 8 & 0xff) << 0x10 | (local_d4 >> 0x10 & 0xff) << 8 |
              local_d4 >> 0x18;
  local_104 = local_d0 << 0x18 | (local_d0 >> 8 & 0xff) << 0x10 | (local_d0 >> 0x10 & 0xff) << 8 |
              local_d0 >> 0x18;
  local_100 = local_cc << 0x18 | (local_cc >> 8 & 0xff) << 0x10 | (local_cc >> 0x10 & 0xff) << 8 |
              local_cc >> 0x18;
  memcpy(param_3,&local_108,0xc);
  return 0xc;
}

