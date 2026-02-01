// Function: SysControl__13CFlatRuntime2Fii
// Entry: 80069da0
// Size: 640 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SysControl__13CFlatRuntime2Fii(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  
  bVar4 = (byte)param_3;
  switch(param_2) {
  case 0:
    CFlat._4836_1_ = (byte)((int)(char)bVar4 << 7) | CFlat._4836_1_ & 0x7f;
    break;
  case 2:
    CFlat._4836_1_ = (byte)((int)(char)bVar4 << 3) & 8 | CFlat._4836_1_ & 0xf7;
    break;
  case 3:
    CFlat._4840_4_ = param_3;
    break;
  case 4:
    Game.game.m_gameWork.m_radarType = bVar4;
    break;
  case 5:
    CFlat._4844_4_ = param_3;
    break;
  case 6:
  case 7:
  case 8:
  case 0xc:
  case 0xd:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x15:
  case 0x16:
    iVar2 = 0;
    iVar1 = -0x7fde1140;
    do {
      iVar3 = *(int *)(iVar1 + 0xc5d0);
      if ((iVar3 != 0) && ((param_3 == 0 || ((*(uint *)(iVar3 + 0x6ec) & param_3) != 0)))) {
        sysControl__8CGMonObjFi(iVar3,param_2);
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar2 < 0x40);
    break;
  case 9:
    ClrBattleItem__8CMenuPcsFv(&MenuPcs);
    break;
  case 10:
    CFlat._4836_1_ = (byte)((int)(char)bVar4 << 4) & 0x10 | CFlat._4836_1_ & 0xef;
    break;
  case 0xb:
    CFlat._4836_1_ = (byte)((int)(char)bVar4 << 5) & 0x20 | CFlat._4836_1_ & 0xdf;
    break;
  case 0xe:
    CFlat._4836_1_ = (byte)((int)(char)bVar4 << 1) & 2 | CFlat._4836_1_ & 0xfd;
    ChangeMogMode__6CCharaFi(&Chara,param_3);
    break;
  case 0x12:
    CFlat._4836_1_ = bVar4 & 1 | CFlat._4836_1_ & 0xfe;
    break;
  case 0x13:
    iVar2 = 0;
    iVar1 = -0x7fde1140;
    do {
      if (*(int *)(iVar1 + 0xc5b0) != 0) {
        sysControl__10CGPartyObjFii(*(int *)(iVar1 + 0xc5b0),param_2,param_3);
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar2 < 4);
    break;
  case 0x14:
    TimeMogFur__6CCharaFv(&Chara);
    break;
  case 0x17:
    Pad._456_4_ = param_3;
    break;
  case 0x18:
    LoadLogoWaitingData__5CGameFv(&Game.game);
    break;
  case 0x19:
    iVar1 = 0;
    iVar3 = -0x7fde1140;
    iVar2 = iVar3;
    do {
      if (*(int *)(iVar2 + 0xc5b0) != 0) {
        damageDelete__10CGCharaObjFv();
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 4;
    } while (iVar1 < 4);
    iVar2 = 0;
    do {
      if (*(int *)(iVar3 + 0xc5d0) != 0) {
        damageDelete__10CGCharaObjFv();
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar2 < 0x40);
    break;
  case 0x1a:
    pppDumpMngSt__8CPartMngFv(&PartMng);
  }
  return;
}

