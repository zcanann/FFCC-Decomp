// Function: SetSmithData__8GbaQueueFiUi
// Entry: 800cfcb8
// Size: 640 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetSmithData__8GbaQueueFiUi(GbaQueue *gbaQueue,int param_2,uint param_3)

{
  uint32_t *puVar1;
  uint16_t uVar2;
  undefined2 uVar3;
  ushort uVar4;
  uint32_t uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint32_t *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined local_48;
  undefined uStack_47;
  
  uVar6 = param_3 >> 8 & 0xff;
  puVar1 = Game.game.m_scriptFoodBase + param_2;
  uVar2 = ((CCaravanWork *)*puVar1)->m_inventoryItems[uVar6];
  DeleteItemIdx__12CCaravanWorkFii((CCaravanWork *)*puVar1,uVar6,1);
  iVar14 = 0;
  iVar13 = Game.game.unkCFlatData0[2] + (short)uVar2 * 0x48;
  uVar3 = *(undefined2 *)(iVar13 + (param_3 & 0xff) * 2 + 0x38);
  puVar11 = Game.game.m_scriptFoodBase + param_2;
  iVar12 = iVar13;
  do {
    uVar6 = (uint)*(ushort *)(iVar12 + 0x26);
    if (uVar6 == 0) break;
    uVar4 = *(ushort *)(iVar12 + 0x2c);
    if (uVar4 == 0) break;
    for (iVar10 = 0; iVar10 < (int)(uint)uVar4; iVar10 = iVar10 + 1) {
      iVar7 = 0;
      iVar9 = 0;
      iVar15 = 8;
      do {
        uVar5 = *puVar11;
        iVar8 = iVar7;
        if ((((((int)*(short *)(uVar5 + iVar9 + 0xb6) == uVar6) ||
              (iVar8 = iVar7 + 1, (int)*(short *)(uVar5 + iVar9 + 0xb8) == uVar6)) ||
             (iVar8 = iVar7 + 2, (int)*(short *)(uVar5 + iVar9 + 0xba) == uVar6)) ||
            ((iVar8 = iVar7 + 3, (int)*(short *)(uVar5 + iVar9 + 0xbc) == uVar6 ||
             (iVar8 = iVar7 + 4, (int)*(short *)(uVar5 + iVar9 + 0xbe) == uVar6)))) ||
           ((iVar8 = iVar7 + 5, (int)*(short *)(uVar5 + iVar9 + 0xc0) == uVar6 ||
            ((iVar8 = iVar7 + 6, (int)*(short *)(uVar5 + iVar9 + 0xc2) == uVar6 ||
             (iVar8 = iVar7 + 7, (int)*(short *)(uVar5 + iVar9 + 0xc4) == uVar6)))))) break;
        iVar9 = iVar9 + 0x10;
        iVar7 = iVar7 + 8;
        iVar15 = iVar15 + -1;
        iVar8 = iVar7;
      } while (iVar15 != 0);
      DeleteItemIdx__12CCaravanWorkFii((CCaravanWork *)*puVar11,iVar8,1);
    }
    iVar14 = iVar14 + 1;
    iVar12 = iVar12 + 2;
  } while (iVar14 < 3);
  uVar6 = AddItem__12CCaravanWorkFiPi((CCaravanWork *)*puVar1,uVar3,0);
  uStack_47 = (undefined)(param_3 >> 0x10);
  local_48 = (undefined)(param_3 >> 0x18);
  if (-1 < (int)(-uVar6 | uVar6)) {
    SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_48,uStack_47);
  }
  uVar6 = AddGil__12CCaravanWorkFi
                    ((CCaravanWork *)*puVar1,
                     -(int)((float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(iVar13 + 0x24)) -
                                   DOUBLE_80330d40) *
                           (float)(((double)CONCAT44(0x43300000,
                                                     (int)((CCaravanWork *)*puVar1)->m_shopParam ^
                                                     0x80000000) - DOUBLE_80330d48) /
                                  DOUBLE_80330d38)));
  if (-1 < (int)(-uVar6 | uVar6)) {
    SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_48,uStack_47);
  }
  SendResult__6JoyBusFiiii(&Joybus,param_2,0,local_48,uStack_47);
  return;
}

