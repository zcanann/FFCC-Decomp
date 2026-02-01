// Function: LoadAll__8GbaQueueFv
// Entry: 800d0dec
// Size: 1384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadAll__8GbaQueueFv(GbaQueue *gbaQueue)

{
  char cVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  GbaQueue *pGVar7;
  int iVar8;
  int iVar9;
  GbaQueue *osSemaphore;
  uint uVar10;
  int iVar11;
  
  iVar8 = 0;
  pGVar7 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar7->accessSemaphores);
    iVar8 = iVar8 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
  } while (iVar8 < 4);
  cVar1 = gbaQueue->field_0x2d56;
  gbaQueue->field_0x2d56 = (byte)(-(uint)Game.game.m_gameWork.m_menuStageMode >> 0x1f);
  if (cVar1 != gbaQueue->field_0x2d56) {
    gbaQueue->playModeFlg = 0xf;
  }
  iVar8 = -0x7fde1140;
  bVar3 = Game.game.m_gameWork.m_spModeFlags[0] != '\0';
  if (Game.game.m_gameWork.m_spModeFlags[1] != '\0') {
    bVar3 = bVar3 | 2;
  }
  if (Game.game.m_gameWork.m_spModeFlags[2] != '\0') {
    bVar3 = bVar3 | 4;
  }
  if (Game.game.m_gameWork.m_spModeFlags[3] != '\0') {
    bVar3 = bVar3 | 8;
  }
  bVar4 = bVar3 ^ gbaQueue->field_0x2d5c;
  if ((bVar4 & 1) != 0) {
    gbaQueue->spModeFlg = gbaQueue->spModeFlg | 1;
  }
  if ((bVar4 & 2) != 0) {
    gbaQueue->spModeFlg = gbaQueue->spModeFlg | 2;
  }
  if ((bVar4 & 4) != 0) {
    gbaQueue->spModeFlg = gbaQueue->spModeFlg | 4;
  }
  if ((bVar4 & 8) != 0) {
    gbaQueue->spModeFlg = gbaQueue->spModeFlg | 8;
  }
  gbaQueue->field_0x2d5c = bVar3;
  iVar9 = 0;
  pGVar7 = gbaQueue;
  do {
    OSSignalSemaphore(pGVar7->accessSemaphores);
    uVar2 = CFlat._66564_4_;
    iVar9 = iVar9 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
  } while (iVar9 < 4);
  _LoadPlayerStat__8GbaQueueFv(gbaQueue);
  _LoadEnemyStat__8GbaQueueFv(gbaQueue);
  LoadMapItemStat__8GbaQueueFv(gbaQueue);
  if ((gbaQueue->scrInitEnd == 0) && (uVar2 != 0)) {
    SetRadarType__8GbaQueueFv(gbaQueue);
  }
  if (uVar2 == 0) {
    memset(&gbaQueue->hitEInfo,0xff,0x10);
    gbaQueue->chgHitFlg = 0;
  }
  iVar9 = 0;
  pGVar7 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar7->accessSemaphores);
    iVar9 = iVar9 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
  } while (iVar9 < 4);
  gbaQueue->scrInitEnd = uVar2;
  iVar9 = 0;
  pGVar7 = gbaQueue;
  do {
    OSSignalSemaphore(pGVar7->accessSemaphores);
    iVar9 = iVar9 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
  } while (iVar9 < 4);
  LoadMapObj__8GbaQueueFv(gbaQueue);
  iVar11 = 0;
  pGVar7 = gbaQueue;
  osSemaphore = gbaQueue;
  iVar9 = iVar8;
  do {
    if (*(int *)(iVar9 + 0xc5c0) == 0) {
      (&gbaQueue->field_0x2c96)[iVar11] = 0xff;
    }
    else {
      OSWaitSemaphore(osSemaphore->accessSemaphores);
      uVar5 = *(uint *)(*(int *)(iVar9 + 0xc5c0) + 0x89c);
      uVar10 = uVar5 & 0xffff;
      if ((uVar10 != *(ushort *)&pGVar7->field_0x2c8e) &&
         (iVar6 = SendMask__6JoyBusFiUs(&Joybus,iVar11,uVar10), iVar6 == 0)) {
        *(short *)&pGVar7->field_0x2c8e = (short)uVar5;
        (&gbaQueue->field_0x2c96)[iVar11] = 6;
      }
      OSSignalSemaphore(osSemaphore->accessSemaphores);
    }
    iVar11 = iVar11 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
    pGVar7 = (GbaQueue *)((int)&pGVar7->accessSemaphores[0].count + 2);
    iVar9 = iVar9 + 4;
  } while (iVar11 < 4);
  iVar9 = 0;
  pGVar7 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar7->accessSemaphores);
    iVar9 = iVar9 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
  } while (iVar9 < 4);
  cVar1 = gbaQueue->resetFlg;
  iVar9 = 0;
  pGVar7 = gbaQueue;
  do {
    OSSignalSemaphore(pGVar7->accessSemaphores);
    iVar9 = iVar9 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
  } while (iVar9 < 4);
  iVar9 = 0;
  gbaQueue->resetFlg = 0;
  pGVar7 = gbaQueue;
  do {
    if (*(int *)(iVar8 + 0xc5c0) != 0) {
      uVar10 = 1 << iVar9;
      bVar3 = (byte)uVar10;
      if (((int)cVar1 & uVar10) != 0) {
        if (*(char *)(*(int *)(iVar8 + 0xc5c0) + 0xbe0) == '\x01') {
          OSWaitSemaphore(pGVar7->accessSemaphores);
          gbaQueue->shopFlg = gbaQueue->shopFlg & ~bVar3;
          gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & ~bVar3;
          OSSignalSemaphore(pGVar7->accessSemaphores);
          iVar11 = 0;
          do {
            iVar6 = SetMType__6JoyBusFii(&Joybus,iVar9,0);
            if (iVar6 == 0) break;
            iVar11 = iVar11 + 1;
          } while (iVar11 < 10);
          CallShop__12CCaravanWorkFiiiii(*(CCaravanWork **)(iVar8 + 0xc5c0),0,0,0,0,0);
        }
        if (*(char *)(*(int *)(iVar8 + 0xc5c0) + 0xbe0) == '\x02') {
          OSWaitSemaphore(pGVar7->accessSemaphores);
          bVar4 = ~(byte)(0x10 << iVar9);
          gbaQueue->shopFlg = gbaQueue->shopFlg & bVar4;
          gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & bVar4;
          OSSignalSemaphore(pGVar7->accessSemaphores);
          iVar11 = 0;
          do {
            iVar6 = SetMType__6JoyBusFii(&Joybus,iVar9,0);
            if (iVar6 == 0) break;
            iVar11 = iVar11 + 1;
          } while (iVar11 < 10);
          CallShop__12CCaravanWorkFiiiii(*(CCaravanWork **)(iVar8 + 0xc5c0),1,0,0,0,0);
        }
      }
      if (((byte)gbaQueue->field_0x2d39 & uVar10) == 0) {
        if (((uint)(byte)gbaQueue->field_0x2d39 & 0x10 << iVar9) != 0) {
          OSWaitSemaphore(pGVar7->accessSemaphores);
          bVar3 = (byte)(0x10 << iVar9);
          gbaQueue->shopFlg = gbaQueue->shopFlg | bVar3;
          OSSignalSemaphore(pGVar7->accessSemaphores);
          iVar11 = SetMType__6JoyBusFii(&Joybus,iVar9,3);
          if (iVar11 == 0) {
            gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & ~bVar3;
          }
          else {
            gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 | bVar3;
          }
        }
      }
      else {
        OSWaitSemaphore(pGVar7->accessSemaphores);
        gbaQueue->shopFlg = gbaQueue->shopFlg | bVar3;
        OSSignalSemaphore(pGVar7->accessSemaphores);
        iVar11 = SetMType__6JoyBusFii(&Joybus,iVar9,2);
        if (iVar11 == 0) {
          gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & ~bVar3;
        }
        else {
          gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 | bVar3;
        }
      }
    }
    iVar9 = iVar9 + 1;
    pGVar7 = (GbaQueue *)(pGVar7->accessSemaphores + 1);
    iVar8 = iVar8 + 4;
    if (3 < iVar9) {
      return;
    }
  } while( true );
}

