// Function: OSDumpContext
// Entry: 8017d9f4
// Size: 680 bytes

void OSDumpContext(undefined4 *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined auStack_2e8 [416];
  undefined2 local_148;
  undefined2 local_146;
  
  OSReport(s___________________________Contex_80216c18,param_1);
  uVar6 = 0;
  puVar7 = param_1;
  do {
    OSReport(s_r__2d___0x_08x___14d__r__2d___0x_80216c5c,uVar6,*puVar7,*puVar7,uVar6 + 0x10,
             puVar7[0x10],puVar7[0x10]);
    puVar7 = puVar7 + 1;
    uVar6 = uVar6 + 1;
  } while (uVar6 < 0x10);
  OSReport(s_LR___0x_08x_CR___0x_08x_80216c8c,param_1[0x21],param_1[0x20]);
  OSReport(s_SRR0___0x_08x_SRR1___0x_08x_80216cbc,param_1[0x66],param_1[0x67]);
  OSReport(s_GQRs___________80216cec);
  uVar6 = 0;
  puVar7 = param_1;
  do {
    OSReport(s_gqr_d___0x_08x_gqr_d___0x_08x_80216d00,uVar6,puVar7[0x69],uVar6 + 4,puVar7[0x6d]);
    puVar7 = puVar7 + 1;
    uVar6 = uVar6 + 1;
  } while (uVar6 < 4);
  if ((*(ushort *)((int)param_1 + 0x1a2) & 1) != 0) {
    uVar3 = OSDisableInterrupts();
    uVar2 = DAT_800000d4;
    local_148 = 0;
    local_146 = 0;
    if (auStack_2e8 == DAT_800000d8) {
      DAT_800000d8 = (undefined *)0x0;
    }
    OSSetCurrentContext(auStack_2e8);
    OSReport(s_FPRs___________80216d24);
    uVar6 = 0;
    puVar7 = param_1;
    do {
      uVar4 = __cvt_fp2unsigned(*(undefined8 *)(puVar7 + 0x26));
      uVar5 = __cvt_fp2unsigned(*(undefined8 *)(puVar7 + 0x24));
      OSReport(s_fr_d____d_fr_d____d_80216d38,uVar6,uVar5,uVar6 + 1,uVar4);
      puVar7 = puVar7 + 4;
      uVar6 = uVar6 + 2;
    } while (uVar6 < 0x20);
    OSReport(s_PSFs___________80216d54);
    uVar6 = 0;
    puVar7 = param_1;
    do {
      uVar4 = __cvt_fp2unsigned(*(undefined8 *)(puVar7 + 0x74));
      uVar5 = __cvt_fp2unsigned(*(undefined8 *)(puVar7 + 0x72));
      OSReport(s_ps_d___0x_x_ps_d___0x_x_80216d68,uVar6,uVar5,uVar6 + 1,uVar4);
      puVar7 = puVar7 + 4;
      uVar6 = uVar6 + 2;
    } while (uVar6 < 0x20);
    local_148 = 0;
    local_146 = 0;
    if (auStack_2e8 == DAT_800000d8) {
      DAT_800000d8 = (undefined *)0x0;
    }
    OSSetCurrentContext(uVar2);
    OSRestoreInterrupts(uVar3);
  }
  OSReport(s_Address__Back_Chain_LR_Save_80216d88);
  puVar7 = (undefined4 *)param_1[1];
  uVar6 = 0;
  while (((puVar7 != (undefined4 *)0x0 && (puVar7 != (undefined4 *)0xffffffff)) &&
         (bVar1 = uVar6 < 0x10, uVar6 = uVar6 + 1, bVar1))) {
    OSReport(s_0x_08x__0x_08x_0x_08x_80216db0,puVar7,*puVar7,puVar7[1]);
    puVar7 = (undefined4 *)*puVar7;
  }
  return;
}

