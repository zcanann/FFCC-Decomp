// Function: VIConfigure
// Entry: 8018c6ac
// Size: 2088 bytes

void VIConfigure(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar9;
  uint uVar8;
  int iVar10;
  short sVar11;
  short sVar12;
  int iVar13;
  
  uVar2 = OSDisableInterrupts();
  uVar6 = DAT_800000cc;
  if (DAT_8030cc5c != (*param_1 & 3)) {
    DAT_8032f104 = 1;
    DAT_8030cc5c = *param_1 & 3;
  }
  uVar4 = *param_1 >> 2;
  if ((uVar4 == 4) && (DAT_8032f134 == 0)) {
    DAT_8032f134 = 1;
    OSReport(s__________________________________80217a40);
    OSReport(s_______C_A_U_T_I_O_N_______80217a6c);
    OSReport(s_This_TV_format__DEBUG_PAL__is_on_80217a98);
    OSReport(s_temporary_solution_until_PAL_DAC_80217ac4);
    OSReport(s_is_available__Please_do_NOT_use_t_80217af0);
    OSReport(s_mode_in_real_games____80217b1c);
    OSReport(s__________________________________80217a40);
  }
  if (uVar6 == 2) {
LAB_8018c7b4:
    if (((uVar4 == 0) || (uVar4 == 2)) || (uVar4 == 6)) goto LAB_8018c7fc;
  }
  else if ((int)uVar6 < 2) {
    if (uVar6 == 0) goto LAB_8018c7b4;
    if (-1 < (int)uVar6) {
LAB_8018c7d0:
      if ((uVar4 == 1) || (uVar4 == 5)) goto LAB_8018c7fc;
    }
  }
  else {
    if (uVar6 == 6) goto LAB_8018c7b4;
    if (((int)uVar6 < 6) && (4 < (int)uVar6)) goto LAB_8018c7d0;
  }
  OSPanic(&DAT_8032eb0c,0x75c,s_VIConfigure____Tried_to_change_m_80217b48,uVar6,uVar4);
LAB_8018c7fc:
  if ((uVar4 == 0) || (DAT_8030cc60 = uVar4, uVar4 == 2)) {
    DAT_8030cc60 = uVar6;
  }
  DAT_8030cc38 = *(short *)((int)param_1 + 10);
  if (DAT_8030cc5c == 1) {
    DAT_8030cc3a = *(short *)(param_1 + 3) << 1;
  }
  else {
    DAT_8030cc3a = *(ushort *)(param_1 + 3);
  }
  DAT_8030cc3c = *(ushort *)((int)param_1 + 0xe);
  DAT_8030cc4a = *(ushort *)(param_1 + 1);
  DAT_8030cc4c = *(short *)(param_1 + 2);
  DAT_8030cc58 = param_1[5];
  DAT_8030cc4e = 0;
  DAT_8030cc50 = 0;
  DAT_8030cc3e = DAT_8030cc4c;
  if (((DAT_8030cc5c != 2) && (DAT_8030cc5c != 3)) && (DAT_8030cc58 == 0)) {
    DAT_8030cc3e = DAT_8030cc4c << 1;
  }
  DAT_8030cc7c = (uint)(DAT_8030cc5c == 3);
  DAT_8030cc52 = DAT_8030cc4a;
  DAT_8030cc54 = DAT_8030cc4c;
  puVar3 = (undefined *)getTiming(DAT_8030cc60 * 4 + DAT_8030cc5c);
  uVar6 = 0x2d0 - DAT_8030cc3c;
  uVar4 = (int)DAT_8030cc38 + (int)DAT_8032f100;
  if (((int)uVar4 <= (int)uVar6) && (uVar6 = uVar4, (int)uVar4 < 0)) {
    uVar6 = 0;
  }
  DAT_8030cc40 = (undefined2)uVar6;
  if (DAT_8030cc58 == 0) {
    iVar5 = 2;
  }
  else {
    iVar5 = 1;
  }
  iVar10 = (int)DAT_8032f102;
  uVar7 = DAT_8030cc3a & 1;
  uVar4 = uVar7;
  if ((int)uVar7 < (short)DAT_8030cc3a + iVar10) {
    uVar4 = (short)DAT_8030cc3a + iVar10;
  }
  DAT_8030cc42 = (undefined2)uVar4;
  iVar1 = *(short *)(puVar3 + 2) * 2 - uVar7;
  iVar13 = (int)(short)DAT_8030cc3a + DAT_8030cc3e + iVar10;
  if (iVar13 - iVar1 < 1) {
    sVar12 = 0;
  }
  else {
    sVar12 = (short)iVar13 - (short)iVar1;
  }
  iVar13 = (short)DAT_8030cc3a + iVar10;
  if ((int)(iVar13 - uVar7) < 0) {
    sVar11 = (short)iVar13 - (short)uVar7;
  }
  else {
    sVar11 = 0;
  }
  DAT_8030cc44 = (DAT_8030cc3e + sVar11) - sVar12;
  if ((int)(((short)DAT_8030cc3a + iVar10) - uVar7) < 0) {
    iVar13 = ((short)DAT_8030cc3a + iVar10) - uVar7;
  }
  else {
    iVar13 = 0;
  }
  DAT_8030cc46 = DAT_8030cc50 - (short)(iVar13 / iVar5);
  iVar13 = (int)(short)DAT_8030cc3a + DAT_8030cc3e + iVar10;
  if (iVar13 - iVar1 < 1) {
    iVar13 = 0;
  }
  else {
    iVar13 = iVar13 - iVar1;
  }
  iVar10 = (short)DAT_8030cc3a + iVar10;
  if ((int)(iVar10 - uVar7) < 0) {
    iVar10 = iVar10 - uVar7;
  }
  else {
    iVar10 = 0;
  }
  DAT_8030cc48 = (DAT_8030cc54 + (short)(iVar10 / iVar5)) - (short)(iVar13 / iVar5);
  if (DAT_8032f0fc == 0) {
    DAT_8030cc60 = 3;
  }
  iVar5 = (int)(uint)*(ushort *)(puVar3 + 0x18) >> 1;
  if (((uint)*(ushort *)(puVar3 + 0x18) + iVar5 * -2 & 0xffff) == 0) {
    sVar12 = 0;
  }
  else {
    sVar12 = *(short *)(puVar3 + 0x1a);
  }
  DAT_8030cb7a = sVar12 + 1;
  DAT_8030cb78 = (short)iVar5 + 1U | 0x1000;
  if ((DAT_8030cc5c == 2) || (DAT_8030cc5c == 3)) {
    uVar9 = DAT_8030cb4a & 0xfffb | 4;
  }
  else {
    uVar9 = (ushort)((DAT_8030cc5c & 1) << 2) | DAT_8030cb4a & 0xfffb;
  }
  uVar9 = uVar9 & 0xfff7 | (ushort)(DAT_8030cc7c << 3);
  if ((DAT_8030cc60 == 4) || (DAT_8030cc60 - 5 < 2)) {
    DAT_8030cb4a = uVar9 & 0xfcff;
  }
  else {
    DAT_8030cb4a = uVar9 & 0xfcff | (ushort)(DAT_8030cc60 << 8);
  }
  uVar4 = *param_1;
  if (((uVar4 == 2) || (uVar4 == 3)) || (uVar4 == 0x1a)) {
    DAT_8030cbb4 = DAT_8030cbb4 & 0xfffe | 1;
  }
  else {
    DAT_8030cbb4 = DAT_8030cbb4 & 0xfffe;
  }
  uVar7 = (uint)DAT_8030cc3c;
  uVar8 = (uint)DAT_8030cc52;
  uVar4 = uVar8;
  if (DAT_8030cc7c != 0) {
    uVar4 = uVar8 << 1;
  }
  if ((uVar4 & 0xffff) < uVar7) {
    DAT_8030cb92 = (ushort)((uVar7 + (uVar4 & 0xffff) * 0x100 + -1) / uVar7) | 0x1000;
    DAT_8030cbb8 = (undefined2)uVar4;
    DAT_8032f10c = DAT_8032f10c | 0x4000280;
  }
  else {
    DAT_8030cb92 = 0x100;
    DAT_8032f10c = DAT_8032f10c | 0x4000200;
  }
  DAT_8030cb4e = *(undefined2 *)(puVar3 + 0x1a);
  DAT_8030cb4c = *(undefined2 *)(puVar3 + 0x1d);
  uVar4 = ((uint)(byte)puVar3[0x1f] + (uVar6 & 0xffff)) - 0x28;
  DAT_8030cb52 = (ushort)(byte)puVar3[0x1c] | (short)uVar4 * 0x80;
  DAT_8030cb50 = (ushort)(uVar4 >> 9) |
                 (short)(((uint)*(ushort *)(puVar3 + 0x20) + (uVar6 & 0xffff) + 0x28) -
                        (0x2d0 - uVar7)) * 2;
  DAT_8030cb5e = (ushort)(byte)puVar3[0xc] | *(short *)(puVar3 + 0x10) << 5;
  DAT_8030cb5c = (ushort)(byte)puVar3[0xe] | *(short *)(puVar3 + 0x14) << 5;
  DAT_8030cb62 = (ushort)(byte)puVar3[0xd] | *(short *)(puVar3 + 0x12) << 5;
  DAT_8030cb60 = (ushort)(byte)puVar3[0xf] | *(short *)(puVar3 + 0x16) << 5;
  DAT_8032f108 = DAT_8032f108 | 0x7c3c00c0;
  DAT_8030cc64 = (char)((int)(DAT_8030cc4a + 0xf) >> 4);
  DAT_8030cc65 = DAT_8030cc64;
  if (DAT_8030cc58 != 0) {
    DAT_8030cc65 = DAT_8030cc64 << 1;
  }
  DAT_8030cc74 = (char)DAT_8030cc4e + (char)((int)(uint)DAT_8030cc4e >> 4) * -0x10;
  DAT_8030cc66 = (undefined)((int)((uint)DAT_8030cc74 + uVar8 + 0xf) >> 4);
  DAT_8030cb90 = CONCAT11(DAT_8030cc66,DAT_8030cc65);
  DAT_8032f10c = DAT_8032f10c | 0x8000000;
  DAT_8030cc8c = puVar3;
  if (DAT_8032f130 != 0) {
    setFbbRegs(&DAT_8030cc38,&DAT_8030cc6c,&DAT_8030cc70,&DAT_8030cc84,&DAT_8030cc88);
  }
  setVerticalRegs(DAT_8030cc42,DAT_8030cc44,*puVar3,*(undefined2 *)(puVar3 + 2),
                  *(undefined2 *)(puVar3 + 4),*(undefined2 *)(puVar3 + 6),
                  *(undefined2 *)(puVar3 + 8),*(undefined2 *)(puVar3 + 10),DAT_8030cc78);
  OSRestoreInterrupts(uVar2);
  return;
}

