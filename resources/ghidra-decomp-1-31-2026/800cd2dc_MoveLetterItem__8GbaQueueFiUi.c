// Function: MoveLetterItem__8GbaQueueFiUi
// Entry: 800cd2dc
// Size: 316 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void MoveLetterItem__8GbaQueueFiUi(GbaQueue *gbaQueue,int param_2,uint param_3)

{
  uint32_t *puVar1;
  ushort uVar2;
  byte bVar3;
  CCaravanWork *caravanWork;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_r31;
  undefined local_28;
  undefined uStack_27;
  
  iVar6 = (param_3 >> 8 & 0xff) * 0xc;
  puVar1 = Game.game.m_scriptFoodBase + param_2;
  caravanWork = (CCaravanWork *)*puVar1;
  bVar3 = caravanWork->m_letter0[iVar6] >> 3 & 1;
  if (bVar3 == 0) {
    uVar2 = *(ushort *)(caravanWork->m_letter0 + iVar6 + 2);
    if ((uVar2 & 0x1ff) != 0) {
      if (((uVar2 & 0x1ff) == 0) || (0x9e < (uVar2 & 0x1ff))) {
        iVar4 = AddItem__12CCaravanWorkFiPi(caravanWork,uVar2 & 0x1ff,0);
        if (iVar4 == 0) {
          unaff_r31 = 1;
        }
        else {
          unaff_r31 = 0;
        }
      }
      goto LAB_800cd3a4;
    }
  }
  if (bVar3 != 0) {
    if ((*(ushort *)(caravanWork->m_letter0 + iVar6 + 2) & 0x1ff) != 0) {
      iVar5 = (*(ushort *)(caravanWork->m_letter0 + iVar6 + 2) & 0x1ff) * 100;
      iVar4 = CanAddGil__12CCaravanWorkFi(caravanWork,iVar5);
      if (iVar4 == 0) {
        unaff_r31 = 1;
      }
      else {
        AddGil__12CCaravanWorkFi((CCaravanWork *)*puVar1,iVar5);
        unaff_r31 = 0;
      }
    }
  }
LAB_800cd3a4:
  iVar4 = 0;
  do {
    local_28 = (undefined)(param_3 >> 0x18);
    uStack_27 = (undefined)(param_3 >> 0x10);
    iVar5 = SendResult__6JoyBusFiiii(&Joybus,param_2,unaff_r31,local_28,uStack_27);
    if (iVar5 == 0) break;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 10);
  if ((unaff_r31 == 0) && (iVar4 < 10)) {
    *(byte *)(*puVar1 + iVar6 + 0x3ec) = *(byte *)(*puVar1 + iVar6 + 0x3ec) & 0xbf | 0x40;
  }
  return;
}

