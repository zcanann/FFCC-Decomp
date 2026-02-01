// Function: IsOutOfShouki__12CCaravanWorkFv
// Entry: 800a269c
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 IsOutOfShouki__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  undefined4 uVar1;
  void *pvVar2;
  
  pvVar2 = (caravanWork->gObjWork).m_ownerObj;
  uVar1 = 0;
  if (FLOAT_803309a8 * Game.game.unkFloat_0xca10 < *(float *)((int)pvVar2 + 0x5bc)) {
    if ((caravanWork->gObjWork).m_hp != 0) {
      if ((((int)((uint)(byte)CFlat._4836_1_ << 0x18) < 0) ||
          ((int)((uint)(byte)CFlat._4836_1_ << 0x1b | (uint)((byte)CFlat._4836_1_ >> 5)) < 0)) &&
         ((int)((uint)*(byte *)((int)pvVar2 + 0x9b) << 0x18) < 0)) {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

