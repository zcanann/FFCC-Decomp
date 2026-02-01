// Function: Init__8GbaQueueFv
// Entry: 800d1354
// Size: 568 bytes

void Init__8GbaQueueFv(GbaQueue *gbaQueue)

{
  int iVar1;
  GbaQueue *osSemaphore;
  
  memset(&gbaQueue->field_0x30,0,0x400);
  memset(&gbaQueue->field_0x430,0,0x10);
  memset(&gbaQueue->field_0x440,0,4);
  memset(&gbaQueue->field_0x454,0,0x370);
  memset(&gbaQueue->field_0x7c4,0,0x370);
  memset(&gbaQueue->field_0xb34,0,0x500);
  memset(&gbaQueue->field_0x1034,0,0x1400);
  memset(&gbaQueue->field_0x2434,0,0x140);
  memset(&gbaQueue->field_0x2574,0,0x500);
  memset(gbaQueue->caravanName,0,0x80);
  memset(&gbaQueue->field_0x2b00,0,0x188);
  memset(&gbaQueue->field_0x2c8e,0,8);
  memset(&gbaQueue->cmakeInfo,0,0x80);
  memset(&gbaQueue->hitEInfo,0xff,0x10);
  iVar1 = 0;
  osSemaphore = gbaQueue;
  do {
    OSInitSemaphore(osSemaphore->accessSemaphores,1);
    iVar1 = iVar1 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar1 < 4);
  *(undefined4 *)&gbaQueue->field_0x448 = 0xff;
  *(undefined4 *)&gbaQueue->field_0x444 = 0xff;
  gbaQueue->field_0x44c = 0;
  *(undefined2 *)&gbaQueue->field_0x44e = 0;
  *(undefined2 *)&gbaQueue->field_0x450 = 0;
  gbaQueue->letterDatFlg = '\0';
  gbaQueue->field_0x2c88 = 0;
  gbaQueue->field_0x2c89 = 0;
  gbaQueue->shopFlg = 0;
  gbaQueue->field_0x2d39 = 0;
  gbaQueue->sellFlg = 0;
  gbaQueue->buyFlg = 0;
  gbaQueue->mkSmithFlg = 0;
  gbaQueue->resetFlg = 0;
  gbaQueue->chgUseItemFlg = 0;
  gbaQueue->favoriteFlag = '\0';
  gbaQueue->moneyFlg = 0;
  gbaQueue->artifactFlg = 0;
  gbaQueue->strengthFlg = '\0';
  gbaQueue->artiDatFlg = '\0';
  gbaQueue->field_0x2af4 = 0;
  gbaQueue->radarTypeFlg = 0;
  gbaQueue->field_0x2d41 = 0xf;
  gbaQueue->chgRadarMode = 0;
  gbaQueue->chgHitFlg = 0;
  gbaQueue->chgScouFlg = 0;
  gbaQueue->field_0x2d56 = 0;
  gbaQueue->field_0x2d57 = 0;
  gbaQueue->field_0x2d58 = 0;
  gbaQueue->field_0x2d59 = 0;
  gbaQueue->field_0x2d5a = 0;
  gbaQueue->field_0x2d5b = 0;
  gbaQueue->field_0x2d5c = 0;
  gbaQueue->spModeFlg = 0xf;
  gbaQueue->memorysFlg = 0;
  gbaQueue->cmdNumFlag = 0;
  gbaQueue->playModeFlg = 0xf;
  gbaQueue->startBonusFlg = 0;
  gbaQueue->field_0x2c96 = 0xff;
  *(undefined4 *)&gbaQueue->field_0x2c9c = 0;
  gbaQueue->field_0x2cac = 0;
  gbaQueue->compatibilityFlg = 0;
  gbaQueue->field_0x2d32 = 1;
  gbaQueue->field_0x2c97 = 0xff;
  *(undefined4 *)&gbaQueue->field_0x2ca0 = 0;
  gbaQueue->field_0x2cad = 0;
  gbaQueue->field_0x2c8b = 0;
  gbaQueue->field_0x2d33 = 1;
  gbaQueue->field_0x2c98 = 0xff;
  *(undefined4 *)&gbaQueue->field_0x2ca4 = 0;
  gbaQueue->field_0x2cae = 0;
  gbaQueue->field_0x2c8c = 0;
  gbaQueue->field_0x2d34 = 1;
  gbaQueue->field_0x2c99 = 0xff;
  *(undefined4 *)&gbaQueue->field_0x2ca8 = 0;
  gbaQueue->field_0x2caf = 0;
  gbaQueue->field_0x2c8d = 0;
  gbaQueue->field_0x2d35 = 1;
  return;
}

