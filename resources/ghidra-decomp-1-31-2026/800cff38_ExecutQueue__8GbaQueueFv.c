// Function: ExecutQueue__8GbaQueueFv
// Entry: 800cff38
// Size: 2972 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ExecutQueue__8GbaQueueFv(GbaQueue *gbaQueue)

{
  uint16_t uVar1;
  short sVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  byte bVar10;
  CCaravanWork *pCVar7;
  undefined4 uVar8;
  int iVar9;
  char cVar11;
  uint uVar12;
  GbaQueue *pGVar13;
  int *piVar14;
  int iVar15;
  GbaQueue *pGVar16;
  int iVar17;
  int iVar18;
  GbaQueue *osSemaphore;
  GbaQueue *pGVar19;
  int *piVar20;
  uint *puVar21;
  undefined local_4a8;
  undefined uStack_4a7;
  undefined local_4a4;
  undefined uStack_4a3;
  undefined local_4a0;
  undefined uStack_49f;
  undefined uStack_49b;
  undefined uStack_49a;
  undefined uStack_499;
  char cStack_497;
  undefined uStack_493;
  char cStack_48f;
  char cStack_48e;
  byte local_48c;
  byte bStack_48b;
  byte bStack_48a;
  char cStack_487;
  byte bStack_486;
  int local_484 [4];
  uint local_474 [257];
  double local_70;
  undefined4 local_68;
  uint uStack_64;
  double local_60;
  GbaQueue *local_58;
  int local_54;
  uint *local_50;
  
  iVar15 = 0;
  pGVar13 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar13->accessSemaphores);
    iVar15 = iVar15 + 1;
    pGVar13 = (GbaQueue *)(pGVar13->accessSemaphores + 1);
  } while (iVar15 < 4);
  memcpy(local_474,&gbaQueue->field_0x30,0x400);
  memcpy(local_484,&gbaQueue->field_0x430,0x10);
  memset(&gbaQueue->field_0x30,0,0x400);
  memset(&gbaQueue->field_0x430,0,0x10);
  iVar15 = 0;
  pGVar13 = gbaQueue;
  do {
    OSSignalSemaphore(pGVar13->accessSemaphores);
    iVar15 = iVar15 + 1;
    pGVar13 = (GbaQueue *)(pGVar13->accessSemaphores + 1);
  } while (iVar15 < 4);
  local_58 = gbaQueue;
  local_54 = -0x7fde1140;
  piVar14 = local_484;
  local_50 = local_474;
  iVar15 = 0;
  pGVar13 = gbaQueue;
  osSemaphore = gbaQueue;
  pGVar19 = gbaQueue;
  do {
    if (gbaQueue->compatibilityStr[iVar15 + -0x18] == '\0') {
      bVar5 = (byte)(1 << iVar15);
      bVar3 = ~bVar5;
      piVar20 = (int *)(local_54 + 0xc5c0);
      bVar4 = ~(byte)(0x10 << iVar15);
      puVar21 = local_50;
      for (iVar18 = 0; iVar18 < *piVar14; iVar18 = iVar18 + 1) {
        bVar10 = *(byte *)puVar21 & 0x3f;
        if (bVar10 == 0x17) {
          pCVar7 = (CCaravanWork *)*piVar20;
          if (pCVar7 != (CCaravanWork *)0x0) {
            cStack_487 = (char)(*puVar21 >> 0x10);
            bStack_486 = (byte)(*puVar21 >> 8);
            if (cStack_487 == '\x01') {
              FGUseItem__12CCaravanWorkFii(pCVar7,(uint)bStack_486,1);
            }
            else if (cStack_487 == '\x02') {
              FGPutItem__12CCaravanWorkFii(pCVar7,(uint)bStack_486,1);
            }
            else if (cStack_487 == '\x03') {
              DeleteItemIdx__12CCaravanWorkFii(pCVar7,(uint)bStack_486,1);
            }
          }
        }
        else if (bVar10 == 0x1a) {
          if (*piVar20 != 0) {
            uVar6 = *puVar21;
            local_48c = (byte)(uVar6 >> 0x18);
            bStack_48b = (byte)(uVar6 >> 0x10);
            if (*piVar20 != 0) {
              bStack_48a = (byte)(uVar6 >> 8);
              if ((int)(uint)local_48c >> 6 == 0) {
                (&gbaQueue->field_0x2cac)[iVar15] = bStack_48b | 0x80;
                *(uint *)&pGVar19->field_0x2c9c = (uint)bStack_48a << 0x18;
                *(uint *)&pGVar19->field_0x2c9c =
                     *(uint *)&pGVar19->field_0x2c9c | (uVar6 & 0xff) << 0x10;
              }
              else if ((&gbaQueue->field_0x2cac)[iVar15] == '\0') {
                SendResult__6JoyBusFiiii(&Joybus,iVar15,1,local_48c,bStack_48b);
              }
              else {
                *(uint *)&pGVar19->field_0x2c9c =
                     *(uint *)&pGVar19->field_0x2c9c | (uint)bStack_48b << 8;
                *(uint *)&pGVar19->field_0x2c9c = *(uint *)&pGVar19->field_0x2c9c | (uint)bStack_48a
                ;
                SendResult__6JoyBusFiiii
                          (&Joybus,iVar15,0,local_48c,(&gbaQueue->field_0x2cac)[iVar15] & 7);
                if (((&gbaQueue->field_0x2cac)[iVar15] & 7) == 1) {
                  FGPutGil__12CCaravanWorkFi
                            ((CCaravanWork *)*piVar20,*(undefined4 *)&pGVar19->field_0x2c9c);
                }
                *(undefined4 *)&pGVar19->field_0x2c9c = 0;
                (&gbaQueue->field_0x2cac)[iVar15] = 0;
              }
            }
            else {
              SendResult__6JoyBusFiiii(&Joybus,iVar15,1,local_48c,bStack_48b);
            }
          }
        }
        else if (bVar10 == 0x1e) {
          if ((CCaravanWork *)*piVar20 != (CCaravanWork *)0x0) {
            cStack_48f = (char)(*puVar21 >> 0x10);
            cStack_48e = (char)(*puVar21 >> 8);
            ChgEquipPos__12CCaravanWorkFii
                      ((CCaravanWork *)*piVar20,(int)cStack_48f,(short)cStack_48e);
          }
        }
        else if (bVar10 == 0x1f) {
          if (*piVar20 != 0) {
            uVar6 = *puVar21;
            uStack_493 = (undefined)(uVar6 >> 0x10);
            uStack_4a7 = (undefined)uVar6;
            local_4a8 = (undefined)(uVar6 >> 8);
            ChgCmdLst__12CCaravanWorkFii(*piVar20,uStack_493,(int)CONCAT11(uStack_4a7,local_4a8));
          }
        }
        else if (bVar10 == 0xc) {
          if (*piVar20 != 0) {
            bVar10 = *(byte *)((int)puVar21 + 1);
            if (bVar10 == 3) {
              OSWaitSemaphore(osSemaphore->accessSemaphores);
              gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & bVar3;
              OSSignalSemaphore(osSemaphore->accessSemaphores);
              SetLetterSize__6JoyBusFii(&Joybus,iVar15,0);
              uVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,iVar15);
              MakeLetterList__8GbaQueueFiPc(gbaQueue,iVar15,uVar8);
            }
            else if (bVar10 == 2) {
              OSWaitSemaphore(osSemaphore->accessSemaphores);
              gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & bVar3;
              OSSignalSemaphore(osSemaphore->accessSemaphores);
              SetLetterSize__6JoyBusFii(&Joybus,iVar15,0);
              FGLetterOpen__12CCaravanWorkFi
                        ((CCaravanWork *)*piVar20,(uint)*(byte *)((int)puVar21 + 2));
              uVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,iVar15);
              MakeLetterData__8GbaQueueFiPci
                        (gbaQueue,iVar15,uVar8,(uint)*(byte *)((int)puVar21 + 2));
            }
            else if (bVar10 == 6) {
              OSWaitSemaphore(osSemaphore->accessSemaphores);
              gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & bVar3;
              OSSignalSemaphore(osSemaphore->accessSemaphores);
              SetLetterSize__6JoyBusFii(&Joybus,iVar15,0);
              uVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,iVar15);
              MakeSellData__8GbaQueueFiPc(gbaQueue,iVar15,uVar8);
            }
            else if (bVar10 == 7) {
              OSWaitSemaphore(osSemaphore->accessSemaphores);
              gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & bVar3;
              OSSignalSemaphore(osSemaphore->accessSemaphores);
              SetLetterSize__6JoyBusFii(&Joybus,iVar15,0);
              uVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,iVar15);
              MakeBuyData__8GbaQueueFiPc(gbaQueue,iVar15,uVar8);
            }
            else if (bVar10 == 8) {
              OSWaitSemaphore(osSemaphore->accessSemaphores);
              gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & bVar3;
              OSSignalSemaphore(osSemaphore->accessSemaphores);
              SetLetterSize__6JoyBusFii(&Joybus,iVar15,0);
              uVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,iVar15);
              MakeSmithData__8GbaQueueFiPc(gbaQueue,iVar15,uVar8);
            }
            else if (bVar10 == 9) {
              OSWaitSemaphore(osSemaphore->accessSemaphores);
              gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & bVar3;
              OSSignalSemaphore(osSemaphore->accessSemaphores);
              SetLetterSize__6JoyBusFii(&Joybus,iVar15,0);
              uVar8 = GetLetterBuffer__6JoyBusFi(&Joybus,iVar15);
              MakeArtiData__8GbaQueueFiPc(gbaQueue,iVar15,uVar8);
            }
          }
        }
        else if (bVar10 == 0x14) {
          bVar10 = *(byte *)((int)puVar21 + 1);
          if ((bVar10 == 0) || (bVar10 == 1)) {
            if (*piVar20 != 0) {
              MoveLetterItem__8GbaQueueFiUi(gbaQueue,iVar15,*puVar21);
            }
          }
          else if (bVar10 == 2) {
            ChkCMakeCharaType__8GbaQueueFiUi(gbaQueue,iVar15,*puVar21);
          }
          else if (bVar10 == 3) {
            ChkCMakeJob__8GbaQueueFiUi(gbaQueue,iVar15,*puVar21);
          }
          else if ((bVar10 == 4) || (bVar10 == 5)) {
            cStack_497 = (char)(*puVar21 >> 0x10);
            iVar17 = 0;
            do {
              iVar9 = SetMType__6JoyBusFii(&Joybus,iVar15,4);
              if (iVar9 == 0) break;
              iVar17 = iVar17 + 1;
            } while (iVar17 < 10);
            if (9 < iVar17) {
              cStack_497 = '\x04';
            }
            if (cStack_497 == '\x04') {
              ClrCMakeFlg__8CMenuPcsFi(&MenuPcs,iVar15);
            }
            else if (cStack_497 == '\x05') {
              SetCMakeEnd__8CMenuPcsFi(&MenuPcs,iVar15);
            }
          }
          else if (bVar10 == 6) {
            uVar6 = *puVar21;
            OSWaitSemaphore(osSemaphore->accessSemaphores);
            uStack_49a = (undefined)(uVar6 >> 8);
            uStack_499 = (undefined)uVar6;
            pGVar13->field_0x2ccb = uStack_49a;
            pGVar13->field_0x2ccc = uStack_499;
            OSSignalSemaphore(osSemaphore->accessSemaphores);
            uStack_49b = (undefined)(uVar6 >> 0x10);
            SendResult__6JoyBusFiiii(&Joybus,iVar15,0,uStack_49b,0);
          }
          else if (bVar10 == 7) {
            OSWaitSemaphore(osSemaphore->accessSemaphores);
            gbaQueue->shopFlg = gbaQueue->shopFlg & bVar3;
            gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & bVar3;
            OSSignalSemaphore(osSemaphore->accessSemaphores);
            iVar17 = 0;
            do {
              iVar9 = SetMType__6JoyBusFii(&Joybus,iVar15,0);
              if (iVar9 == 0) break;
              iVar17 = iVar17 + 1;
            } while (iVar17 < 10);
            CallShop__12CCaravanWorkFiiiii((CCaravanWork *)*piVar20,0,0,0,0,0);
          }
          else if (bVar10 == 8) {
            pCVar7 = (CCaravanWork *)*piVar20;
            if (pCVar7 != (CCaravanWork *)0x0) {
              uVar6 = *puVar21;
              uVar12 = uVar6 >> 8 & 0xff;
              uVar1 = pCVar7->m_inventoryItems[uVar12];
              DeleteItemIdx__12CCaravanWorkFii(pCVar7,uVar12,1);
              local_70 = (double)(CONCAT44(0x43300000,(int)((CCaravanWork *)*piVar20)->m_shopParam)
                                 ^ 0x80000000);
              uStack_64 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + (short)uVar1 * 0x48 + 0x20)
              ;
              local_68 = 0x43300000;
              iVar17 = (int)((float)((local_70 - DOUBLE_80330d48) / DOUBLE_80330d38) *
                             FLOAT_80330d50 *
                            (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330d40));
              local_60 = (double)(longlong)iVar17;
              if (iVar17 < 1) {
                iVar17 = 1;
              }
              AddGil__12CCaravanWorkFi((CCaravanWork *)*piVar20,iVar17);
              local_4a0 = (undefined)(uVar6 >> 0x18);
              uStack_49f = (undefined)(uVar6 >> 0x10);
              SendResult__6JoyBusFiiii(&Joybus,iVar15,0,local_4a0,uStack_49f);
            }
          }
          else if (bVar10 == 9) {
            if (*piVar20 != 0) {
              uVar6 = *puVar21;
              iVar17 = 0;
              sVar2 = *(short *)(*piVar20 + (uVar6 >> 8 & 0xff) * 2 + 0xbe6);
              while( true ) {
                uStack_4a3 = (undefined)(uVar6 >> 0x10);
                local_4a4 = (undefined)(uVar6 >> 0x18);
                if ((int)(uVar6 & 0xff) <= iVar17) break;
                uVar12 = AddItem__12CCaravanWorkFiPi((CCaravanWork *)*piVar20,sVar2,0);
                if (-1 < (int)(-uVar12 | uVar12)) {
                  SendResult__6JoyBusFiiii(&Joybus,iVar15,1,local_4a4,uStack_4a3);
                }
                iVar17 = iVar17 + 1;
              }
              local_68 = 0x43300000;
              local_60 = (double)(CONCAT44(0x43300000,(int)((CCaravanWork *)*piVar20)->m_shopParam)
                                 ^ 0x80000000);
              uStack_64 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + sVar2 * 0x48 + 0x20);
              iVar17 = (int)((float)((local_60 - DOUBLE_80330d48) / DOUBLE_80330d38) *
                            (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330d40));
              local_70 = (double)(longlong)iVar17;
              AddGil__12CCaravanWorkFi((CCaravanWork *)*piVar20,-(iVar17 * (uVar6 & 0xff)));
              SendResult__6JoyBusFiiii(&Joybus,iVar15,0,local_4a4,uStack_4a3);
            }
          }
          else if (bVar10 == 10) {
            if (*piVar20 != 0) {
              SetSmithData__8GbaQueueFiUi(gbaQueue,iVar15,*puVar21);
            }
          }
          else if (bVar10 == 0xb) {
            OSWaitSemaphore(osSemaphore->accessSemaphores);
            gbaQueue->shopFlg = gbaQueue->shopFlg & bVar4;
            gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & bVar4;
            OSSignalSemaphore(osSemaphore->accessSemaphores);
            iVar17 = 0;
            do {
              iVar9 = SetMType__6JoyBusFii(&Joybus,iVar15,0);
              if (iVar9 == 0) break;
              iVar17 = iVar17 + 1;
            } while (iVar17 < 10);
            CallShop__12CCaravanWorkFiiiii((CCaravanWork *)*piVar20,1,0,0,0,0);
          }
          else if (bVar10 == 0x15) {
            iVar17 = 0;
            pGVar16 = gbaQueue;
            do {
              OSWaitSemaphore(pGVar16->accessSemaphores);
              iVar17 = iVar17 + 1;
              pGVar16 = (GbaQueue *)(pGVar16->accessSemaphores + 1);
            } while (iVar17 < 4);
            iVar17 = 0;
            gbaQueue->moneyFlg = gbaQueue->moneyFlg | bVar5;
            pGVar16 = gbaQueue;
            do {
              OSSignalSemaphore(pGVar16->accessSemaphores);
              iVar17 = iVar17 + 1;
              pGVar16 = (GbaQueue *)(pGVar16->accessSemaphores + 1);
            } while (iVar17 < 4);
          }
        }
        else if (bVar10 == 0x15) {
          if (*piVar20 != 0) {
            ReplyLetter__8GbaQueueFi(gbaQueue,iVar15);
          }
        }
        else if ((bVar10 == 6) && (*(byte *)((int)puVar21 + 1) == 0x18)) {
          if (*piVar20 != 0) {
            *(undefined4 *)(*piVar20 + 0x8a0) = 1;
          }
          (&gbaQueue->field_0x2c96)[iVar15] = 0xff;
        }
        else if (bVar10 == 0x1c) {
          ChkCMakeName__8GbaQueueFiUi(gbaQueue,iVar15,*puVar21);
        }
        else if (bVar10 == 0x1d) {
          CMakeFavorite__8GbaQueueFiUi(gbaQueue,iVar15,*puVar21);
        }
        puVar21 = puVar21 + 1;
      }
      if (-1 < (char)(&gbaQueue->field_0x2c96)[iVar15]) {
        if (((&gbaQueue->field_0x2c96)[iVar15] == '\0') &&
           (iVar18 = SendMask__6JoyBusFiUs(&Joybus,iVar15,*(undefined2 *)&local_58->field_0x2c8e),
           iVar18 == 0)) {
          (&gbaQueue->field_0x2c96)[iVar15] = 6;
        }
        (&gbaQueue->field_0x2c96)[iVar15] = (&gbaQueue->field_0x2c96)[iVar15] + -1;
      }
      if (((int)(char)gbaQueue->field_0x2c89 & 1 << iVar15) != 0) {
        cVar11 = IsLetterMenu__6JoyBusFi(&Joybus,iVar15);
        if (cVar11 == '\0') {
          gbaQueue->field_0x2c89 = gbaQueue->field_0x2c89 & bVar3;
        }
        else {
          iVar18 = SendAddLetter__6JoyBusFi(&Joybus,iVar15);
          if (iVar18 == 0) {
            gbaQueue->field_0x2c89 = gbaQueue->field_0x2c89 & bVar3;
          }
        }
      }
    }
    iVar15 = iVar15 + 1;
    pGVar19 = (GbaQueue *)&pGVar19->accessSemaphores[0].queue;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
    local_54 = local_54 + 4;
    pGVar13 = (GbaQueue *)&pGVar13->accessSemaphores[2].queue.tail;
    piVar14 = piVar14 + 1;
    local_58 = (GbaQueue *)((int)&local_58->accessSemaphores[0].count + 2);
    local_50 = local_50 + 0x40;
    if (3 < iVar15) {
      return;
    }
  } while( true );
}

