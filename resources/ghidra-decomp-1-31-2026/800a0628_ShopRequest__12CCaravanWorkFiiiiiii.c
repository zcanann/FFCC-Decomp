// Function: ShopRequest__12CCaravanWorkFiiiiiii
// Entry: 800a0628
// Size: 340 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
ShopRequest__12CCaravanWorkFiiiiiii
          (CCaravanWork *caravanWork,int param_2,int32_t param_3,int32_t param_4,int32_t param_5,
          int32_t param_6,byte param_7)

{
  short sVar1;
  
  if (param_2 == 3) {
    caravanWork->m_shopParam = (int16_t)param_3;
  }
  else if (param_2 < 3) {
    if (param_2 == 1) {
      sVar1 = caravanWork->m_shopListCount;
      caravanWork->m_shopListCount = sVar1 + 1;
      caravanWork->m_shopList[sVar1] = (int16_t)param_3;
    }
    else if (param_2 < 1) {
      if (-1 < param_2) {
        caravanWork->m_shopListCount = 0;
        caravanWork->m_shopRequestState = '\0';
        caravanWork->m_shopList[0] = 0;
        caravanWork->m_shopList[1] = 0;
        caravanWork->m_shopList[2] = 0;
        caravanWork->m_shopList[3] = 0;
        caravanWork->m_shopList[4] = 0;
        caravanWork->m_shopList[5] = 0;
        caravanWork->m_shopList[6] = 0;
        caravanWork->m_shopList[7] = 0;
        caravanWork->m_shopList[8] = 0;
        caravanWork->m_shopList[9] = 0;
        caravanWork->m_shopList[10] = 0;
        caravanWork->m_shopList[0xb] = 0;
        caravanWork->m_shopList[0xc] = 0;
        caravanWork->m_shopList[0xd] = 0;
        caravanWork->m_shopList[0xe] = 0;
        caravanWork->m_shopList[0xf] = 0;
      }
    }
    else {
      caravanWork->m_shopArg0 = param_3;
      caravanWork->m_shopArg1 = param_4;
      caravanWork->m_shopArg2 = param_5;
      caravanWork->m_shopArg3 = param_6;
      caravanWork->m_shopRequestFlags = param_7 & 1;
    }
  }
  else if (param_2 == 5) {
    caravanWork->m_shopRequestState = '\x02';
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      SetSmithFlg__8GbaQueueFi(&GbaQue,caravanWork->m_joybusCaravanId);
    }
    else {
      Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = '\x01';
    }
  }
  else if (param_2 < 5) {
    caravanWork->m_shopRequestState = '\x01';
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      SetShopFlg__8GbaQueueFi(&GbaQue,caravanWork->m_joybusCaravanId);
    }
    else {
      Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = '\x01';
    }
  }
  return 0;
}

