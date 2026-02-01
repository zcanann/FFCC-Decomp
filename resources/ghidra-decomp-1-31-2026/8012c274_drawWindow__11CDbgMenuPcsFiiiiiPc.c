// Function: drawWindow__11CDbgMenuPcsFiiiiiPc
// Entry: 8012c274
// Size: 1336 bytes

void drawWindow__11CDbgMenuPcsFiiiiiPc
               (int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
               int param_7)

{
  undefined4 *puVar1;
  byte bVar2;
  uint uVar3;
  undefined uVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 local_88;
  
  if (*(int *)(param_1 + 0x2a68) != 1) {
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxAttrFmt(1,9,1,4,0);
    GXSetVtxAttrFmt(1,0xb,1,5,0);
    GXSetChanCtrl(4,0,0,1,0,2,1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    *(undefined4 *)(param_1 + 0x2a68) = 1;
  }
  if ((param_2 & 1) == 0) {
    GXBegin(0x98,1,4);
    puVar5 = &DAT_80212694;
    uVar7 = 0;
    iVar9 = 2;
    do {
      uVar3 = uVar7 >> 1;
      uVar8 = uVar7 + 1;
      uVar7 = uVar7 + 2;
      DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80331ca0);
      DAT_cc008000 = (float)((double)CONCAT44(0x43300000,
                                              param_4 + (param_6 & -(uVar3 & 1)) ^ 0x80000000) -
                            DOUBLE_80331ca0);
      DAT_cc008000 = FLOAT_80331c98;
      DAT_cc008000 = *puVar5;
      DAT_cc008000 = (float)((double)CONCAT44(0x43300000,
                                              param_3 + (param_5 & -(uVar8 & 1)) ^ 0x80000000) -
                            DOUBLE_80331ca0);
      DAT_cc008000 = (float)((double)CONCAT44(0x43300000,
                                              param_4 + (param_6 & -(uVar8 >> 1 & 1)) ^ 0x80000000)
                            - DOUBLE_80331ca0);
      DAT_cc008000 = FLOAT_80331c98;
      puVar1 = puVar5 + 1;
      puVar5 = puVar5 + 2;
      DAT_cc008000 = *puVar1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  uVar7 = param_2 >> 1 & 1;
  GXBegin(0xb0,1,3);
  param_5 = param_3 + param_5;
  param_6 = param_4 + param_6;
  iVar9 = uVar7 * 4;
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_5 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = FLOAT_80331c98;
  DAT_cc008000 = *(undefined4 *)(&DAT_8032ea48 + iVar9);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = FLOAT_80331c98;
  DAT_cc008000 = *(undefined4 *)(&DAT_8032ea48 + iVar9);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_6 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = FLOAT_80331c98;
  DAT_cc008000 = *(undefined4 *)(&DAT_8032ea48 + iVar9);
  GXBegin(0xb0,1,3);
  iVar9 = (1 - uVar7) * 4;
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_5 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = FLOAT_80331c98;
  DAT_cc008000 = *(undefined4 *)(&DAT_8032ea48 + iVar9);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_5 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_6 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = FLOAT_80331c98;
  DAT_cc008000 = *(undefined4 *)(&DAT_8032ea48 + iVar9);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = (float)((double)CONCAT44(0x43300000,param_6 ^ 0x80000000) - DOUBLE_80331ca0);
  DAT_cc008000 = FLOAT_80331c98;
  DAT_cc008000 = *(undefined4 *)(&DAT_8032ea48 + iVar9);
  bVar2 = *(byte *)(*(int *)(param_1 + 0x2a5c) + 0x34);
  if ((int)((uint)bVar2 << 0x19 | (uint)(bVar2 >> 7)) < 0) {
    uVar4 = 0xc0;
    if ((System.m_frameCounter >> 2 & 1) != 0) {
      uVar4 = 0xff;
    }
    local_88 = CONCAT22(CONCAT11(uVar4,uVar4),CONCAT11(uVar4,(char)DAT_80331c88));
    GXBegin(0xb0,1,5);
    uVar6 = param_5 + 1 ^ 0x80000000;
    uVar8 = param_4 - 1 ^ 0x80000000;
    uVar3 = param_3 - 1 ^ 0x80000000;
    uVar7 = param_6 + 1 ^ 0x80000000;
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80331ca0);
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_80331ca0);
    DAT_cc008000 = FLOAT_80331c98;
    DAT_cc008000 = local_88;
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar3) - DOUBLE_80331ca0);
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_80331ca0);
    DAT_cc008000 = FLOAT_80331c98;
    DAT_cc008000 = local_88;
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar3) - DOUBLE_80331ca0);
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar7) - DOUBLE_80331ca0);
    DAT_cc008000 = FLOAT_80331c98;
    DAT_cc008000 = local_88;
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80331ca0);
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar7) - DOUBLE_80331ca0);
    DAT_cc008000 = FLOAT_80331c98;
    DAT_cc008000 = local_88;
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80331ca0);
    DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_80331ca0);
    DAT_cc008000 = FLOAT_80331c98;
    DAT_cc008000 = local_88;
  }
  if (param_7 != 0) {
    drawFont__11CDbgMenuPcsFiiiPc(param_1,5,param_3 + 8,param_4 - 6,param_7);
  }
  return;
}

