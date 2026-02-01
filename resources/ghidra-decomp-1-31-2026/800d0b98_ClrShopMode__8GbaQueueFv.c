// Function: ClrShopMode__8GbaQueueFv
// Entry: 800d0b98
// Size: 596 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ClrShopMode__8GbaQueueFv(GbaQueue *gbaQueue)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  GbaQueue *osSemaphore;
  int iVar5;
  
  iVar5 = -0x7fde1140;
  iVar4 = 0;
  osSemaphore = gbaQueue;
  do {
    if (*(int *)(iVar5 + 0xc5c0) != 0) {
      if (*(char *)(*(int *)(iVar5 + 0xc5c0) + 0xbe0) == '\x01') {
        OSWaitSemaphore(osSemaphore->accessSemaphores);
        bVar1 = ~(byte)(1 << iVar4);
        gbaQueue->shopFlg = gbaQueue->shopFlg & bVar1;
        gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & bVar1;
        OSSignalSemaphore(osSemaphore->accessSemaphores);
        iVar3 = 0;
        do {
          iVar2 = SetMType__6JoyBusFii(&Joybus,iVar4,0);
          if (iVar2 == 0) break;
          iVar3 = iVar3 + 1;
        } while (iVar3 < 10);
        CallShop__12CCaravanWorkFiiiii(*(CCaravanWork **)(iVar5 + 0xc5c0),0,0,0,0,0);
      }
      if (*(char *)(*(int *)(iVar5 + 0xc5c0) + 0xbe0) == '\x02') {
        OSWaitSemaphore(osSemaphore->accessSemaphores);
        bVar1 = ~(byte)(0x10 << iVar4);
        gbaQueue->shopFlg = gbaQueue->shopFlg & bVar1;
        gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & bVar1;
        OSSignalSemaphore(osSemaphore->accessSemaphores);
        iVar3 = 0;
        do {
          iVar2 = SetMType__6JoyBusFii(&Joybus,iVar4,0);
          if (iVar2 == 0) break;
          iVar3 = iVar3 + 1;
        } while (iVar3 < 10);
        CallShop__12CCaravanWorkFiiiii(*(CCaravanWork **)(iVar5 + 0xc5c0),1,0,0,0,0);
      }
      if (((uint)(byte)gbaQueue->field_0x2d39 & 1 << iVar4) == 0) {
        if (((uint)(byte)gbaQueue->field_0x2d39 & 0x10 << iVar4) != 0) {
          OSWaitSemaphore(osSemaphore->accessSemaphores);
          bVar1 = (byte)(0x10 << iVar4);
          gbaQueue->shopFlg = gbaQueue->shopFlg | bVar1;
          OSSignalSemaphore(osSemaphore->accessSemaphores);
          iVar3 = SetMType__6JoyBusFii(&Joybus,iVar4,3);
          if (iVar3 == 0) {
            gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & ~bVar1;
          }
          else {
            gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 | bVar1;
          }
        }
      }
      else {
        OSWaitSemaphore(osSemaphore->accessSemaphores);
        bVar1 = (byte)(1 << iVar4);
        gbaQueue->shopFlg = gbaQueue->shopFlg | bVar1;
        OSSignalSemaphore(osSemaphore->accessSemaphores);
        iVar3 = SetMType__6JoyBusFii(&Joybus,iVar4,2);
        if (iVar3 == 0) {
          gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & ~bVar1;
        }
        else {
          gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 | bVar1;
        }
      }
    }
    iVar4 = iVar4 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
    iVar5 = iVar5 + 4;
    if (3 < iVar4) {
      return;
    }
  } while( true );
}

