// Function: SetDrawEnv__7CMapObjFv
// Entry: 800293c8
// Size: 368 bytes

void SetDrawEnv__7CMapObjFv(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  
  DAT_8032e498 = CONCAT31(DAT_8032e498._0_3_,*(undefined *)(param_1 + 0x23));
  if (*(char *)(param_1 + 0x21) == '\0') {
    local_10 = CONCAT31(CONCAT21(CONCAT11(MapMng._141708_1_,MapMng._141709_1_),MapMng._141710_1_),
                        MapMng._141711_1_);
  }
  else {
    local_10 = *(uint *)(param_1 + 0xe8);
  }
  if (MapMng._141705_1_ != '\0') {
    local_10 = CONCAT31(CONCAT21(CONCAT11((char)((local_10 >> 0x18) * (uint)(byte)MapMng._141712_1_
                                                >> 8),
                                          (char)((local_10 >> 0x10 & 0xff) *
                                                 (uint)(byte)MapMng._141713_1_ >> 8)),
                                 (char)((local_10 >> 8 & 0xff) * (uint)(byte)MapMng._141714_1_ >> 8)
                                ),(char)((local_10 & 0xff) * (uint)(byte)MapMng._141715_1_ >> 8));
  }
  uVar4 = (uint)*(byte *)(param_1 + 0x24);
  if (uVar4 != 0xff) {
    uVar1 = local_10 >> 0x18;
    uVar2 = local_10 >> 0x10;
    uVar3 = local_10 >> 8;
    local_10 = CONCAT22(CONCAT11((char)(uVar1 * uVar4 >> 8),(char)((uVar2 & 0xff) * uVar4 >> 8)),
                        CONCAT11((char)((uVar3 & 0xff) * uVar4 >> 8),(undefined)local_10));
  }
  local_18 = DAT_8032e498;
  local_14 = local_10;
  SetMapColorAlpha__9CLightPcsFPA4_f8_GXColor8_GXColorUcfffUc
            ((double)*(float *)(param_1 + 0x44),(double)*(float *)(param_1 + 0x48),
             (double)*(float *)(param_1 + 0x54),&LightPcs,param_1 + 0xb8,&local_14,&local_18,
             *(undefined *)(param_1 + 0x26),*(short *)(param_1 + 0x28) >> 7 & 0xff);
  return;
}

